#include "backtrack.h"

//复习重点在于如何通过位运算进行优化，以及通过对称性进行剪枝。

class Solution {
    bool isValid(vector<string>& board, int row, int col, int n) {
        int dia_left = col-1, dia_right = col+1;
        for (int i = row-1; i >= 0; i--) {
            if(board[i][col] == 'Q') return false;
            if(dia_left >= 0 && board[i][dia_left] == 'Q') return false;
            if(dia_right < n && board[i][dia_right] == 'Q') return false;
            dia_left--;dia_right++;
        }
        return true;
        
    }

    void addChess(vector<vector<string>>& res, vector<string>& board, int row, int n) {
        if(row == n) {
            res.push_back(board);
            return;
        }
        auto& row_now = board[row];
        for(int col = 0; col < n; col++) {
            if(isValid(board, row, col, n)) {
                row_now[col] = 'Q';
                addChess(res, board, row+1, n);
                row_now[col] = '.';
            }
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;
        vector<string> board(n, string(n, '.'));
        addChess(res, board, 0, n);
        return res;
    }
};

//最佳解法优化：位运算
class SolutionBest {
private:
    vector<vector<string>> res;
    vector<string> board;

    /**
     * @brief 回溯核心函数（使用位运算加速状态传递与位置查找）
     *
     * @param row    当前处理的行号 [0, n-1]
     * @param cols   列占用的位掩码：第 i 位为 1 表示第 i 列已放置皇后
     * @param diag1  主对角线(左下->右上)占用的位掩码
     * @param diag2  副对角线(右下->左上)占用的位掩码
     * @param n      棋盘大小 (N*N)
     */
    void backtrack(int row, int cols, int diag1, int diag2, int n) {
        // 终止条件：成功在所有 n 行都放置了皇后，保存当前棋盘解
        if (row == n) {
            res.push_back(board);
            return;
        }

        /*
         * 【原理 1：算出当前行所有可以放置皇后的位置】
         * 1. (cols | diag1 | diag2)：按位或运算，三者任何一个方向占用了，对应位就是 1 (不可用)。
         * 2. ~(...)：按位取反，把不可用的 1 变成 0，可用的 0 变成 1。
         * 3. (1 << n) - 1：构造掩码 Mask（例如 n=4 时为二进制 01111），避免取反时把高位的无效 0 误变成 1。
         * 最终 availablePositions 中，所有是 1 的 bit 位表示当前行“能够合法放置皇后”。
         */
        int availablePositions = ((1 << n) - 1) & ~(cols | diag1 | diag2);

        // 只要当前行还有可以放皇后的位置，就继续尝试
        while (availablePositions > 0) {
            /*
             * 【原理 2：提取最低位的 1 (Lowbit 技巧)】
             * 依靠计算机补码特性：x & (-x) 可以精准提取出最右边的那个 1，其余位置全部置 0。
             * 示例：x = 01010 (二进制)，-x = 10110 -> x & (-x) = 00010 (成功提取出倒数第二位的 1)
             */
            int position = availablePositions & (-availablePositions);

            /*
             * 【原理 3：抹去最低位的 1】
             * x & (x - 1) 可以把最右边的那个 1 变成 0，表示这个位置我们即将进行尝试。
             * 示例：x = 01010，x - 1 = 01001 -> x & (x - 1) = 01000
             */
            availablePositions &= (availablePositions - 1);

            /*
             * 【原理 4：快速转化位位置为列索引】
             * __builtin_ctz 是 GCC/Clang 硬件级指令 (Count Trailing Zeros)，计算末尾连续 0 的个数。
             * 示例：position = 00100 (只有一个 1)，末尾有 2 个 0，直接对应列索引 col = 2。
             */
            int col = __builtin_ctz(position);

            // 放置皇后
            board[row][col] = 'Q';

            /*
             * 【原理 5：递归下一行，更新对角线掩码】
             * - cols | position：记录列占用。
             * - (diag1 | position) << 1：主对角线下一行影响位置整体向左平移 1 位。
             * - (diag2 | position) >> 1：副对角线下一行影响位置整体向右平移 1 位。
             */
            backtrack(row + 1, cols | position, (diag1 | position) << 1, (diag2 | position) >> 1, n);

            // 回溯：恢复棋盘状态（位掩码通过参数按值传递，无需手动恢复）
            board[row][col] = '.';
        }
    }

    /**
     * @brief 辅助函数：将棋盘解沿垂直中轴线进行镜像翻转
     */
    vector<string> generateSymmetric(const vector<string>& originalBoard, int n) {
        vector<string> symBoard(n, string(n, '.'));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                symBoard[i][j] = originalBoard[i][n - 1 - j];
            }
        }
        return symBoard;
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        board = vector<string>(n, string(n, '.'));

        /*
         * 【原理 6：轴对称剪枝（搜索空间减半）】
         * N 皇后棋盘具有左右轴对称性。
         * 第一行只需要枚举左半边的列 [0, n/2 - 1]，剩下的右半边解可以通过“镜像翻转”直接生成。
         */
        for (int col = 0; col < n / 2; ++col) {
            int pos = 1 << col;
            board[0][col] = 'Q';

            int startIdx = res.size();
            // 传入第一行的占用状态，对角线左移和右移1位传递给第二行
            backtrack(1, pos, pos << 1, pos >> 1, n);
            int endIdx = res.size();

            board[0][col] = '.';

            // 对第一行放在左半边搜出来的所有解，直接翻转生成右半边的对应解
            for (int i = startIdx; i < endIdx; ++i) {
                res.push_back(generateSymmetric(res[i], n));
            }
        }

        /*
         * 如果 N 为奇数（如 N=5），第一行正中间的位置 (col = n/2) 无法镜像，
         * 需要单独跑一次完整的回溯，且不需要执行镜像翻转。
         */
        if (n % 2 == 1) {
            int midCol = n / 2;
            int pos = 1 << midCol;
            board[0][midCol] = 'Q';
            backtrack(1, pos, pos << 1, pos >> 1, n);
            board[0][midCol] = '.';
        }

        return res;
    }
};

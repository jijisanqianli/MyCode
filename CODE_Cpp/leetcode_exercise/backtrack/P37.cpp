#include "backtrack.h"

class Solution {
    vector<char> getCandidates(const vector<vector<char>>& board, int row, int col) {
        vector<char> candidates = {'1','2','3','4','5','6','7','8','9'};
        int rowStart = row / 3 * 3;
        int colStart = col / 3 * 3;
        for (int i = 0; i < 9; i++) {
            if (board[row][i] != '.') {
                candidates[board[row][i] - '1'] = 0;
            }
            if (board[i][col] != '.') {
                candidates[board[i][col] - '1'] = 0;
            }
            int r = rowStart + i / 3;
            int c = colStart + i % 3;
            if (board[r][c] != '.') {
                candidates[board[r][c] - '1'] = 0;
            }
        }
        vector<char> candidates_res;
        for (int i = 0; i < 9; i++) {
            if (candidates[i] != 0) {
                candidates_res.push_back(candidates[i]);
            }
        }
        return candidates_res;
    }

    vector<int> getNext(const vector<vector<char>>& board, int row, int col) {
        for (int i = row; i < 9; i++) {
            int startCol = (i == row) ? col : 0;
            for (int j = startCol; j < 9; j++) {
                if (board[i][j] == '.') {
                    return {i, j};
                }
            }
        }
        return {};
    }

    bool fill(vector<vector<char>>& board, int row, int col) {
        vector<char> candidates = getCandidates(board, row, col);
        for (char c : candidates) {
            board[row][col] = c;
            vector<int> next = getNext(board, row, col);
            if (next.empty()) {
                return true;
            }
            if (fill(board, next[0], next[1])) {
                return true;
            }
            board[row][col] = '.';
        }
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<int> next = getNext(board, 0, 0);
        if (next.empty()) return;
        fill(board, next[0], next[1]);
    }
};

#include <vector>

using namespace std;

class SolutionBest {
    // 使用 3 个数组作为“位掩码（Bitmask）”，记录每一行、每一列、每个九宫格中数字 1~9 的占用状态
    // 每个整数的二进制低 9 位（第 0~8 位）分别对应数字 1~9：
    // 比如二进制 000000101 表示数字 1 和数字 3 已经被占用
    int rowMask[9] = {0};
    int colMask[9] = {0};
    int boxMask[9] = {0};

    // 预先存储所有需要填数的空位坐标 (row, col)，避免递归时重复扫描棋盘
    vector<pair<int, int>> spaces;

    /**
     * 递归回溯求解函数
     * @param board 9x9 的数独棋盘
     * @param idx 当前正在填充第几个空位（即 spaces 数组中的索引）
     */
    bool fill(vector<vector<char>>& board, int idx) {
        // 递归出口：如果 spaces 中的空位全部处理完毕，说明找到了一组可行解
        if (idx == spaces.size()) return true;

        // 获取当前空位的坐标 (r, c)
        auto [r, c] = spaces[idx];
        // 计算当前坐标属于第几个九宫格 (0~8)
        int b = (r / 3) * 3 + c / 3;

        // 【位掩码核心计算】：
        // 1. (rowMask[r] | colMask[c] | boxMask[b]) 计算出同行、同列、同九宫格内【已被占用】的数字掩码
        // 2. ~ 取反：将 1 变为 0（已被占用），0 变为 1（当前可用）
        // 3. & 0x1FF (二进制 111111111)：只保留最低的 9 位，屏蔽掉高位干扰
        // 最终 valid 的二进制中，数值为 1 的位即为当前位置【绝对合法且可用】的数字！
        int valid = ~(rowMask[r] | colMask[c] | boxMask[b]) & 0x1FF;

        // 循环尝试所有当前可用的数字
        while (valid > 0) {
            // 【位运算黑科技】：x & -x 可以快速提取出二进制中“最低位的 1”
            // 比如 valid = 010100 (二进制)，-valid = 101100，两者按位与得到 000100
            int bit = valid & -valid;

            // __builtin_ctz 是 GCC/Clang 内置函数，用于计算二进制末尾 0 的个数
            // 比如 bit 为 000000100（第 2 位为 1，0 开头），末尾有 2 个 0，加上 1 后得到数字 3
            int digit = __builtin_ctz(bit) + 1;

            // --- 1. 尝试放置数字，并更新掩码状态 ---
            board[r][c] = digit + '0';
            rowMask[r] |= bit;  // 将第 r 行的 bit 位置为 1
            colMask[c] |= bit;  // 将第 c 列的 bit 位置为 1
            boxMask[b] |= bit;  // 将第 b 个九宫格的 bit 位置为 1

            // --- 2. 递归填充下一个空位 ---
            if (fill(board, idx + 1)) return true;

            // --- 3. 回溯：清除状态，撤销操作 ---
            board[r][c] = '.';
            rowMask[r] &= ~bit; // 将第 r 行的 bit 位置重新清零
            colMask[c] &= ~bit; // 将第 c 列的 bit 位置重新清零
            boxMask[b] &= ~bit; // 将第 b 个九宫格的 bit 位置重新清零

            // 【位运算技巧】：x & (x - 1) 用于清空二进制最低位的 1
            // 代表当前数字已尝试完毕，准备在下一轮 loop 尝试下一个可用的数字
            valid &= (valid - 1);
        }

        // 所有合法数字都尝试过且均无法解出，返回 false 触发上一层回溯
        return false;
    }

public:
    void solveSudoku(vector<vector<char>>& board) {
        // 第一步：预处理棋盘
        // 1. 扫描初始已知数字，更新行、列、九宫格的位掩码状态
        // 2. 将所有 '.'（待填空位）的坐标保存到 spaces 数组中
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.') {
                    spaces.push_back({i, j});
                } else {
                    int digit = board[i][j] - '0';
                    int bit = 1 << (digit - 1); // 映射为二进制掩码：数字 1 -> 001, 数字 3 -> 100
                    int b = (i / 3) * 3 + j / 3;

                    rowMask[i] |= bit;
                    colMask[j] |= bit;
                    boxMask[b] |= bit;
                }
            }
        }

        // 第二步：从第 0 个空位开始递归求解
        fill(board, 0);
    }
};

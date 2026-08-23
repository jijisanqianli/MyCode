#include "backtrack.h"

class Solution {
    void cut(string s, int startIndex, vector<string>& path, vector<string>& res) {
        for(int i = startIndex; i < s.size() && i < startIndex + 3; i++) {
            if(s[startIndex] == '0' && i > startIndex) break;
            string str = s.substr(startIndex, i - startIndex + 1);
            int num = stoi(str);
            if(num > 255) break;
            path.push_back(str);
            if(path.size() == 4 && i == s.size() - 1) {
                res.push_back(path[0] + "." + path[1] + "." + path[2] + "." + path[3]);
            }
            if(path.size() < 4) cut(s, i + 1, path, res);
            path.pop_back();
        }
    }

    void cutBest(const string& s, int startIndex, int segCount, vector<int>& segments, vector<string>& res) {
        int n = s.size();
        int remainingSegs = 4 - segCount;
        int remainingChars = n - startIndex;

        // 剪枝 1：剩余字符数不足（少于每段最少1个字符）或过多（多于每段最多3个字符），直接返回
        if (remainingChars < remainingSegs || remainingChars > remainingSegs * 3) {
            return;
        }

        // 递归终止：已找到 4 段且刚好消耗完全部字符
        if (segCount == 4) {
            res.push_back(to_string(segments[0]) + "." +
                          to_string(segments[1]) + "." +
                          to_string(segments[2]) + "." +
                          to_string(segments[3]));
            return;
        }

        int num = 0;
        for (int i = startIndex; i < n && i < startIndex + 3; ++i) {
            num = num * 10 + (s[i] - '0'); // O(1) 方式直接计算数字

            if (num > 255) break; // 数值溢出，剪枝

            segments[segCount] = num;
            cutBest(s, i + 1, segCount + 1, segments, res);

            // 前导零剪枝：如果当前段开头是 '0'，它只能单独作为 0，不能继续看后面的两位（如 "01"、"012"）
            if (s[startIndex] == '0') break;
        }
    }
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        if (s.size() < 4 || s.size() > 12) return res;
        vector<int> segments(4, 0); // 固定 4 段
        cutBest(s, 0, 0, segments, res);
        return res;
    }
};

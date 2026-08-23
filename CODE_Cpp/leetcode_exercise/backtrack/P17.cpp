#include "backtrack.h"

class Solution {
    string map[10] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

    void build(vector<string>& res, vector<char>& path, string& digits, int idx) {
        for(char c : map[digits[idx] - '0']) {
            path.push_back(c);
            if(idx == digits.size() - 1) {
                res.push_back(string(path.begin(), path.end()));
            }
            else build(res, path, digits, idx + 1);
            path.pop_back();
        }
    }
public:
    vector<string> letterCombinations(string digits) {
        vector<string> res;
        vector<char> path;
        if(digits.size() == 0) return res;
        build(res, path, digits, 0);
        return res;
    }
};

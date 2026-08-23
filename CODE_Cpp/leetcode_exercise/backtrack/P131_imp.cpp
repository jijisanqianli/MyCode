#include "backtrack.h"

class Solution {
    bool isPalindrome(string s, int l, int r) {
        while(l < r) {
            if (s[l]!=s[r]) return false;
            l++; r--;
        }
        return true;
    }

    void computePalindromeTable(string& s, vector<vector<bool>>& table) {
        for (int left = s.size()-1; left >= 0; left--) {
            for (int right = left; right < s.size(); right++) {
                if (s[left] == s[right] && (right-left <= 2 || table[left+1][right-1])) {
                    table[left][right] = true;
                }
            }
        }
    }

    void cut(string s, vector<vector<string>>& res, vector<string>& path, int startIndex) {
        for(int i = startIndex; i < s.size(); i++) {
            if(isPalindrome(s, startIndex, i)) {
                path.push_back(s.substr(startIndex, i-startIndex+1));
                if(i == s.size()-1) res.push_back(path);
                cut(s, res, path, i+1);
                path.pop_back();
            }
        }
    }

    void cutBest(string s, vector<vector<string>>& res, vector<string>& path, int startIndex, vector<vector<bool>>& table) {
        for(int i = startIndex; i < s.size(); i++) {
            if(table[startIndex][i]) {
                path.push_back(s.substr(startIndex, i-startIndex+1));
                if(i == s.size()-1) res.push_back(path);
                cutBest(s, res, path, i+1, table);
                path.pop_back();
            }
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> path;
        vector<vector<bool>> tableIsPalindrome(s.size(), vector<bool>(s.size(), false));
        computePalindromeTable(s, tableIsPalindrome);
        cutBest(s, res, path, 0, tableIsPalindrome);
        return res;
    }
};

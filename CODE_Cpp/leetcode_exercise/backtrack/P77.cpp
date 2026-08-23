#include "backtrack.h"

class Solution {
    void addNewNum(vector<int>& cur, vector<vector<int>>& result, int n, int k, int start) {
        if(cur.size()==k) {
            result.push_back(cur);
            return;
        }
        for(int i=start; i<=n - (k - cur.size()) + 1; i++) {
            cur.push_back(i);
            addNewNum(cur, result, n, k, i+1);
            cur.pop_back();
        }
    }
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> result;
        vector<int> cur;
        cur.reserve(k);
        addNewNum(cur, result, n, k, 1);
        return result;
    }
};
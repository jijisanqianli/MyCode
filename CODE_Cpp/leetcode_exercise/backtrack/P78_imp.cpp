#include "backtrack.h"

class Solution {
    void addNum(vector<int>& nums, vector<vector<int>>& res, vector<int>& cur, int idx) {
        if (idx == nums.size()) {
            res.push_back(cur);
            return;
        }
        addNum(nums, res, cur, idx+1);
        cur.push_back(nums[idx]);
        addNum(nums, res, cur, idx+1);
        cur.pop_back();
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> cur;
        addNum(nums, res, cur, 0);
        return res;
    }
    // 重点主要就是这个迭代,只用复习这个迭代
    vector<vector<int>> subsetsIterative(vector<int>& nums) {
        vector<vector<int>> res={{}};
        for(int num: nums) {
            int n = res.size();
            for(int i=0; i<n; i++) {
                vector<int> tmp = res[i];
                tmp.push_back(num);
                res.push_back(move(tmp));
            }
        }
        return res;
    }
};

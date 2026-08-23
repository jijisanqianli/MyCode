#include "backtrack.h"

//重点在于去重不能再使用排序了，因为要保留原顺序，所以用数组哈希去重

class Solution {
    void addNum(vector<int>& nums, int start, vector<int>& path, vector<vector<int>>& res) {
        if(path.size() >= 2) res.push_back(path);
        bool used[201] = {false};
        for(int i = start; i < nums.size(); i++) {
            if (used[nums[i]+100]) continue;
            if(path.empty() || nums[i] >= path.back()) {
                path.push_back(nums[i]);
                used[nums[i]+100] = true;
                addNum(nums, i+1, path, res);
                path.pop_back();
            }
        }
    }

public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> path;
        addNum(nums, 0, path, res);
        return res;
    }
};

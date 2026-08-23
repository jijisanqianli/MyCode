#include "backtrack.h"

class Solution {
    void addNum(vector<int>& nums, vector<int>& sequence, vector<vector<int>>& res) {
        if (sequence.size() == nums.size()) {
            res.push_back(sequence);
            return;
        }
        bool used[21] = {false};
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i]==INT_MIN) continue;
            if (used[nums[i] + 10]) continue;
            sequence.push_back(nums[i]);
            used[nums[i] + 10] = true;
            int temp = nums[i];
            nums[i] = INT_MIN;
            addNum(nums, sequence, res);
            nums[i] = temp;
            sequence.pop_back();
        }
    }
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> sequence;
        addNum(nums, sequence, res);
        return res;
    }
};

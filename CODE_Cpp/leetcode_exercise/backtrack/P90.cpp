#include "backtrack.h"

class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        vector<int> cur;
        res.push_back(cur);
        int record_start = 0,last_num = INT_MIN;
        for(int i = 0; i < nums.size(); i++) {
            if (nums[i] != last_num) record_start = 0;
            int len = res.size();
            for (int j = record_start; j < len; j++) {
                vector<int> tmp = res[j];
                tmp.push_back(nums[i]);
                res.push_back(tmp);
            }
            record_start = len;
            last_num = nums[i];
        }
        return res;
    }
};

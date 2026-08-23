#include "backtrack.h"

class Solution {
    void build(vector<int>& candidates, vector<vector<int>>& res, vector<int>& path, int target, int sum, int start = 0) {
        for(int i = start; i < candidates.size(); i++) {
            if(sum + candidates[i] > target) return;
            path.push_back(candidates[i]);
            sum += candidates[i];
            if(sum == target) {
                res.push_back(path);
                path.pop_back();
                sum -= candidates[i];
                return;
            }
            build(candidates, res, path, target, sum, i);
            path.pop_back();
            sum -= candidates[i];
        }
    }
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        sort(candidates.begin(), candidates.end());
        build(candidates, res, path, target, 0);
        return res;
    }
};

#include "backtrack.h"

class Solution {
    void build(vector<int>& candidates, vector<vector<int>>& res, vector<int>& path, int target, int sum, int start = 0) {
        int i = start;
        while(i < candidates.size()) {
            if(sum + candidates[i] > target) return;
            path.push_back(candidates[i]);
            sum += candidates[i];
            if(sum == target) {
                res.push_back(path);
                path.pop_back();
                sum -= candidates[i];
                return;
            }
            build(candidates, res, path, target, sum, i+1);
            path.pop_back();
            sum -= candidates[i];
            while(i+1 < candidates.size() && candidates[i+1] == candidates[i]) i++;
            i++;
        }
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        sort(candidates.begin(), candidates.end());
        build(candidates, res, path, target, 0);
        return res;
    }
};

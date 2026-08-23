#include "backtrack.h"

class Solution {
    void addNewNum(vector<vector<int>>& result, vector<int>& path, int k, int n, int start, int sum) {
        if (9-start+1 < k-path.size()) return;
        for(int i = start; i <= 9; i++) {
            if(sum + i > n) break;
            path.push_back(i);
            sum += i;
            if(path.size() == k) {
                if(sum == n) {
                    result.push_back(path);
                    path.pop_back();
                    sum -= i;
                    break;
                }
            }else {
                addNewNum(result, path, k, n, i+1, sum);
            }
            path.pop_back();
            sum -= i;
        }
    }
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> result;
        vector<int> path;
        addNewNum(result, path, k, n, 1, 0);
        return result;
    }
};

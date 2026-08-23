#include <deque>
#include <vector>
using namespace std;

class Solution {
public:
    void handle_push(deque<int>& record, int num, int& max) {
        if (num>max) {
            while (!record.empty()) {
                record.pop_back();
            }
            max=num;
            record.push_back(num);
        }else if (num<=record.back()) {
            record.push_back(num);
        }else if (num>record.back()) {
            while (num>record.back()) {
                record.pop_back();
            }
            record.push_back(num);
        }
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int max=-10001;
        vector<int> result;
        result.reserve(nums.size() - k + 1);
        deque<int> record;
        int left=0,right=k-1;
        for (int i=0;i<k;i++) {
            handle_push(record, nums[i], max);
        }
        while (true) {
            result.push_back(record.front());
            if (nums[left]==record.front()) {
                record.pop_front();
                max=record.front();
            }
            left++;
            right++;
            if (right>=nums.size()) return result;
            handle_push(record, nums[right], max);
        }
    }

    vector<int> maxSlidingWindowFinal(vector<int>& nums, int k) {
        vector<int> result;
        result.reserve(nums.size() - k + 1);
        deque<int> record;
        for (int i=0;i<nums.size();i++) {
            if (!record.empty() && record.front()<=i-k) {
                record.pop_front();
            }
            while (!record.empty() && nums[record.back()]<=nums[i]) {
                record.pop_back();
            }
            record.push_back(i);
            if (i>=k-1) {
                result.push_back(nums[record.front()]);
            }
        }
        return result;
    }
};

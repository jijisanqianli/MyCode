
#include <vector>
using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int now=0,before=0;
        int count=0,num_size=nums.size();
        while(before<num_size) {
            if(nums[before]==val) {
                count++;
                before++;
                continue;
            }
            nums[now]=nums[before];
            before++;
            now++;
        }
        return num_size-count;
    }
};

#include <algorithm>
#include <string>
using namespace std;

class Solution {
public:
    string reverseWordsInitial(string s) {
        string result;
        int begin = 0, right = s.size() - 1;
        while (begin<right && s[begin] == ' ') begin++;
        while (begin<right && s[right] == ' ') right--;
        int left=right;
        while (left >= begin) {
            while (left >= begin && s[left] != ' ') left--;
            result.append(&s[left + 1],right-left);
            if (left!=begin-1) result.append(" ");
            while (left >= begin && s[left] == ' ') left--;
            right = left;
        }
        return result;
    }

    string reverseWords(string s) {
        int slow = 0, fast = 0;
        while (fast < s.size()) {
            while (fast < s.size() && s[fast] == ' ') fast++;
            if (fast < s.size() && slow>0) {
                s[slow] = ' ';
                slow++;
            }
            while (fast < s.size() && s[fast] != ' ') {
                s[slow]=s[fast];
                slow++;fast++;
            }
        }
        s.resize(slow);
        reverse(s.begin(), s.end());
        int left=0,right=0;
        while (right<slow) {
            while (right<slow && s[right] != ' ') right++;
            reverse(s.begin()+left, s.begin()+right);
            left=right+1;
            right=left;
        }
        return s;
    }
};

#include <string>
#include <stack>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
                st.push(s[i]);
            }else {
                if (st.empty()) return false;
                char c = st.top();
                if (s[i] == ')' && c == '(') st.pop();
                else if (s[i] == ']' && c == '[') st.pop();
                else if (s[i] == '}' && c == '{') st.pop();
                else return false;
            }
        }
        return st.empty();
    }
};

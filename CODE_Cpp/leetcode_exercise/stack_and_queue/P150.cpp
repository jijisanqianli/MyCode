#include <string>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        if(tokens.empty()) return 0;
        stack<int> st;
        for (int i = 0; i < tokens.size(); i++) {
            if(!isOperator(tokens[i])) {
                st.push(stoi(tokens[i]));
            }else {
                int a = st.top(); st.pop();
                int b = st.top(); st.pop();
                st.push(calculate(b, a, tokens[i]));
            }
        }
        return st.top();
    }

    bool isOperator(string& s) {
        return s == "+" || s == "-" || s == "*" || s == "/";
    }

    int calculate(int a, int b, string& op) {
        if(op == "+") return a + b;
        if(op == "-") return a - b;
        if(op == "*") return a * b;
        if(op == "/") return a / b;
        return 0;
    }
};

#include <queue>
using namespace std;

class MyStack {
    queue<int> q1;
    queue<int> q2;
public:
    MyStack() {

    }

    void push(int x) {
        if (!q1.empty()) {
            q1.push(x);
        }else {
            q2.push(x);
        }
    }

    int pop() {
        int result;
        if (!q1.empty()) {
            while (q1.size() > 1) {
                q2.push(q1.front());
                q1.pop();
            }
            result = q1.front();
            q1.pop();
        }else {
            while (q2.size() > 1) {
                q1.push(q2.front());
                q2.pop();
            }
            result = q2.front();
            q2.pop();
        }
        return result;
    }

    int top() {
        int result;
        if (!q1.empty()) {
            while (q1.size() > 1) {
                q2.push(q1.front());
                q1.pop();
            }
            result = q1.front();
            q1.pop();
            q2.push(result);
        }else {
            while (q2.size() > 1) {
                q1.push(q2.front());
                q2.pop();
            }
            result = q2.front();
            q2.pop();
            q1.push(result);
        }
        return result;
    }

    bool empty() {
        return q1.empty() && q2.empty();
    }
};
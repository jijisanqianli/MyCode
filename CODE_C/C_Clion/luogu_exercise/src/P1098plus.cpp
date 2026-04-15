#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

bool is_letter(char c) {
    return (c >= 'a' && c <= 'z');
}

bool is_number(char c) {
    return (c >= '0' && c <= '9');
}

bool is_same_type(char c1, char c2) {
    return (is_letter(c1) && is_letter(c2)) || (is_number(c1) && is_number(c2));
}

char get_char(char c, int p1) {
    if (p1 == 3) return '*';
    if (p1 == 2 && is_letter(c)) return c - 32;
    return c;
}

int main () {
    int p1,p2,p3;
    cin>>p1>>p2>>p3;
    string s;
    cin>>s;
    string result;
    for (int i=0;i<s.length();i++) {
        if (s[i] == '-' && i > 0 && i < s.size()-1) {
            if (is_same_type(s[i-1],s[i+1])&&s[i-1]<s[i+1]) {
                string middle;
                char begin=s[i-1],end=s[i+1];
                for (char c=begin+1;c<end;c++) {
                    char c_fill=get_char(c,p1);
                    for (int j=0;j<p2;j++) {
                        middle+=c_fill;
                    }
                }
                if (p3==2) {
                    reverse(middle.begin(),middle.end());
                }
                result+=middle;
            }else {
                result+=s[i];
            }
        }else {
            result+=s[i];
        }
    }
    cout<<result;
}

#include <stdio.h>
#include <stdlib.h>

void process(int target) {
    int w = 0, l = 0;
    char ch;
    
    while ((ch = getchar()) != 'E') {
        if (ch == 'W') w++;
        else if (ch == 'L') l++;
        else continue;
        
        if ((w >= target || l >= target) && abs(w - l) >= 2) {
            printf("%d:%d\n", w, l);
            w = l = 0;
        }
    }
    printf("%d:%d\n\n", w, l);
}

int main() {
    process(11);
    process(21);
    return 0;
}
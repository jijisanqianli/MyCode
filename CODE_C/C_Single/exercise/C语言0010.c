#include <stdio.h>
#include <string.h>

int main() 
{
    char buf[1024];
    fgets(buf, sizeof(buf), stdin);
    buf[strcspn(buf, "\n")] = '\0';
    puts(buf);
    puts(buf);
    return 0;
}
#include <stdio.h>

int main() {
    char source[] = "Hello, World! This is a test string for my_strcpy function.\n";
    char destination[101];
    
    for(int i = 0; i < 101; i++)
    {
        if (source[i] != 0)
        {
            destination[i] = source[i];
        }
        else
        {
            destination[i] = 0;
            break;
        }
    }

    
    printf("拷贝后的字符串: %s", destination);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个 key = name, value = John
 */

int parse_url(const char* url) {
    int err = 0;

    int i = 0;
    while (url[i] != 0 && url[i] != '?') i++;
    i++;
    int toggleKey = 0;

    printf("key = ");
    while (url[i] != 0)
    {
        if (url[i] == '&') {
            toggleKey = 0;
            putc('\n', stdout);
            printf("key = ");
        }
        else if (url[i] == '=')
        {
            printf(", ");
            printf("value = ");
        }
        else if (url[i] == '+')
        {
            printf(" ");
        }
        else
        {
            putc(url[i], stdout);
        }
        i++;
    }
    return 0;

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}
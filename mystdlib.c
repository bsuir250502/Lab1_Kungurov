#define MYSTDLIB_H_INCLUDED
#include "mystdlib.h"
int mystrcmp(char *str1, char *str2)
{
    while (*str1 && *str2 && (*str1 == *str2)) {
        str1++;
        str2++;
    };
    return *str1 - *str2;
}

void mystrcpy(char *str1, char *str2)
{
    int i = 0;
    while (str2[i]) {
        str1[i] = str2[i];
        i++;
    }
    str1[i] = '\0';
}

int myatoi(char *str)
{
    int n, i = 0, sign;
    while (*(str + i) == ' ')
        i++;
    if (!*(str + i))
        return 0;
    sign = (*(str + i) == '-') ? -1 : 1;
    if (*(str + i) == '+' || *(str + i) == '-')
        i++;
    for (n = 0; *(str + i) >= '0' && *(str + i) <= '9'; i++)
        n = 10 * n + (*(str + i) - '0');
    return sign * n;
}

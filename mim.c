#include <stdio.h>

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        i++;
    }
    return (i);
}

int main()
{
    int num = ft_strlen("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_");
    printf("%d", num);
    return (0);
}
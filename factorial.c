#include <stdio.h>

int fun(int n)
{
    if (n == 0)

        return 1;

    else

        return fun(n - 1) * n;
}
int main()
{
    int r;
    r = fun(7);
    printf("%d\n", r);
    return 0;
}
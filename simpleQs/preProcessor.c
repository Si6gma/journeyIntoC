#include <stdio.h>

#define sqr(a) (a * a)

int main()
{
    int num = 5;
    int b = 4;
    int square = sqr(num - b);
    // 5 - 4 * 5 - 4 == 5 - (4 * 5) - 4

    printf("Square is: %d \n", square);
}

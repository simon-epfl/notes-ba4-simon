#include <math.h>
#include <stdio.h>
#include <stdbool.h>

void swap(int* a, int* b);

int main(void)
{
    int i = 10;
    int j = 55;
    printf("Before: i=%d and j=%d\n", i, j);
    swap(&i, &j);
    printf("After: i=%d and j=%d\n", i, j);
    return 0;
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

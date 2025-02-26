#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int g = 3;

void foo()
{
    // g--; // (1)
    if (g > 0)
    {
        puts("Hello");
        int f = fork();
        if (f == 0)
        {
            foo();
        }
        g--; // (2)
        waitpid(f, NULL, 0);
        exit(0);
    }
}
int main()
{
    int f = fork();
    if (f == 0)
    {
        foo();
    }
    waitpid(f, NULL, 0);
    printf("World\n");
    exit(0);
}

#include <stdio.h>
#include <string.h>

int main(void)
{
    FILE *fp;
    char name[1024];
    unsigned int age;

    fp = fopen("data.dat", "w");
    if (fp == NULL) return 1;
    
    while (1) {
        printf("Enter a name (CTRL+D to finish): ");
        fflush(stdout);
    
        if (fgets(name, 1024, stdin) == NULL) break;
        name[strcspn(name, "\n")] = '\0';
        
        printf("Age: ");
        fflush(stdout);

        if (scanf("%u", &age) != 1) {
            printf("I'm asking you for an age (positive integer)!\n");
            printf("This registration is cancelled.\n");
            // No need to call `fflush` because it is automatically flushed when `\n` is printed

            while (getchar() != '\n');
            continue;
        }

        fprintf(fp, "%s %d\n", name, age);
    }

    fputc('\n', fp);
    fclose(fp);

    return 0;
}

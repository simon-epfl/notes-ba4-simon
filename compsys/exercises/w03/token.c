#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 500

int nextToken(char const * str, size_t* from, size_t* len) {
    bool isWordStarted = false;
    //printf("len is=%lu", *len);
    for (size_t i = *from; i < *len; i++) {
        const char currentChar = str[i];
        if (currentChar != ' ' && currentChar != '\0' && !isWordStarted) {
            printf("starting word, setting from =%lu", i);
            isWordStarted = true;
            *from = i;
        }
        if (currentChar == ' ' || currentChar == '\0') {
            printf("found space at i=%lu.", i);
            if (isWordStarted) {
                *len = i - *from;
                printf("ending word at length=%lu", *len);
                return 1;
            }
        }
    }
    return 0;
}

int main () {
    char line_to_read[MAX_SIZE];
    fgets(line_to_read, MAX_SIZE, stdin);

    size_t rLen = strlen(line_to_read);
    if ((rLen != 0) && (line_to_read[--rLen] == '\n')) {
        line_to_read[rLen] = '\0';
    }

    size_t fromInitial = 0;
    size_t* from = &fromInitial;
    size_t lenCst = rLen +1;
    size_t* len = &lenCst;

    while (nextToken(line_to_read, from, len) > 0) {
        printf("new word starting from %lu\n", *from);

        printf("'");
        for (size_t i = *from; i < (*from + *len); i++) {
            printf("%c", line_to_read[i]);
        }
        printf("'\n");
        *from = *from + *len;
        size_t newLenCst = rLen +1;
        *len = newLenCst;
    }
}
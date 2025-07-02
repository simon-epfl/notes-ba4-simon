#include <stdlib.h>
#include <stdio.h>

enum Gender {
    Mr,
    Ms
};

void generateLetter(
    enum Gender gender,
    char recipient[],
    char subject[],
    int day,
    int month,
    char polite[],
    char author[]
) {


    printf("Dear %s %s,\n", gender == Mr ? "Mr." : "Ms.", recipient);
    printf("I am writing to you regarding %s.\n", subject);
    printf("We should see each other on %d/%d to discuss it.\n", day, month);
    puts("Let me know!");
    printf("%s, %s", polite, author);

}

int main(void) {

    generateLetter(Mr, "recip1", "subj1", 5, 6, "polite1", "author1");

}

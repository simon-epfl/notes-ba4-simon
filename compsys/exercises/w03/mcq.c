#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_QUESTION_LENGTH 1000

typedef struct {
    char* question;
    char* reponses[10];
    unsigned int nb_rep;
    unsigned int solution;
} MCQ;

typedef MCQ** Exam;

void display(const MCQ* mcq) {
    printf("%s", mcq->question);
    for (int i = 0; i < mcq->nb_rep; i++) {
        printf("%s", mcq->reponses[i]);
    }
}

int ask_number(int min, int max) {
    int nb = 0.0;
    int j = 0;
    do {
        printf("Entrez un nombre entre %d et %d: ", min, max);
        j = scanf("%d", &nb);
        if (j != 1) {
            printf("Ce n'est pas une réponse valide.\n");
            // clear stdin
            while (!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
        }
    } while (!feof(stdin) && !ferror(stdin) && ((j!=1) || (nb<min) || (nb>max)));
    return nb;
}

unsigned int ask_question(const MCQ* mcq) {
    printf("%s\n", mcq->question);
    for (int i = 0; i < mcq->nb_rep; i++) {
        printf("  %d - %s\n", i, mcq->reponses[i]);
    }
    int answer = ask_number(0, mcq->nb_rep);
    return answer;
}

MCQ** create_examination() {
    MCQ** back = calloc(3, sizeof(MCQ*));
    back[0] = malloc(sizeof(MCQ));
    back[1] = malloc(sizeof(MCQ));
    back[2] = malloc(sizeof(MCQ));
    
    (*back)[0].question = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    strcpy((*back)[0].question,
    "How many teeth does an adult elephant have");
    (*back)[0].nb_rep = 5;
    for (int i = 0; i < (*back)[0].nb_rep; i++) {
        (*back)[0].reponses[i] = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    }
    strcpy((*back)[0].reponses[0], "32");
    strcpy((*back)[0].reponses[1], "from 6 to 10");
    strcpy((*back)[0].reponses[2], "a lot");
    strcpy((*back)[0].reponses[3], "24");
    strcpy((*back)[0].reponses[4], "2");
    (*back)[0].solution = 2;

    (*back)[1].question = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    strcpy((*back)[1].question,
    "Which of the following statements is a function prototype");
    (*back)[1].nb_rep = 4;
    for (int i = 0; i < (*back)[1].nb_rep; i++) {
        (*back)[1].reponses[i] = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    }
    strcpy((*back)[1].reponses[0], "int f(0);");
    strcpy((*back)[1].reponses[1], "int f(int 0);");
    strcpy((*back)[1].reponses[2], "int f(int i);");
    strcpy((*back)[1].reponses[3], "int f(i);");
    (*back)[1].solution = 3;

    (*back)[2].question = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    strcpy((*back)[2].question,
    "Who asks stupid questions");
    (*back)[2].nb_rep = 7;
    for (int i = 0; i < (*back)[2].nb_rep; i++) {
        (*back)[2].reponses[i] = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    }
    strcpy((*back)[2].reponses[0], "the math prof.");
    strcpy((*back)[2].reponses[1], "my boyfriend/girlfriend");
    strcpy((*back)[2].reponses[2], "the physics prof.");
    strcpy((*back)[2].reponses[3], "me");
    strcpy((*back)[2].reponses[4], "the programming prof.");
    strcpy((*back)[2].reponses[5], "no one, there are no stupid questions");
    strcpy((*back)[2].reponses[6], "polls");
    (*back)[2].solution = 6;

    return back;
}

void destroy_examination(Exam* exam){
    free(exam);
}

int main() {

    MCQ** exam = create_examination();
    int tot = 0;
    
    for (int i = 0; i < 3; i++) {
        const MCQ mcq = (*exam)[i];
        int res = ask_question(&mcq);
        if (res == mcq.solution) {
            tot++;
        }
    }

    printf("%d", tot);

}


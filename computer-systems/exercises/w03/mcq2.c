#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_QUESTION_LENGTH 1000
#define NB_DEMANDES 3

typedef struct {
    char* question;
    char* reponses[10];
    unsigned int nb_rep;
    unsigned int solution;
} MCQ;

typedef MCQ* Exam;

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

void create_examination(Exam* back, FILE* file) {

    *back = NULL;

    int i = 0;

    char content[MAX_QUESTION_LENGTH];
    int nb_rep = 0;

    bool questionRead = false;
    while(fgets(content, MAX_QUESTION_LENGTH, file)) {
        //printf("%s", content);
        //fflush(stdout);
        if (!questionRead && content[0] == 'Q' && content[1] == ':') {
            questionRead = true;

            /* INIT MEMORY */
            *back = realloc(*back, sizeof(MCQ) * (i + 1));
            (*back)[i].question = calloc(MAX_QUESTION_LENGTH, sizeof(char));
            for (int k = 0; k < 10; k++) {
                (*back)[i].reponses[k] = calloc(MAX_QUESTION_LENGTH, sizeof(char));
            }

            /* COPY QUESTION */
            strcpy((*back)[i].question, content);
        } else {
            if (content[0] == '\n') {
                //printf("end of question!");
                questionRead = false;
                (*back)[i].nb_rep = nb_rep;
                i = i + 1;
                nb_rep = 0;
            } else {
                if (content[0] == '-' && content[1] == '>') {
                    (*back)[i].solution = nb_rep;
                    //printf("found answer!");
                    //printf("i=%d, nb_rep=%d", i, nb_rep);
                    //fflush(stdout);
                    char* ptr_to_content = content;
                    ptr_to_content += 2;
                    strcpy((*back)[i].reponses[nb_rep], ptr_to_content);
                } else {
                    char* ptr_to_content = content;
                    //printf("%d", *ptr_to_content == ' ');
                    while (*ptr_to_content == ' ') ptr_to_content = ptr_to_content + 1;
                    //fflush(stdout);
                    strcpy((*back)[i].reponses[nb_rep], ptr_to_content);
                }
                nb_rep++;
            }
        }
        //printf("%s", content);
        //fflush(stdout);
    }
    //printf("save last question!");
    (*back)[i].nb_rep = nb_rep;

    // (*back)[0].question = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    // strcpy((*back)[0].question,
    // "How many teeth does an adult elephant have");
    // (*back)[0].nb_rep = 5;
    // for (int i = 0; i < (*back)[0].nb_rep; i++) {
    //     (*back)[0].reponses[i] = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    // }
    // strcpy((*back)[0].reponses[0], "32");
    // strcpy((*back)[0].reponses[1], "from 6 to 10");
    // strcpy((*back)[0].reponses[2], "a lot");
    // strcpy((*back)[0].reponses[3], "24");
    // strcpy((*back)[0].reponses[4], "2");
    // (*back)[0].solution = 2;

    // (*back)[1].question = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    // strcpy((*back)[1].question,
    // "Which of the following statements is a function prototype");
    // (*back)[1].nb_rep = 4;
    // for (int i = 0; i < (*back)[1].nb_rep; i++) {
    //     (*back)[1].reponses[i] = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    // }
    // strcpy((*back)[1].reponses[0], "int f(0);");
    // strcpy((*back)[1].reponses[1], "int f(int 0);");
    // strcpy((*back)[1].reponses[2], "int f(int i);");
    // strcpy((*back)[1].reponses[3], "int f(i);");
    // (*back)[1].solution = 3;

    // (*back)[2].question = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    // strcpy((*back)[2].question,
    // "Who asks stupid questions");
    // (*back)[2].nb_rep = 7;
    // for (int i = 0; i < (*back)[2].nb_rep; i++) {
    //     (*back)[2].reponses[i] = calloc(MAX_QUESTION_LENGTH, sizeof(char));
    // }
    // strcpy((*back)[2].reponses[0], "the math prof.");
    // strcpy((*back)[2].reponses[1], "my boyfriend/girlfriend");
    // strcpy((*back)[2].reponses[2], "the physics prof.");
    // strcpy((*back)[2].reponses[3], "me");
    // strcpy((*back)[2].reponses[4], "the programming prof.");
    // strcpy((*back)[2].reponses[5], "no one, there are no stupid questions");
    // strcpy((*back)[2].reponses[6], "polls");
    // (*back)[2].solution = 6;

}

void destroy_examination(Exam* exam){
    for (int i = 0; i < 3; i++) {
        MCQ mcq = (*exam)[i];
        for (int j = 0; j < mcq.nb_rep; j++) {
            free(mcq.reponses[j]);
        }
        free(mcq.question);
    }
    free(*exam);
}

int main() {

    FILE* entree = NULL;
    char nom_entree[FILENAME_MAX+1] = "data.dat";
    entree = fopen(nom_entree, "r");

    Exam exam = NULL;
    create_examination(&exam, entree);
    int tot = 0;
    
    for (int i = 0; i < 3; i++) {
        const MCQ mcq = (exam)[i];
        int res = ask_question(&mcq);
        if (res == mcq.solution) {
            tot++;
        }
    }

    printf("%d\n\n", tot);

    destroy_examination(&exam);

}

FILE* demander_fichier(void)
{
  FILE* f = NULL;
  char nom_fichier[FILENAME_MAX+1];
  size_t taille_lue = 0;
  unsigned short int nb = 0;

  do {
    ++nb;

    /* demande le nom du fichier */
    do {
      printf("Nom du fichier à lire : "); fflush(stdout);
      fgets(nom_fichier, FILENAME_MAX+1, stdin);
      taille_lue = strlen(nom_fichier);
      if ((taille_lue >= 1) && (nom_fichier[taille_lue-1] == '\n'))
        nom_fichier[--taille_lue] = '\0';
    } while ((taille_lue == 0) && !feof(stdin));

    if (nom_fichier[0] == '\0') {
      return NULL;
    }

    /* essaye d'ouvrir le fichier */
    f = fopen(nom_fichier, "r");

    /* est-ce que ça a marché ? */
    if (f == NULL) {
      printf("-> ERREUR, je ne peux pas lire le fichier \"%s\"\n",
             nom_fichier);
    } else {
      printf("-> OK, fichier \"%s\" ouvert pour lecture.",
             nom_fichier);
    }
  } while ((f == NULL) && (nb < NB_DEMANDES));
  
  /* la valeur de retour est le résultat du test entre (): 0 ou 1 */
  return f;
}

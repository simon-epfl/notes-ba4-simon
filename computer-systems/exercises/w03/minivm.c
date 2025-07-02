#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_SIZE 500

typedef void (*Command)(void *);

void command(void *data)
{
    puts("test!");
}

void print(void *data)
{
    double * values = data;
    printf("%f", values[0]);
    printf("c'est un print!\n");
}

void quit(void *data) {
    printf("Bye!");
    exit(0);
}

Command interpreter(const char *v)
{
    if (!strncmp(v, "print", 5))
    {
        return print;
    } else if (!strncmp(v, "quit", 4)) {
        return quit;
    }

    return print;
}

int main()
{

    double values[2] = {0};

    while (true)
    {
        char text[MAX_SIZE];
        printf("Enter a command (print, add, push, pop, quit) :");
        fgets(text, MAX_SIZE, stdin);

        size_t len = strlen(text);
        if ((len != 0) && (text[--len] == '\n'))
        {
            text[len] = '\0';
        }

        interpreter(text)(values);

    }
}

/*
#include <stdio.h>
#include <string.h>

typedef void (*Cmd)(void* data);

// Notre machine simpliste
void print(void* data);
void add(void* data);
void push(void* data);
void pop(void* data);
void quit(void* data);

Cmd interprete(const char* nom_commande);

// ----------------------------------------------------------------------
int main(void)
{
  double registres[] = { 0.0, 0.0 };

  Cmd cmd = quit;
  do {
    char lu[] = "nom de la plus longue commande";
    printf("Entrez une commande (print, add, push, pop, quit) : ");
    scanf("%s", lu);
    (cmd = interprete(lu))(registres);
  } while (cmd != quit);
  
  return 0;
}

// ----------------------------------------------------------------------
Cmd interprete(const char* nom)
{
  if (nom == NULL) return quit;
  
  if ( ! strcmp(nom, "print") ) {
    return print;
  } else
  if ( ! strcmp(nom, "add") ) {
    return add;
  } else
  if ( ! strcmp(nom, "push") ) {
    return push;
  } else
  if ( ! strcmp(nom, "pop") ) {
    return pop;
  } 
  return quit;
}

// ----------------------------------------------------------------------
void print(void* data)
{
  const double * const px = data;
  printf("-> %g\n", *px);
}

// ----------------------------------------------------------------------
void add(void* data)
{
  double * const regs = data;
  regs[0] += regs[1];
}

// ----------------------------------------------------------------------
void push(void* data)
{
  double * const regs = data;
  regs[1] = regs[0];
  printf("Valeur ? ");
  scanf("%lf", regs);
}
  
// ----------------------------------------------------------------------
void pop(void* data)
{
  double * const regs = data;
  regs[0] = regs[1];
}

// ----------------------------------------------------------------------
void quit(void* useless)
{
  puts("Bye!");
}
*/
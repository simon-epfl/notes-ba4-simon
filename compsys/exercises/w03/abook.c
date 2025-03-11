#include <stdlib.h>

#define MAX_LENGTH 1000

/* a node of the tree */
typedef struct addr__ addr_t;
struct addr__
{
    char* name;
    int phoneNumber[10];
};
/* the tree, defined by its root */
typedef struct book__
{
    addr_t *root;
    size_t size;
} book_t;
/* create a new empty address book */
book_t *book_create(void);
/* release associated resources */
void book_free(book_t *b);
/* list in order all the names in the address book */
void book_list(book_t *b);
/* display an address book entry */
void book_view(book_t *b, const char *name);
/* add or modify an address book entry */
void book_add(book_t *b, const char *name, const char *num);
/* delete an entry from the address book */
void book_remove(book_t *b, const char *name);
/* replace the contents of the address book with those of the file */
void book_load(book_t *b, const char *file);
/* save the contents of the notebook in a CSV format file */
void book_save(book_t *b, const char *file);

book_t* book_create() {
    book_t* book = malloc(sizeof(book_t));
    return book;
}

void book_free(book_t* b) {
    for (int i = 0; i < b->size; i++) {
        free(b->root);
    }
}


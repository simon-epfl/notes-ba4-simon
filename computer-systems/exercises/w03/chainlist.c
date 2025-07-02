#include <stdlib.h>
#include <stdio.h>

typedef int type_el;

typedef struct _linked_list_node {
    type_el value;
    struct _linked_list_node* previous_element; 
} ChainListElement;

int insert_after_element(const type_el* to_insert, const type_el* after_el, ChainListElement** first_el);
int insert_at_head(const type_el* to_insert, ChainListElement** first_el);
int remove_head_from_list(const type_el* to_remove, ChainListElement** first_el);
int remove_from_list(const type_el* to_remove, ChainListElement* first_el);
int compute_length(const ChainListElement* first_el);

// returns 1 if the operation is successful
int insert_after_element(const type_el* to_insert, const type_el* after_el, ChainListElement** first_el) {
    ChainListElement** element = first_el;
    while (element != NULL && (*element)->previous_element != NULL && (*element)->value != *after_el) {
        element = &(*element)->previous_element;
    }
    if (element != NULL && (*element)->value == *to_insert) {
        ChainListElement* el = malloc(sizeof(ChainListElement));
        if (el != NULL) {
            el->value = *to_insert;
            if ((*element)->previous_element != NULL) {
                el->previous_element = (*element)->previous_element;
            }
            (*element)->previous_element = el;
            return 1;
        }
    }
    return 0;
}

int insert_at_head(const type_el* to_insert, ChainListElement** first_el) {
    ChainListElement* tmp_first_el = *first_el;
    *first_el = malloc(sizeof(ChainListElement));
    if (first_el != NULL) {
        (*first_el)->value = *to_insert;
        (*first_el)->previous_element = tmp_first_el;
        return 1;
    }
    return 0;
}

int remove_head_from_list(const type_el* to_remove, ChainListElement** list) {
    if (list == NULL) {
        ChainListElement* new_list = (*list)->previous_element;
        free(*list);
        *list = new_list;
        return 1;
    }
    return 0;
}

int compute_length(const ChainListElement* list) {
    size_t size = 0;
    const ChainListElement* el = list;
    while(el != NULL) {
        size += 1;
        el = list->previous_element;
    }
    return size;
}

int main() {

    ChainListElement* first_el = NULL;

    int to_add = 9;
    insert_at_head(&to_add, &first_el);
    printf("%d", compute_length(first_el));

}



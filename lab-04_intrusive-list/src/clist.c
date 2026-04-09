#include "clist.h"

#include <stdlib.h>

void init_list(struct intrusive_list *list) {
    list->head = NULL;
}

void add_node(struct intrusive_list *list, struct intrusive_node *node) {
    node->next = list->head;
    node->prev = NULL;
    if (list->head != NULL)
        (list->head)->prev = node;
    list->head = node;
}

int get_length(struct intrusive_list *list) {
    int len = 0;
    struct intrusive_node *current = list->head;
    while(current != NULL){
        len++;
        current = current->next;
    }
    return len;
}

void remove_node(struct intrusive_list *list, struct intrusive_node *node) {
    if (node == NULL) return;
    if (list->head == node){
        list->head = node->next;
        if (list->head != NULL)
            list->head->prev = NULL;
    } else {
        if (node->prev != NULL)
            node->prev->next = node->next;
        if (node->next != NULL)  
            node->next->prev = node->prev;
    }
    node->next = NULL;
    node->prev = NULL;   
}

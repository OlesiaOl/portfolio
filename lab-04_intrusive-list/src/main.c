#include "clist.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct point {
  int x, y;
  struct intrusive_node node;
};

void add_point(struct intrusive_list *list, int x, int y) {
  struct point *p = (struct point*)malloc(sizeof(struct point));
  if (p){
    p->x = x;
    p->y = y;
    add_node(list, &p->node);
  }
}

void remove_point(struct intrusive_list *list, int x, int y) { // removes all (x, y) pairs
  struct intrusive_node *current = list->head;
  while (current != NULL){
    struct intrusive_node *next = current->next;
    struct point *container = container_of(current, struct point, node);
    if (container->x == x && container->y == y) {
      remove_node(list, current);
      free(container);
    }
    current = next;
  }
}

void show_all_points(struct intrusive_list *list) {
  struct intrusive_node *current = list->head;
  while (current != NULL) {
    printf("(%d %d)", (container_of(current, struct point, node))->x, (container_of(current, struct point, node))->y);
    current = current->next;
    if (current != NULL)
      printf(" ");
  }
  printf("\n");
}

void remove_all_points(struct intrusive_list *list) {
  struct intrusive_node *current = list->head;
  while (current != NULL) {
    struct intrusive_node *next = current->next;
    remove_node(list, current);
    free(container_of(current, struct point, node));
    current = next;
  }
  list->head = NULL;
}

int main(void) {
    struct intrusive_list list;
    init_list(&list);
    while (1) {
        char com[10];
        if (scanf("%9s", com) != 1) {
            printf("Unknown command\n");
            continue;
        }
        if (strcmp(com, "add") == 0 || strcmp(com, "rm") == 0) {
            int x, y;
            if (strcmp(com, "add") == 0){
              scanf("%d %d", &x, &y);
              add_point(&list, x, y);
            } else {
              scanf("%d %d", &x, &y);
              remove_point(&list, x, y);
            }
        } else if (strcmp(com, "print") == 0) {
            show_all_points(&list);
        } else if (strcmp(com, "rma") == 0) {
            remove_all_points(&list);
        } else if (strcmp(com, "len") == 0) {
            printf("%d\n", get_length(&list));
        } else if (strcmp(com, "exit") == 0) {
            break;
        } else {
            printf("Unknown command\n");
        }
    }
    remove_all_points(&list);
    return 0;
}

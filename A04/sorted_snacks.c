/*----------------------------------------------
 * Author: Owen Yaggy
 * Date: 2/14/25
 * Description: Implements a program that allows
 * usersd to add snacks to the snackbar and then
 * displays them alphabetically
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// define a snack struct
struct snack {
  char name[32];
  float cost;
  int quantity;
};

struct node {
  struct snack *data;
  struct node *next;
};

void insert_first(struct node *head, struct snack *new_snack);

void clear(struct node *head);

void printList(struct node *head);

void printListHelper(struct node *head, int count);

void sortCost(struct node *head);

void sortName(struct node *head);

void sortQuantity(struct node *head);

void swap(struct node *head, struct node *new);

int main() {
  int count;
  struct node *head;
  head = NULL; // an empty linked list (textbook)
  head = malloc(sizeof(struct node));
  if (!head) {
    printf("Error malloc\n");
    exit(1);
  }
  head->next = NULL;
  printf("Enter a number of snacks: ");
  scanf("%d", &count);

  // prompt for attributes
  for (int i = 0; i < count; i++) {
    struct snack *new_snack;
    new_snack = NULL;
    new_snack = malloc(sizeof(struct snack));
    if (!new_snack) {
      printf("Malloc error\n");
      exit(1);
    }
    printf("Enter a name: ");
    scanf("%s", new_snack->name);
    printf("Enter a cost: ");
    scanf("%f", &new_snack->cost);
    printf("Enter a quantity: ");
    scanf("%d", &new_snack->quantity);
    if (i == 0) {
      head->data = new_snack;
    } else {
      insert_first(head, new_snack);
    }
  }
  
  printf("\nWelcome to Sorted Sally's Snack Bar.\n");

  // sort list by cost
  sortCost(head);
  printf("\nSorted by cost:\n");
  printList(head);

  // sort list by name
  sortName(head);
  printf("\nSorted by name:\n");
  printList(head);

  // sort list by quantity
  sortQuantity(head);
  printf("\nSorted by quantity:\n");
  printList(head);
  
  // clear list
  clear(head);

  return 0;
}

void insert_first(struct node *head, struct snack *new_snack) {
  struct node *temp;
  temp = NULL;
  temp = malloc(sizeof(struct node));
  if (!temp) {
    printf("Malloc error\n");
    exit(1);
  }
  temp->data = head->data;
  temp->next = head->next;
  head->data = new_snack;
  head->next = temp;
}

void clear(struct node *head) {
  if (head->next) {
    clear(head->next);
  }
  if (head->data) {
    free(head->data);
  }
  free(head);
}

void printList(struct node *head) {
  printListHelper(head, 0);
}

void printListHelper(struct node *head, int count) {
  printf("%d) %-12scost: $%-9.2fquantity: %d\n", count, head->data->name, head->data->cost, head->data->quantity);
  if (head->next) {
    printListHelper(head->next, ++count);
  }
}

void sortCost(struct node *head) {
  if (!head-> next) return;
  int length;
  length = 0;
  struct node *min;
  min = head;
  for (struct node *cur = head->next; cur; cur = cur->next) {
    if (cur->data->cost < min->data->cost) {
      min = cur;
    }
  }

  if (min != head) {
    swap(head, min);
  }

  sortCost(head->next);
}

void sortName(struct node *head) {
  if (!head-> next) return;
  int length;
  length = 0;
  struct node *min;
  min = head;
  for (struct node *cur = head->next; cur; cur = cur->next) {
    if (strcmp(cur->data->name, min->data->name) < 0) {
      min = cur;
    }
  }

  if (min != head) {
    swap(head, min);
  }

  sortName(head->next);
}

void sortQuantity(struct node *head) {
  if (!head-> next) return;
  int length;
  length = 0;
  struct node *min;
  min = head;
  for (struct node *cur = head->next; cur; cur = cur->next) {
    if (cur->data->quantity < min->data->quantity) {
      min = cur;
    }
  }

  if (min != head) {
    swap(head, min);
  }

  sortQuantity(head->next);
}

void swap(struct node *head, struct node *new) {
  struct snack *temp = head->data;
  head->data = new->data;
  new->data = temp;
}
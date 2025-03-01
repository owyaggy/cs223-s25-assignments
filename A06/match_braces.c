#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
  int row;
  int col;
  struct node *next;
};

void push(int new_row, int new_col, struct node *head);

int* pop(struct node *head);

void clearL(struct node *head);

void printL(struct node *head); 

void read_file(FILE *infile);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("usage: ./match_braces <program.c>\n");
    exit(1);
  }
  FILE *infile;
  infile = fopen(argv[1], "r");
  if (infile == NULL) {
    printf("Cannot open file: %s\n", argv[1]);
    exit(1);
  }
  read_file(infile);
  fclose(infile);
  return 0;
}

void push(int new_row, int new_col, struct node *head) {
  // create temp node to hold head (and whole stack)
  if (head->row < 0 || head->col < 0) {
    head->row = new_row;
    head->col = new_col;
    head->next = NULL;
    return;
  }
  struct node *temp;
  temp = NULL;
  temp = malloc(sizeof(struct node));
  if (!temp) {
    printf("Error: malloc failed\n");
    exit(1);
  }
  // give temp the head node's data
  temp->row = head->row;
  temp->col = head->col;
  temp->next = head->next;
  // put the new data into the head node
  // and have it point to the previous stack
  head->row = new_row;
  head->col = new_col;
  head->next = temp;
}

int* pop(struct node *head) {
  // change head to point to second node
  int *result;
  result = malloc(sizeof(int) * 2);
  if (!result) {
    printf("Error: malloc failed\n");
    exit(1);
  }
  if (!head) {
    return NULL;
  }
  if (head->row < 0 || head->col < 0) {
    head = NULL;
    return NULL;
  }
  if (!head->next) {
    result[0] = head->row;
    result[1] = head->col;
    head = NULL;
    return result;
  }
  result[0] = head->row;
  result[1] = head->col;
  void *ptr = head->next;
  head->row = head->next->row;
  head->col = head->next->col;
  head->next = head->next->next;
  free(ptr);
  return result;
}

void clearL(struct node *head) {
  if (!head) {
    return;
  }
  if (head->next) {
    clearL(head->next);
  }
  free(head);
  head = NULL;
}

void printL(struct node *head) {
  printf("|------------|\n|            |\n| (%3d, %3d) |\n|            |\n", head->row, head->col);
  if (!head->next) {
    printf("|------------|\n\n");
  } else {
    printL(head->next);
  }
}

void read_file(FILE *infile) {
  int next;
  int row = 1;
  int col = 0;
  struct node *head;
  int *matching;
  head = malloc(sizeof(struct node));
  if (!head) {
    printf("Error: malloc failed\n");
    exit(1);
  }
  head->row = -1;
  head->col = -1;
  for (int next = fgetc(infile); next != EOF; col++, next = fgetc(infile)) {
    if (next == '\n') {
      row++;
      col = 0;
      continue;
    }
    if (next == '{') {
      push(row, col, head);
    } else if (next == '}') {
      matching = pop(head);
      if (matching && matching[0] >= 0 && matching[1] >= 0) {
        printf("Found matching braces: (%d, %d) -> (%d, %d)\n", matching[0], matching[1], row, col);
      } else {
        printf("Unmatched brace on Line %d and Column %d\n", row, col);
      }
      free(matching);
    }
  }
  //clearL(head);
  matching = pop(head);
  while (matching) {
    if (matching[0] < 0 || matching[1] < 0) {
      break;
    }
    printf("Unmatched brace on Line %d and Column %d\n", matching[0], matching[1]);
    free(matching);
    matching = pop(head);
  }
  free(matching);
  clearL(head);
}
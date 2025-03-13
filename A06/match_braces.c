#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
  int row;
  int col;
  struct node *next;
};

void push(int new_row, int new_col, struct node **head);

unsigned long pop(struct node **head);

void clearL(struct node *head);

void printL(struct node *head); 

void read_file(FILE *infile);

int main(int argc, char *argv[]) {
  if (argc != 2) { // ensure correct number of args
    printf("usage: ./match_braces <program.c>\n");
    exit(1);
  }
  FILE *infile; // set infile
  infile = fopen(argv[1], "r"); // open file
  if (infile == NULL) { // check file opened successfully
    printf("Cannot open file: %s\n", argv[1]);
    exit(1);
  }
  read_file(infile); // run read_file function
  fclose(infile); // close file
  return 0;
}

unsigned long pop(struct node **head) {
  // check
  if (!(*head)) {
    printf("Pop was passed an empty stack!\n");
    exit(1);
  }
  // store info to return
  long rowcol = (*head)->row;
  rowcol = rowcol << 32;
  rowcol += (*head)->col;
  // pop element
  struct node *popped = (*head);
  (*head) = (*head)->next;
  free(popped);
  // return information
  return rowcol;
}

void push(int new_row, int new_col, struct node **head) {
  if (!(*head)) {
    *head = malloc(sizeof(struct node));
    if (!(*head)) {
      printf("Malloc failed!\n");
      exit(1);
    }
    (*head)->row = new_row;
    (*head)->col = new_col;
    (*head)->next = NULL;
  } else {
    struct node *temp = malloc(sizeof(struct node));
    if (!temp) {
      printf("Malloc failed!\n");
      exit(1);
    }
    temp->row = (*head)->row;
    temp->col = (*head)->col;
    temp->next = (*head)->next;
    (*head)->row = new_row;
    (*head)->col = new_col;
    (*head)->next = temp;
  }
}

void read_file(FILE *infile) {
  int ch = fgetc(infile);
  unsigned int row = 1;
  unsigned int col = 0;
  struct node *head = NULL;
  while (ch != EOF) {
    // check for special characters
    if (ch == '\n') {
      row++;
      col = 0;
    } else {
      // handle stack operations
      if (ch == '{') {
        push(row, col, &head);
      } else if (ch == '}') {
        if (!head) {
          printf("Unmatched brace on Line %d and Column %d\n", row, col);
        } else {
          unsigned long rowcol = pop(&head);
          unsigned int match_row = rowcol >> 32;
          unsigned int match_col = rowcol;
          printf("Found matching braces: (%d, %d) -> (%d, %d)\n", match_row, match_col, row, col);
        }
      }
    }
    // increment character
    ch = fgetc(infile);
    col++;
  }
  clearL(head);
}

void clearL(struct node *head) {
  if (!head) {
    return;
  }
  printf("Unmatched brace on Line %d and Column %d\n", head->row, head->col);
  if (head->next) {
    clearL(head->next);
  }
  free(head);
  head = NULL;
}

// this function not used, but kept according to assignment instructions
void printL(struct node *head) {
  printf("|------------|\n|            |\n| (%3d, %3d) |\n|            |\n", head->row, head->col);
  if (!head->next) {
    printf("|------------|\n\n");
  } else {
    printL(head->next);
  }
}
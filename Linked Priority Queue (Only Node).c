#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct PNode {
  int data;
  int priority;
  struct PNode* next;
};

struct PNode* newPNode (int data, int priority) {
  struct PNode* new = (struct PNode*) malloc (sizeof(struct PNode));
  new->data = data;
  new->priority = priority;
  new->next = NULL;
  return new;
}

bool isEmpty (struct PNode** head) {
  if ((*head) == NULL) return true;
  return false;
}

int peek (struct PNode** head) {
  return ((*head)->data);
}

void push (struct PNode** head, int data, int priority) {
  struct PNode* ref = (*head);
  struct PNode* new = newPNode(data, priority);

  if (ref->priority < priority && ref == NULL) {
    new->next = *head;
    (*head) = new;
  }
  else {
    while ((ref->next != NULL) && (ref->next->priority > priority)) {
      ref = ref->next;
    }
    new->next = ref->next;
    ref->next = new;
  }
}

void pop (struct PNode** head) {
  struct PNode* ref = (*head);
  (*head) = (*head)->next;
  free(ref);
}

void printPnewNode (struct PNode** head) {
  struct PNode* ref = (*head)->next;
  while (ref->next != NULL) {
    printf(" %d ", ref->data);
    ref = ref->next;
  }
  printf(" %d ", ref->data);
}

void main() {
  struct PNode* head = newPNode(-1, -1);

  push(&head, 2, 1);
  push(&head, 4, 1);
  push(&head, 4, 1);
  push(&head, 8, 1);
  push(&head, 16, 1);
  push(&head, 32, 1);

  push(&head, 3, 2);
  push(&head, 9, 2);
  push(&head, 27, 2);
  push(&head, 81, 2);
  
  push(&head, 0, 1);

  pop(&head);

  printPnewNode(&head);
  
  free(head);
}
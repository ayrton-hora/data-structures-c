  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>
  #include <assert.h>
  
struct Node {
  int data;
  struct Node* next;
  struct Node* prev;
};

void push (struct Node** head, int data) {
  struct Node* new = (struct Node*) malloc (sizeof(struct Node));
  new->data = data;
  new->next = *head;
  new->prev = NULL;

  if (*head != NULL) (*head)->prev = new;

  *head = new;
}

void insertAfter (struct Node* prev, int data) {
  if (prev == NULL) return;

  struct Node* new = (struct Node*) malloc (sizeof(struct Node));
  new->data = data;
  new->next = prev->next;
  prev->next = new;
  new->prev = prev;

  if (new->next != NULL) new->next->prev = new;
}

void append (struct Node** head, int data) {
  struct Node* new = (struct Node*) malloc (sizeof(struct Node));
  struct Node* last = *head;
  new->data = data;
  new->next = NULL;

  if (*head == NULL) {
    new->prev = NULL;
    *head = new;
    return;
  }
  while (last->next != NULL) last = last->next;

  last->next = new;
  new->prev = last;
  return;
}

void printList(struct Node* head) { 
  while (head != NULL) {
    printf(" %d ", head->data);  
    head = head->next;
  }
} 

void main() {
  struct Node* head = NULL;

  append(&head, 4);
  append(&head, 8);
  append(&head, 16);
  append(&head, 32);
  append(&head, 64);
  push(&head, 2);
  
  printList(head);

  free(head);
}
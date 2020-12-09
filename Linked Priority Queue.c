#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct PNode {
  int data;
  int priority;
  struct PNode* next;
};

struct PriorityQueue {
  struct PNode* front;
  struct PNode* rear; 
};

struct PriorityQueue* createPqueue () {
  struct PriorityQueue* queue = (struct PriorityQueue*) malloc (sizeof(struct PriorityQueue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

bool isEmpty (struct PriorityQueue** head) {
  if ((*head)->front == NULL) return true;
  return false;
}

void fixRear (struct PriorityQueue** head) {
  struct PNode* ref = (*head)->front;
  while (ref->next != NULL) {
    ref = ref->next;
  }
  (*head)->rear = ref;
}

int peek (struct PriorityQueue** head) {
  return ((*head)->front->data);
}

struct PNode* newPNode (int data, int priority) {
  struct PNode* new = (struct PNode*) malloc (sizeof(struct PNode));
  new->data = data;
  new->priority = priority;
  new->next = NULL;
  return new;
}

void push (struct PriorityQueue** head, int data, int priority) {
  struct PNode* front = (*head)->front;
  struct PNode* rear = (*head)->rear;
  struct PNode* new = newPNode(data, priority);

  if (front->priority < priority && front == NULL) {
    new->next = rear;
    (*head)->front = new;
    (*head)->rear = new;
  }
  // if (*front->priority > priority) {
  //   new->next = rear;
  //   (*head)->front = new;
  //   (*head)->rear = new;
  // }
  else {
    while ((front != rear) && (front->next->priority <= priority)) {
      front = front->next;
    }
    new->next = front->next;
    front->next = new;
    // rear = new;
  }
}

void pop (struct PriorityQueue** head) {
  struct PNode* ref = (*head)->front;
  (*head)->front = (*head)->front->next;
  ref->next = NULL;
  free(ref);
}

void printPqueue (struct PriorityQueue** head) {
  struct PNode* ref = (*head)->front;
  while (ref->next != NULL) {
    printf(" %d ", ref->data);
    ref = ref->next;
  }
  printf(" %d ", ref->data);
}

void main() {
  struct PriorityQueue* head = createPqueue();

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
  
  // push(&head, 0, 1);

  pop(&head);

  fixRear(&head);

  printPqueue(&head);

  free(head);
}
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
  int data;
  struct Node* arrow;
};

struct CircularQueue {
  struct Node* front;
  struct Node* rear; 
};

struct CircularQueue* createCqueue () {
  struct CircularQueue* queue = (struct CircularQueue*) malloc (sizeof(struct CircularQueue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

void insertNode (struct CircularQueue* q, int data) {
  struct Node* node = (struct Node*) malloc (sizeof(struct Node));
  node->data = data;  
  node->arrow = NULL;

  if (q->front = NULL) {
    q->front = node;

  }
  else {
    node->arrow = q->rear;
    q->rear = node; 
    q->front = q->rear;
  }
}

void deleteNode (struct CircularQueue* head) {
  if (head->front == NULL) return;

  if (head->front == head->rear) {
    free(head->front);
    head->front = NULL;
    head->rear = NULL;
  }
  else {
    struct Node* n = head->front;
    head->front = head->front->arrow;
    head->rear->arrow = head->front;
    free(n);
  }
}

void printCqueue (struct CircularQueue* head) {
  struct Node* ref = head->front;
  while (ref->arrow != head->rear) {
    printf(" %d ", ref->data);
    ref = ref->arrow;
  }
  printf(" %d ", ref->data); 
}


void main() {
  struct CircularQueue* head = createCqueue();
  
  insertNode(head, 3);
  insertNode(head, 9);
  insertNode(head, 27);
  insertNode(head, 81);
  
  printCqueue(head);

  free(head);
}
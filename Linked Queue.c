#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct QNode {
  int data;
  struct QNode* next;
};

struct Queue {
  struct QNode *front;
  struct QNode *rear;
};

struct QNode* newNode (int data) {
  struct QNode* node = (struct QNode*) malloc (sizeof(struct QNode));
  node->data = data;
  node->next = NULL;
  return node;
}

struct Queue* createQueue () {
  struct Queue* queue = (struct Queue*) malloc (sizeof(struct Queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

void insertNode (struct Queue* q, int data) {
  struct QNode* new = newNode(data);
  if (q->rear == NULL) {
    q->front = q->rear = new;
    return;
  }
  q->rear->next = new;
  q->rear = new;
}

void removeNode (struct Queue* q) {
  if (q->front == NULL) return;
    
  struct QNode* n = q->front;
  q->front = q->front->next;

  if (q->front == NULL) q->rear = NULL;
  
  free(n);
}

void printQueue (struct Queue* q) {
  struct QNode* current = q->front;
  while (current != NULL) {
    printf(" %d ", current->data);
    current = current->next;
  }
}

void main() {
  struct Queue* q = createQueue();
  insertNode(q, 5);
  insertNode(q, 10);
  insertNode(q, 15);
  insertNode(q, 20);
  insertNode(q, 25);
  removeNode(q);
  removeNode(q);
  printQueue(q);

  free(q);
}
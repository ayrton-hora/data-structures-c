  #include <stdio.h>
  #include <stdlib.h>
  #include <stdbool.h>

struct StackNode {
  int data;
  struct StackNode * next;
};

struct StackNode* createNode (int data) {
  struct StackNode* node = (struct StackNode*) malloc (sizeof(struct StackNode));
  node->data = data;
  node->next = NULL;
  return node;
}

bool isFull (struct StackNode* root) {
  if (root != NULL) return true;
  return false;
}

bool isEmpty (struct StackNode* root) {
  if (root == NULL) return true;
  return false;
}

void push (struct StackNode** root, int data) {
  struct StackNode* new = createNode(data);
  new->next = *root;
  *root = new;
}

void pop (struct StackNode** root) {
  if (isEmpty(*root)) return;

  struct StackNode* n = *root;
  *root = (*root)->next;
  free(n);
}

int peek (struct StackNode* root) {
  if (isEmpty(root)) return INT_MIN;
  return root->data;
}

void printStack (struct StackNode* root) {
  struct StackNode* n = root;
  while (n != NULL) {
    printf(" %d ", n->data);
    n = n->next;
  }
}

void main() {
  struct StackNode* root = NULL;

  push(&root, 50);
  push(&root, 60);
  push(&root, 70);
  pop(&root);
  peek(root);

  printStack(root);

  free(root);
}
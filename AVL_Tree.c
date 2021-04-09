#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct AVLnode {
  int data;
  int height;
  struct AVLnode * left;
  struct AVLnode * right;
};

int max (int a, int b) {
  return (a > b)? a : b;
}

int height (struct AVLnode* n) {
  if (n == NULL) return 0;
  
  else return n->height;
}

int getTreebalance (struct AVLnode* n) {
  if (n == NULL) return 0;
  
  else return (height(n->left) - height(n->right));
}

struct AVLnode* min_Node (struct AVLnode* root) {
  struct AVLnode* ref = root;
  while (ref->left != NULL) ref = ref->left;
  return ref;
}

struct AVLnode* createNode (int data) {
  struct AVLnode* new = (struct AVLnode*) malloc(sizeof(struct AVLnode));
  new->data = data;
  new->height = 1;
  new->left = NULL;
  new->right = NULL;
  return (new);
}

struct AVLnode* leftRotation (struct AVLnode* n) {
  struct AVLnode* a = n->right;
  struct AVLnode* b = a->left;

  a->left = n;
  n->right = b;

  n->height = max(height(n->left), height(n->right)) + 1;
  a->height = max(height(a->left), height(a->right)) + 1;
  
  return a;
}

struct AVLnode* rightRotation (struct AVLnode* n) {
  struct AVLnode* a = n->left;
  struct AVLnode* b = a->right;

  a->right = n;
  n->left = b;
  
  n->height = max(height(n->left), height(n->right)) + 1;
  a->height = max(height(a->left), height(a->right)) + 1;
  
  return a;
}

struct AVLnode* insertNode (struct AVLnode* root, int data) {
  // Base
  if (root == NULL) return (createNode(data));

  // Searching
  if (data < root->data) root->left = insertNode(root->left, data);

  else if (data > root->data) root->right = insertNode(root->right, data);
  
  // If data is equal = error
  else return root;

  // Updating height of actual state of recursin after insertion
  root->height = max(height(root->left), height(root->right)) + 1;

  // Check and fix the balance
  int actual_balance = getTreebalance(root);

  // Left Left Case
  if ((actual_balance > 1) && (data < root->left->data)) return (rightRotation(root));  // <-1

  // Right Right Case
  if ((actual_balance < -1) && (data > root->right->data)) return (leftRotation(root));  // > 1

  // Left Right Case
  if ((actual_balance > 1) && (data > root->left->data)) { 
    root->left = leftRotation(root->left);
    return (rightRotation(root));
  } 

  // Right Left Case
  if ((actual_balance < -1) && (data < root->right->data)) { 
    root->right = rightRotation(root->right);
    return (leftRotation(root));
  }

  // Returning
  return root;
}

struct AVLnode* deleteNode (struct AVLnode* root, int data) {
  // Base
  if (root == NULL) return root;

  // Searching
  if (data < root->data) root->left = deleteNode(root->left, data);

  else if (data > root->data) root->right = deleteNode(root->right, data);

  else {
    
    // Only one child or none
    if ((root->left == NULL) || (root->right == NULL)) { 
      struct AVLnode* n = root->left ? root->left : root->right; // Auxiliar
     
      //  No child
      if (n == NULL) {
        n = root; 
        root = NULL;
      } 
      
      // One child
      else *root = *n; // Saving

      free(n); // Deleting
    }
    
    // Two children
    else {
      // Get smallest in the right
      struct AVLnode* min_n = min_Node(root->right);
      
      // Save the data
      root->data = min_n->data;

      // Delete min_n with recursion and go to another child
      root->right = deleteNode(root->right, min_n->data);
    }
  }
  // Tree has only one node
  if (root == NULL) return root;

  
  root->height = max(height(root->left), height(root->right)) + 1;
  
  // Check and fix the balance
  int actual_balance = getTreebalance(root);
  
  // Left Left Case
  if ((actual_balance > 1) && (getTreebalance(root->left) >= 0)) return rightRotation(root);
  
  // Right Right Case
  if ((actual_balance < -1) && (getTreebalance(root->right) <= 0)) return leftRotation(root);

  // Left Right Case
  if ((actual_balance > 1) && (getTreebalance(root->left) < 0)) {
    root->left = leftRotation(root->left);
    return rightRotation(root);
  }

  // Right Left Case
  if ((actual_balance < -1) && (getTreebalance(root->right) > 0)) {
    root->right = rightRotation(root->right);
    return leftRotation(root);
  }

  // Returning
  return root;
}

void deleteTree (struct AVLnode* root) {
  if (root) {
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
  }
}

void print_PreOrder (struct AVLnode* root) {
  struct AVLnode* ref = root;
  if (root != NULL) {
    printf("%d ", root->data);
    print_PreOrder(ref->left);
    print_PreOrder(ref->right);
  }
}

void print_InOrder (struct AVLnode* root) {
  struct AVLnode* ref = root;
  if (ref != NULL) {
    print_InOrder(ref->left);
    printf("%d ", ref->data);
    print_InOrder(ref->right);
  }
}

void print_PostOrder(struct AVLnode* root) {
  struct AVLnode* ref = root;
  if (ref != NULL) {
    print_PostOrder(ref->left);
    print_PostOrder(ref->right);
    printf("%d ", ref->data);
  }
}

void main() {
  struct AVLnode* root = NULL;

  // Inserting
  root = insertNode(root, 10); 
  root = insertNode(root, 20); 
  root = insertNode(root, 30); 
  root = insertNode(root, 40); 
  root = insertNode(root, 50); 
  root = insertNode(root, 25); 

  printf("AVL Tree:\n");
  print_PreOrder(root);

  // Deleting
  root = deleteNode(root, 25);

  printf("\nAfter deleting:\n");
  print_PreOrder(root);
  
  // Cleaning
  deleteTree(root);
}
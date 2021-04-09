#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct TreeNode {
  int data;
  struct TreeNode * left;
  struct TreeNode * right;
};

struct TreeNode* createNode (int data) {
  struct TreeNode* new = (struct TreeNode*) malloc(sizeof(struct TreeNode));
  new->data = data;
  new->left = NULL;
  new->right = NULL;
  return new;
}

// void setLeft (struct TreeNode** node, int data) {
//   struct TreeNode** new = createNode(data);
//   if (*node == NULL) printf("Node is empty, impossible to set a new left child");
//   else if ((*node)->left != NULL) printf("Left node is full");
//   else (*root)->left = new;      
// }

// void setRight (struct TreeNode** node, int data) {
//   struct TreeNode** new = createNode(data);
//   if (*node == NULL) printf("Node is empty, impossible to set a new right child");
//   else if ((*node)->right != NULL) printf("Right node is full");
//   else (*root)->right = new; 
// }

struct TreeNode* searchNode (struct TreeNode* root, int data) {
  struct TreeNode* ref = root;
  if (ref != NULL) {
    if (data == ref->data) return ref;
    if (data < ref->data) return searchNode(ref->left, data);
    else return searchNode(ref->right, data);
  }
}

struct TreeNode* minNode (struct TreeNode* root) {
  struct TreeNode* ref = root;
  while (ref && ref->left != NULL) ref = ref->left;
  
  return ref;
}

void insertNode (struct TreeNode** root, int data) {
  struct TreeNode* ref = *root;
  if (*root == NULL) *root = createNode(data);
    
  else if (data < (*root)->data) insertNode(&(*root)->left, data);

  else if (data >= (*root)->data) insertNode(&(*root)->right, data);
}

struct TreeNode* deleteNode (struct TreeNode** root, int data) {
  struct TreeNode* temp = NULL;
  
  // Base
  if (*root == NULL) return *root; 
  
  // Data is smaller than
  if (data < (*root)->data) (*root)->left = deleteNode(&(*root)->left, data); 

  // Data is greater than
  else if (data > (*root)->data) (*root)->right = deleteNode(&(*root)->right, data); 

  // Data is equal
  else { 

    // One or no child
    if ((*root)->left == NULL) {
      temp = (*root)->right;
      free(*root);
      return temp;
    }

    else if ((*root)->right == NULL) {
      temp = (*root)->left;
      free(*root);
      return temp;
    }

    // Two children
    // Smallest in the right (InOrder sucessor)
    temp = minNode((*root)->right); 

    // Copy and save the data
    (*root)->data = temp->data; 

    // Delete smallest in the right (InOrder sucessor)
    (*root)->right = deleteNode(&(*root)->right, temp->data); 
  }
  return (*root);
}

void deleteTree (struct TreeNode* root) {
  if (root) {
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
  }
}

void print_PreOrder (struct TreeNode* root) {
  struct TreeNode* ref = root;
  if (root != NULL) {
    printf("%d ", root->data);
    print_PreOrder(ref->left);
    print_PreOrder(ref->right);
  }
}

void print_InOrder (struct TreeNode* root) {
  struct TreeNode* ref = root;
  if (ref != NULL) {
    print_InOrder(ref->left);
    printf("%d ", ref->data);
    print_InOrder(ref->right);
  }
}

void print_PostOrder(struct TreeNode* root) {
  struct TreeNode* ref = root;
  if (ref != NULL) {
    print_PostOrder(ref->left);
    print_PostOrder(ref->right);
    printf("%d ", ref->data);
  }
}

void main() {
  struct TreeNode* root = NULL;

  // Inserting
  insertNode(&root, 10);
  insertNode(&root, 8);
  insertNode(&root, 3);
  insertNode(&root, 1);
  insertNode(&root, 15);
  insertNode(&root, 5);

  // Deleting
  deleteNode(&root, 3);

  printf("The minimum Node is:\n");
  printf("%d\n", minNode(root)->data);

  printf("Binary Tree:\n");
  print_InOrder(root);

  // Cleaning
  deleteTree(root);
}
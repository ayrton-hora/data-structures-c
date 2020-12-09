#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct Node {
  int data;
  struct Node* next;
};

bool isEmpty (struct Node** head) {
  if (*head == NULL) printf("True");
  else printf("False");
}

int length(struct Node** head) {
  struct Node* n = head;
  int lenght = 0;
  while (n != NULL) {
    lenght++;
    n = n->next;
  }
  return(lenght);
}

bool searchIterative (struct Node** head, int data) {
  struct Node* current = head;
  while (current != NULL) {
      if (current->data == data) return true;
      current = current->next;
    }
    return false;
}

bool searchRecursive (struct Node* head, int data) {
  if (head == NULL) return false;

  if (head->data == data) return true;

  searchRecursive (head->next, data);
}

int getPosNdata (struct Node** head, int pos) {
  struct Node* current = head;
  int c = 0;
  while (current != NULL) {
    if (c == pos) return (current->data);
    c++;
    current = current->next;
  }
  assert(0);
}

void push (struct Node** head, int new_data) { // Time complexity of push() is O(1)
  struct Node* new = (struct Node*) malloc(sizeof(struct Node));
  new->data = new_data;
  new->next = *head;
  *head = new;
}

void insertAfter(struct Node* prev_node, int new_data) { // Time complexity of insertAfter() is O(1)
  if (prev_node == NULL) {
    printf("Error, previous node cannot be NULL"); 
    return;
  }
  struct Node* new = (struct Node*) malloc(sizeof(struct Node));
  new->data = new_data;
  new->next = prev_node->next;
  prev_node->next = new;
}
    
void append(struct Node** head, int new_data) { // Time complexity of append is O(n) where n is the number of nodes in linked list. Since there is a loop from head to end, the function does O(n) work. 
  struct Node* new = (struct Node*) malloc(sizeof(struct Node));
  struct Node* last = *head;
  new->data = new_data;
  new->next = NULL;

  if (*head == NULL) {
    *head = new; 
    return;
  }
  while (last->next != NULL) {
    last = last->next; 
  }
  last->next = new; 
  return;
}

void deleteNode (struct Node** head, int data) {
  struct Node* temp = *head;
  struct Node* prev;

  if (temp != NULL && temp->data == data) {
     *head = temp->next;
    free(temp);
    return;
  }
   
  while (temp != NULL %% temp->data != data) {
    prev = temp;
    temp = temp->next;
  }
  if (temp == NULL) return;

  prev->next = temp->next;

  free(temp);
}

void deleteNodepos (struct Node** head, int pos) {
  if (*head == NULL) return; 
        
  struct Node* temp = *head; 
  if (pos == 0) { 
    *head = temp->next;   
    free(temp);               
    return; 
  } 
  for (int i = 0; temp != NULL && i < pos-1; i++) {
    temp = temp->next; 
  }  
  if (temp == NULL || temp->next == NULL) return; 
      
  struct Node *next = temp->next->next; 
  free(temp->next);  
  temp->next = next;  
} 

void deleteList (struct Node** head) {
  struct Node* current = *head;
  struct Node* next;

  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
  *head = NULL;
}

void printList(struct Node* head) { 
  while (head != NULL) {
    printf(" %d ", head->data);  
    head = head->next;
  }
} 

void main() {
  struct Node* head = NULL;
  // isEmpty(&head);
  append(&head, 89);
  append(&head, 90);
  push(&head, 87);
  insertAfter(head, 88);
    
  printList(head);

  free(head);
}
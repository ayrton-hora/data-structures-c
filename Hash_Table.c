#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAPACITY 1000 // Size of the Hash Table

typedef struct Linked_list Linked_list;

struct Linked_list {
  struct Data* data;
  struct Linked_list* next;
};

typedef struct Data Data;

struct Data {
  char* key;
  char* data;
};

typedef struct Hash_table Hash_table;

struct Hash_table {
  int size;
  int elements;
  struct Data** data_array;
  struct Linked_list** chaining;
};

struct Linked_list* createLLNode (struct Data* data) {
  struct Linked_list* new = (Linked_list*) malloc (sizeof(struct Linked_list));
  new->data = data;
  new->next = NULL;
  return new;
}

struct Linked_list* insertLLNode (struct Linked_list* lst, Data* data) {
  struct Linked_list* node = createLLNode(data);
  // Head case
  if (!lst) {
    lst = node;
    return lst;
  }

  // Next
  else if (lst->next == NULL) {
    lst->next = node;
    return lst;
  }

  // Searching free space
  struct Linked_list* ref = lst;
  while (ref->next->next != NULL) ref = ref->next;
  ref->next = node;

  // Returning
  return lst;
}

struct Data* popLLNode (struct Linked_list* lst) {  
  if (lst == NULL) return NULL;

  if (lst->next == NULL) return NULL;

  struct Linked_list* ref = lst;
  struct Linked_list* ref_next = lst->next;
  struct Data* popped = NULL;
  
  ref->next = NULL;
  lst = ref_next;

  memcpy(ref->data, popped, sizeof(struct Data));
  
  free(ref->data->key);
  free(ref->data->data);
  free(ref->data);
  free(ref);

  return popped;
}

void clear_Linkedlist (struct Linked_list* lst) {
  struct Linked_list* ref = lst;
  while (lst != NULL) {
    ref = lst;
    lst = lst->next;
    free(ref->data->key);
    free(ref->data->data);
    free(ref->data);
    free(ref);
  }
}

struct Linked_list** createChaining (struct Hash_table* table) {
  struct Linked_list** chains = (Linked_list**) calloc (table->size, sizeof(Linked_list*));
  
  for (int i = 0; i < table->size; i++) chains[i] = NULL;

  return chains;
}

void clear_Chains (struct Hash_table* table) {
  struct Linked_list** chains = table->chaining;

  for (int i = 0; i < table->size; i++) clear_Linkedlist(chains[i]);

  free(chains);
}
 
unsigned long hash_function (char* string) {
  unsigned long i = 0;
  for (int j = 0; string[j]; j++) i = i + string[j];
  return i % CAPACITY;
}

struct Data* createData (char* key, char* data) {
  struct Data* new = (struct Data*) malloc(sizeof(struct Data));
  new->key = (char*) malloc (strlen(key) + 1);
  new->data = (char*) malloc (strlen(data) + 1);
  strcpy(new->key, key);
  strcpy(new->data, data);
  return new;
}

struct Hash_table* createTable (int size) {
  struct Hash_table* new_table = (struct Hash_table*) malloc (sizeof(struct Hash_table));
  new_table->size = size;
  new_table->elements = 0;
  new_table->data_array = (struct Data**) calloc (new_table->size, sizeof(struct Data*));
  
  // Setting Null
  for (int i = 0; i < new_table->size; i++) {
    new_table->data_array[i] = NULL;
  }
  
  // Creating chaining
  new_table->chaining = createChaining(new_table);

  return new_table;
}

char* search_Data (struct Hash_table* table, char* key) {
  int index = hash_function(key);
  struct Data* target_data = table->data_array[index];
  struct Linked_list* chaining_ref = table->chaining[index];
  
  // Searching
  while (target_data != NULL) {
    if (strcmp(target_data->key, key) == 0) return target_data->data;
    
    if (chaining_ref == NULL) return NULL;

    target_data = chaining_ref->data;
    chaining_ref = chaining_ref->next;
  }

  // Returning
  return NULL;
}

void colision (struct Hash_table* table, unsigned long index, Data* data) {
  struct Linked_list* chaining_head = table->chaining[index];

  // If is empty
  if (chaining_head == NULL) {
    chaining_head = (Linked_list*) malloc (sizeof(struct Linked_list));
    chaining_head->data = data;
    chaining_head->next = NULL;
    table->chaining[index] = chaining_head;
  }

  // If not
  else table->chaining[index] = insertLLNode(chaining_head, data);
}

void insert_Data (struct Hash_table* table, char* key, char* data) {
  struct Data* new = createData(key, data);

  // Find the index
  int index = hash_function(key);

  struct Data* current_data = table->data_array[index];

  // If the key does not exist
  if (current_data == NULL) {
    
    // If table is full
    if (table->elements == table->size) printf("Error: Hash Table is full\n");

    // Insert
    table->data_array[index] = new;
    table->elements ++;
  }
  
  // If key exist in table
  else {
    
    // Comparing
    if (strcmp(current_data->key, key) == 0) strcpy(table->data_array[index]->data, data);

    // Collision
    else colision(table, index, new);
  }
}

void clear_Data (struct Data* data) {
  free(data->key);
  free(data->data);
  free(data);
}

void delete_Data (struct Hash_table* table, char* key) {
  int index = hash_function(key);
  struct Data* ref_data = table->data_array[index];
  struct Linked_list* ref_chains = table->chaining[index];

  // if is NULL, end
  if (ref_data == NULL) return; 
  
  // Searching
  else {
    // No collision, just remove
    if ((ref_chains == NULL) && (strcmp(ref_data->key, key) == 0)) {
      table->data_array[index] = NULL;
      clear_Data(ref_data);
      table->elements--;
    }

    // Collision
    else if (ref_chains != NULL) {
      // Key is in the head
      if (strcmp(ref_data->key, key) == 0) {
        
        clear_Data(ref_data);
        
        struct Linked_list* temp = ref_chains;
        ref_chains = ref_chains->next;
        temp->next = NULL;    
        table->data_array[index] = createData(temp->data->key, temp->data->data);

        clear_Linkedlist(temp);
        
        table->chaining[index] = ref_chains;
      }
      // Key is in the Linked List
      struct Linked_list* current = ref_chains;
      struct Linked_list* previest = NULL;
      
      // Searching in the chaining
      while (current != NULL) {
        if (strcmp(current->data->key, key) == 0) {
          // First in the chaining
          if (previest == NULL) {
            clear_Linkedlist(ref_chains);
            table->chaining[index] = NULL;
          }
          // If not
          else {
            previest->next = current;
            current->next = NULL;
            clear_Linkedlist(current);
            table->chaining[index] = ref_chains;
          }
        }
        // Possible error
        current = current->next;
        previest = current;
        
      } 
    }
  }
}

void clear_Table (struct Hash_table* table) {
  for (int i = 0; i < table->size; i++) {
    struct Data* ref = table->data_array[i];
    
    if (ref != NULL) clear_Data(ref);
  }
  clear_Chains(table);
  free(table->data_array);
  free(table);
}

void print_Search(struct Hash_table* table, char* key) {
  char* ch;
  if ((ch = search_Data(table, key)) == NULL) printf("The %s doesn't exist\n", key);

  else printf("Key %s, Value %s\n", key, ch);
}

void print_Table (struct Hash_table* table) {
    printf("\nHash Table\n--------------------------------------\n");
    for (int i = 0; i < table->size; i++) {
        if (table->data_array[i]) {
            printf("Index: %d, Key: %s, Data: %s\n", i, table->data_array[i]->key, table->data_array[i]->data);
            if (table->chaining[i]) {
              printf(" '--> Chaining ");
              struct Linked_list* ref = table->chaining[i];
              while (ref != NULL) {
                printf("--> Key: %s, Data: %s ", ref->data->key, ref->data->data);
                ref = ref->next;
              }
            }
            // printf("\n");
        }
    }
    printf("\n--------------------------------------\n\n");
}

void main () {
  struct Hash_table* table = createTable(CAPACITY);

  // Inserting
  insert_Data(table, "1", "0001");
  insert_Data(table, "2", "0002");
  insert_Data(table, "3", "0003");
  insert_Data(table, "4", "0004");
  insert_Data(table, "Hel", "0005");
  insert_Data(table, "Cau", "0006"); // Chain
  insert_Data(table, "Hdm", "0007"); // Chain
  insert_Data(table , "5", "0008");
  insert_Data(table, "6", "0009");
  insert_Data

  // Searching
  print_Search(table, "5");

  // Deleting
  delete_Data(table, "4");
  
  // Printing
  print_Table(table);

  // Cleaning
  clear_Table(table);
}
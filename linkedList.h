#include <stdlib.h>
#include <stdio.h>


typedef union element{
  char c;
  signed long int i;
  double d;
  char* s;
} ELEMENT_t;


typedef enum element_type{
  CHAR_TYPE=0, //0
  INT_TYPE, //1
  DOUBLE_TYPE,//2
  STRING_TYPE,//3
  ARRAY_TYPE // 4
}ELEMENT_TYPE_e;

// LinkList
// doesnt store elements unless it has a key
typedef struct generic_list_item{
  // store type  of variable
  ELEMENT_TYPE_e type;
  //store c,i, d, s  store value
  ELEMENT_t value;
  //keep track of array
  int count;
  // store key  value
  char* key;
  struct generic_list_item *next;
} GENERIC_LIST_ITEM_t;

typedef struct generic_list{
  GENERIC_LIST_ITEM_t *head, *tail;
  int size;
} GENERIC_LIST_t;


void printItem(GENERIC_LIST_t *list, const char* search, int ARRAY_PRINT);
void addElement(GENERIC_LIST_t *list, GENERIC_LIST_ITEM_t *item);
void removeElement(GENERIC_LIST_t *list, char* key);
void printList( GENERIC_LIST_t *list);
void storeValue(GENERIC_LIST_t *main, GENERIC_LIST_ITEM_t *item, const char* right_operand1, int type);
int findType(GENERIC_LIST_t *list, char* right_operand, int search_array);
void Operation( GENERIC_LIST_t *main, GENERIC_LIST_ITEM_t *item,char optype2, const char* right_operand2, int type);
void appendItem(GENERIC_LIST_t *list, char* array_key , char* store);
void arrayStoreValue(GENERIC_LIST_t *list,GENERIC_LIST_ITEM_t *item, char* array_key , char* array_index);
void arrayType(GENERIC_LIST_t *list, GENERIC_LIST_ITEM_t *head, int ARRAY_PRINT);
// void printArr()

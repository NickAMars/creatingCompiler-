#include "linkedList.h"
#include "parser.h"
#include <stdlib.h>

void appendItem(GENERIC_LIST_t *list, char* array_key , char* store){
      GENERIC_LIST_ITEM_t *newItem =  (GENERIC_LIST_ITEM_t*)calloc(1,sizeof(GENERIC_LIST_ITEM_t));
      char  comma = ',';

    	GENERIC_LIST_ITEM_t *head =  list->head;
      // GENERIC_LIST_t *sec_list = (GENERIC_LIST_t*)calloc(1,sizeof(GENERIC_LIST_t));

      while (head != NULL){
        // printf(" value : %s   \n", head->key);

          if(strcmp(head->key, array_key) == 0){

            if(head->type  == ARRAY_TYPE){
                        // get the string and add it in
                        // printf("get the current array values  : %s\n",  head->value.s);
                        newItem->key =  head->key;
                        newItem->type = ARRAY_TYPE;
                        //adding new element to the list
                        int i = 0;
                        int size =0;
                        char *string= calloc(MAX_VAR_LEN,sizeof(char));// = "Hello"
                        // printf(" value : %s   \n", head->value.s);
                        if(head->value.s == NULL){
                          // printf("%s   \n", "string is empty");
                        }else{
                            while(head->value.s[i]   != '\0'){
                             string[i] = head->value.s[i++];
                             size++;
                            }
                        }
                        if(i != 0){
                          string[size] = comma;
                          size++;
                          i = 0;
                        }
                        while(store[i]  != '\0'){
                          string[size++] = store[i++];
                        }
                        newItem->count = head->count + 1;
                        newItem->value.s = string;
                        // printf("get the current array values  : %s\n",  newItem->value.s);
                        // newItem->count++;
                        // putting value in string
                      }
          }
          head = head->next;
      }
      // REMOVE OLD ITEM FROM LIST
      removeElement(list, array_key);
      // ADD NEW ITEM TO LIST
      addElement(list, newItem);
}

// }

void removeElement(GENERIC_LIST_t *list, char* key){
    GENERIC_LIST_ITEM_t *curr =list->head;
    GENERIC_LIST_ITEM_t *prev =list->head;
    while( strcmp(curr->key, key) != 0 && curr != NULL){
      // printf("Went in %s\n", "the loop");
      prev = curr;
      curr = curr->next;
    }
    // if(curr == NULL){}// didnt find anything
    if( strcmp(curr->key, list->head->key) == 0){
      // printf("list: %s\n", list->head->key);
      // printf("curr : %s\n", curr->key);
      // printf("prev : %s\n", prev->key);
      list->head = curr;
    }else{
      prev->next = curr->next;
    }

    if( strcmp(curr->key, list->tail->key ) == 0){
      list->tail = prev;
    }
    free(curr);
}


void addElement(GENERIC_LIST_t *list, GENERIC_LIST_ITEM_t *item){
  if(list->head == NULL){
    list->head = item;
    list->tail = item;
  }else{
      list->tail->next = item;
      list->tail = list->tail->next;
  }
}

void printList( GENERIC_LIST_t *list){
  GENERIC_LIST_ITEM_t *head = list->head;
  while(head != NULL){
    // PRINTS ALL KEYS

    if(DOUBLE_TYPE == head->type){
      printf(" keys:  %s type: %i value : %f\n",
       head->key, DOUBLE_TYPE ,head->value.d);
    }else if(INT_TYPE == head->type){
      printf(" keys:  %s type: %i value : %lu\n",
       head->key,INT_TYPE ,head->value.i);
    }
    head = head->next;
  }
}

void printItem(GENERIC_LIST_t *list, const char* search, int ARRAY_PRINT ){
  GENERIC_LIST_ITEM_t *head = list->head;
  // find out if value is an array in the for loop

    //search for the
  while(head != NULL){
    // find value
    if( strcmp(head->key, search) == 0){
      // if its type array
      if(head->type == ARRAY_TYPE){
        arrayType(list, head , ARRAY_PRINT);
      }else if(head->type == DOUBLE_TYPE){
        printf("Print Variable: %f\n",  head->value.d);
      }else{
        printf("Print Variable: %lu\n",  head->value.i);
      }
    }
    // loop through
    head = head->next;
  }
}

void arrayType(GENERIC_LIST_t *list, GENERIC_LIST_ITEM_t *head, int ARRAY_PRINT){
  // initialize
  // int ARRAY_PRINT = 0;
  int i = 0;
  char *rest = calloc(100,sizeof(char));

  // get a copy of the string
  while(head->value.s[i] != '\0'){
    rest[i] = head->value.s[i++];
  }

  //store values temporarily
  char *store = calloc(100,sizeof(char));
  i = 0;
  // seperate values by ','
  while( i  < head->count){
    // store value temporarily
    store = strtok_r(rest, ",", &rest);

    // permit to search if tpye is array
    int search_array = 1;
    int TYPE  = findType(list ,store, search_array);
    // begin array
    if(i  == 0){
      printf("[");
    }
    if(TYPE == ARRAY_TYPE){
            // arrayType(GENERIC_LIST_t *list, GENERIC_LIST_ITEM_t *head)
                GENERIC_LIST_ITEM_t *head_array = list->head;
                // find the array in the list
                while( strcmp(head_array->key, store) != 0){
                  head_array = head_array->next;
                }
                int Change = 0;
                printItem(list, head_array->key, Change);
                // ARRAY_PRINT = 1;
                // print the string of the array value
                // if(i == head->count -1){
                //   printf("['%s']]",head_array->value.s);
                // }else{
                //   printf("['%s'],",head_array->value.s);
                // }

    }else if(TYPE == STRING_TYPE){
      // place the ""
        // if(ARRAY_PRINT == 0){}
      if(i == head->count -1){
        if(ARRAY_PRINT == 1)
          printf("\"%s\"]]",  store);
        else
        printf("\"%s\"]",  store);
      }else{
        printf("\"%s\",",store);
      }
    }else if(TYPE == CHAR_TYPE){
      if(i == head->count -1){
        if(ARRAY_PRINT == 1)
          printf("'%s']]",  store);
        else
        printf("'%s']",  store);
      }else{
        printf("'%s',",  store);
      }
    }else{

      if(i == head->count -1){
        if(ARRAY_PRINT == 1)
          printf("%s]]",  store);
        else
        printf("%s]",  store );
      }else{
        printf("%s,",  store);
      }

    }
    i++;
  }
// printf("arrayprint%i",  ARRAY_PRINT);
  if(ARRAY_PRINT == 1){
    printf("\n");
  }
}


// atof
// atoi


// find  string, character, double integer
int findType( GENERIC_LIST_t *list, char* right_operand, int search_array){
	int i = 0;
  // just incase value is an array
  if(search_array == 1){
    GENERIC_LIST_ITEM_t *head = list->head;
    while(head != NULL){
      if(strcmp(head->key, right_operand) == 0){
        if(head->type == ARRAY_TYPE){
          // printf("You have found a array : %i \n ", ARRAY_TYPE);
          return ARRAY_TYPE;
        }
      }
      head= head->next;
    }
  }
	// printf("%i", sizeof(result->right_operand1));
	 while(right_operand[i] != '\0'){

		   // value can be a string or char
		   if( (char) right_operand[i] >= 65  && (char) right_operand[i] <= 90
			 || (char) right_operand[i] >= 97  && (char) right_operand[i] <= 122){
				 int j = 0;
				 while(right_operand[j] != '\0'){	j++;}
				 if(j == 1){// character
					 return CHAR_TYPE;
				 }else{// string
					 return STRING_TYPE;
				 }
			 }
			 // if double this runs
			 if(right_operand[i] == '.'){
				 return DOUBLE_TYPE;
			 }
		 	 i++;
		}
		// if nothing is met return the integer
		return INT_TYPE;
}
/*
	goes through the list and store
	the value receive after
	searching for the variable
	p.s. overrides the type for char and string
			to find out what value they have
*/
void storeValue(GENERIC_LIST_t *main, GENERIC_LIST_ITEM_t *item, const char* right_operand1, int type){
	// need a different reference of the object
	// GENERIC_LIST_t *Change = new  GENERIC_LIST_t (main);
	item->value.d= 0.0;
	item->value.i= 0;
	GENERIC_LIST_ITEM_t *head = main->head;
	if(type == CHAR_TYPE){
					// printf("%s \n", "Search for string" );
					// printf("  right operands: %c   \n", right_operand1[0] );
		while(head != NULL){
			 // printf("%s \n", "didnt have a second operand" );
			// look throw all keys to find the matching one
			// printf("  keys: %c   \n", head->key[0] );
			if(head->key[0] == right_operand1[0]){
				// store value
				// printf("%s   \n", "found the key " );
				if(head->type == DOUBLE_TYPE){
						// printf("value for head in list : %i   \n", head->type );
					item->value.d += head->value.d;
					// re-write the type
					item->type = DOUBLE_TYPE;
				}else{
					item->value.i +=  head->value.i;
					item->type = INT_TYPE;
				}
			}
			// going through all of the head values
			head = head->next; // problems with this
		}
	}else if(type == STRING_TYPE){
			// printf("%s   \n", right_operand1);
			// int i = 0;
			// char copy_operand1[100];
			// while(right_operand1[i] != '\0'){
			// 	copy_operand1[i] += right_operand1[i++];
			// }
			// printf(" copy_operand1  : %s   \n", copy_operand1 );
		while(head != NULL){
			// look throw all keys to find the matching one
				// printf("%s   \n", head->key);
			if( strcmp(head->key, right_operand1) == 0 ){ //head->key == right_operand1){
				// printf("%s   \n", "found the key " );
				// store value
				if(head->type == DOUBLE_TYPE){
					item->value.d += head->value.d;
					item->type = DOUBLE_TYPE;
				}else{
					item->value.i += head->value.i;
					item->type = INT_TYPE;
				}
			}
			// going through all of the head values
			head = head->next; // problems with this
		}
	// store rather a double or integer at first in the variable
	}else if(type == DOUBLE_TYPE){
		// printf(" get the right operand1: %s \n", right_operand1);
		item->value.d += (double) atof(right_operand1);
		// printf(" get the right operand1: %f \n", item->value.d);
	}else{// integer
		item->value.i += atoi(right_operand1);
	}
}

void arrayStoreValue(GENERIC_LIST_t *list,GENERIC_LIST_ITEM_t *item, char* array_key , char* array_index){


  GENERIC_LIST_ITEM_t *head = list->head;
    while (head != NULL) {
      if( strcmp(array_key, head->key) == 0){
        // printf(" %s   \n", "found the array" );
        // dont want to change the actual array
        int index =  (int) atoi( array_index);
        int i = 0;
        char *rest = calloc(100,sizeof(char));
        // copy over the string in the array without referencin the address
        while(head->value.s[i] != '\0'){
          rest[i] = head->value.s[i++];
        }
        //
        i = -1;
        char *store = calloc(100,sizeof(char));
        // keep on cutting up the string by ","
        while( i  < index ){
          store = strtok_r(rest, ",", &rest);
          i++;
        }
        if(store != NULL){
          // dont search the aray of the value taken
          int search_array = 0;
          	// printf(" store has the element : %s   \n", 	store );
            item->type = findType(list ,store, search_array);
            storeValue(list, item, store, item->type);
        }
        // test case success when
      	// printf(" store has the element : %s   \n", 	store );
        // if(store != NULL){
        //
        // }
      }
      // compare  the key and the head
      head = head->next;
    }
    // create a new store value for array
    // storeValue(main, item,result->right_operand1,item->type);
}
/*
	goes through and does the
	operations with the second param and
	store the value in the final value
*/
void Operation( GENERIC_LIST_t *main, GENERIC_LIST_ITEM_t *item,char optype2, const char* right_operand2, int type){
  GENERIC_LIST_ITEM_t *head = main->head;
	if(type == CHAR_TYPE){
		while(head != NULL){
			if(head->key[0] == right_operand2[0]){
				if(head->type == DOUBLE_TYPE){

					switch(optype2){
						case '+': item->value.d = item->value.d + head->value.d; break;
						case '-': item->value.d = item->value.d - head->value.d; break;
						case '*': item->value.d = item->value.d * head->value.d; break;
						case '/': item->value.d = item->value.d / head->value.d; break;
						default: break;
					}
				}else{
					switch(optype2){
						case '+': item->value.i = item->value.i + head->value.i; break;
						case '-': item->value.i = item->value.i - head->value.i; break;
						case '*': item->value.i = item->value.i * head->value.i; break;
						case '/': item->value.i = item->value.i / head->value.i; break;
						default: break;
					}
				}
			}
			// going through all of the head values
			head = head->next;
		}

	}else if(type == STRING_TYPE){

		while(head != NULL){
			// look throw all keys to find the matching one

			if(strcmp(head->key, right_operand2) == 0){
				// printf("%s   \n", "found the key string");
				// store value
				if(head->type == DOUBLE_TYPE){
					switch(optype2){
						case '+': item->value.d = item->value.d + head->value.d; break;
						case '-': item->value.d = item->value.d - head->value.d; break;
						case '*': item->value.d = item->value.d * head->value.d; break;
						case '/': item->value.d = item->value.d / head->value.d; break;
						default: break;
					}
				}else{
					switch(optype2){
						case '+': item->value.i = item->value.i +  head->value.i; break;
						case '-': item->value.i = item->value.i -  head->value.i; break;
						case '*': item->value.i = item->value.i *  head->value.i; break;
						case '/': item->value.i = item->value.i /  head->value.i; break;
						default: break;
					}
				}
			}
			// going through all of the head values
			head = head->next;
		}
	}else if(type == DOUBLE_TYPE){

		switch(optype2){
			case '+': item->value.d = item->value.d + (double) atof(right_operand2); break;
			case '-': item->value.d = item->value.d - (double) atof(right_operand2); break;
			case '*': item->value.d = item->value.d * (double) atof(right_operand2); break;
			case '/': item->value.d = item->value.d / (double) atof(right_operand2); break;
			default: break;
		}

	}else{// integer
		switch(optype2){
			case '+': item->value.i +=  ((unsigned long) atoi(right_operand2)) ; break;
			case '-': item->value.i -=  ((unsigned long) atoi(right_operand2)) ; break;
			case '*': item->value.i *= ((unsigned long) atoi(right_operand2)) ; break;
			case '/': item->value.i /= ((unsigned long) atoi(right_operand2)) ; break;
			default: break;
		}
		// printf(" final value in function  : %lu \n", item->value.i);
			// item->value.i = item->value.i  + atoi(result->right_operand2);
	}
}


void alreadyExist(GENERIC_LIST_t *list,  char* key ){
 GENERIC_LIST_ITEM_t *head =  list->head;
  while(head != NULL){
    if(strcmp(head->key, key) == 0){
      // printf("   %s\n",  " already exist ");
      removeElement(list, key);
    }
    head = head->next;
  }

// removeElement(GENERIC_LIST_t *main, left_operand);
}

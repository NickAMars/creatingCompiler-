#include <stdio.h>
#include "linkedList.h"
#include "parser.h"



int main(){
	char comment[100];
		// create container
		GENERIC_LIST_t *main =  (GENERIC_LIST_t*)calloc(1,sizeof(GENERIC_LIST_t));
		PARSE_RESULT_t* result;
		int search_array = 0; // false
		while(1){
		printf(">>>");
		scanf("%99[^\n]", comment);
		scanf("%*c");
		result = parse_string(comment);
		// keep making new items every iteration
		GENERIC_LIST_ITEM_t *item =  (GENERIC_LIST_ITEM_t*)calloc(1,sizeof(GENERIC_LIST_ITEM_t));



				if(result->optype == PRINT_OP){
        		// printf("Print Variable: %s\n",result->right_operand1);
						int ARRAY_PRINT = 1;
						printItem(main, result->left_operand, ARRAY_PRINT );
    		}else if(result->optype == APPEND_OP){
						// result->left_operand  the key
						// appendItem( result->left_operand);
        		// printf("Append Variable: %s\n",result->left_operand);
						// printf("Append Variable: %s\n",result->right_operand1);
						// appendItem(result->left_operand ,result->right_operand1)
						appendItem(main, result->left_operand , result->right_operand1);

    		}else{
					alreadyExist(main,  result->left_operand );
					item->key  =  result->left_operand;
					// if the equal sign has bee given

					// check if the right_operand = '[]'
					if(strcmp(result->right_operand1, "[]") == 0){
								item->type = ARRAY_TYPE;
								// printf("right1 list name : %s   \n", result->right1_list_name);
								if(result->right1_list_name == NULL){
									// key is already stored
									// refering to an array type
									//
									item->value.s = "";
									item->count = 0;
									// addElement(main, item);
									 // printf("%s   \n", "add array into the list ");
								}else{
									arrayStoreValue(main, item, result->right1_list_name , result->right1_list_index);
									// first find the key in the linklist
									// char* key = result->right1_list_name;
									// find what at the location in the string of the array
									//right1_list_index;
									// // use this to iterate array
							}
					}else{ // do normal stuff
							/*
								params  char*
								Looks for type of function
								return int
							 */
							item->type = findType(main ,result->right_operand1, search_array);
							storeValue(main, item,result->right_operand1,item->type);
					}
							/*
							 @params GENERIC_LIST_t, GENERIC_LIST_ITEM_t,int
							 keeps a value in the new item
							*/

							if(result->right_operand2 == NULL){
								addElement(main, item);
							}else{
								int type2 = findType(main , result->right_operand2, search_array);
								/*
									@params GENERIC_LIST_ITEM_t, char , char* , int
								 does the operaction and store the value in item
								*/
								// printf(" second operataion  %c   \n", result->optype2 );
								Operation(main ,item, result->optype2 ,result->right_operand2, type2);
								addElement(main, item);
							}
				// 	if(result->right_operand2 != NULL){
				// 			printf("%s = %s %c %s\n",result->left_operand, result->right_operand1, result->optype2, result->right_operand2);
				// }else{
				// 			printf("%s = %s\n",result->left_operand,result->right_operand1);
				//  }

    }
	}
    free(comment);
	return 0;
}

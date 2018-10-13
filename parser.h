#include <string.h>
#include <stdlib.h>

typedef enum optype{
  ADD_OP = '+',//0
  SUB_OP = '-',//1
  MULT_OP = '*',//2
  DIV_OP = '/',//3
  PRINT_OP= 4,//4
  APPEND_OP = 5,//5
  ASSIGN_OP= 6//6
}OPTYPE_e;
/*left_operand optype  right_operand1 optype2 right_operand2
    a           =        b             +           c
*/
typedef struct parse_result{
    char* left_operand;
    char* right_operand1;
    char* right_operand2;
    char* right1_list_name; // contains the list name
    char* right1_list_index; // contains the number in the list

    OPTYPE_e optype;
    OPTYPE_e optype2;
} PARSE_RESULT_t;

#define PRINT_COMMAND "print("
#define APPEND_COMMAND "append("
#define MAX_BUFFER_LEN 100+1
#define MAX_VAR_LEN 15+1
// annonymous function
PARSE_RESULT_t *parse_string(const char* input_buffer);

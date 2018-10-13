#include "parser.h"
#include "linkedList.h"

// initialize

// GENERIC_LIST_t *main =  (GENERIC_LIST_t*)calloc(1,sizeof(GENERIC_LIST_t));
PARSE_RESULT_t *parse_string(const char* input_buffer){
  // initialize result value to null
    PARSE_RESULT_t* result = (PARSE_RESULT_t*)calloc(1,sizeof(PARSE_RESULT_t));
    //command with max length initial to 15+1
    char* command = (char*)calloc(MAX_BUFFER_LEN,sizeof(char));
    // command value is equal to input_buffer
    strcpy(command, input_buffer);
    char *token, *rest;
    // passing reference address to rest
    rest = command;
    // compare the first 6 char of each string
    if(strncmp(command,PRINT_COMMAND,6)==0){
      // optype is referring to print(
        result->optype = PRINT_OP;

        strtok_r(rest, "()", &rest); // rest = "a)"
        // initalizing
        char* operand = calloc(MAX_VAR_LEN,sizeof(char));
        // token  = a
        token = strtok_r(rest, "()", &rest);
        // store a into the operand
        strcpy(operand,token);
        // the left operand is equal to a
        result->left_operand = operand;
        // clearing the command space
        free(command);
        return result;
        // append is the same thing as print
    }else if(strncmp(command,APPEND_COMMAND,7)==0){

        result->optype = APPEND_OP;
        // rest = append(a,b)
        strtok_r(rest, "()", &rest); // remove append
        // token = a,b
        token = strtok_r(rest, "()", &rest);
        // strcpy(operand,token);
        // result->left_operand = operand;
        char* operand= calloc(MAX_VAR_LEN,sizeof(char));
         // operand =  strtok_r(token, ",", &token);

         //a
         strcpy(operand,strtok_r(token, ",", &token));
         result->left_operand = operand;
        // b
        char* operand2 = calloc(MAX_VAR_LEN,sizeof(char));
        strcpy(operand2,token);
        result->right_operand1 = operand2;
        // give me a good idea of the append method
        // printf(" first variable  %s\n",  result->left_operand);
        // printf(" second variable %s\n",  result->right_operand1);

        //result->right_operand1 = operand;
        free(command);
        return result;


    }else{
        /* e.g. "a = b + c"
        line 1  operand = initialize
        line 2 token  = "a"   and  rest = "b + c"
        line 3  operand = "a"
        line 4  store  a
        */
        char* operand = calloc(MAX_VAR_LEN,sizeof(char));
        token = strtok_r(rest, " +-*/=", &rest);
        strcpy(operand,token);
        result->left_operand = operand;

        result->optype = ASSIGN_OP; // =
        /* e.g. "a = b + c"
        line 1  operand = initialize
        line 2 token  = "b"   and  rest = "c"
        line 3  operand = "b"
        line 4  store  b
        */
        operand = calloc(MAX_VAR_LEN,sizeof(char));
        token = strtok_r(rest, " +-*/=]", &rest);
         //check is [] exist
        int t = 0;
        while(token[t] != '\0'){
          if(token[t++] == '['){
            t= 200;
          }
        }
        if( t == 200 ){
          //we know that this exist
          // printf(" This is a braket %s\n",  token); // token has all the item
          //check weather its a stand alone braket or a array
          if(strcmp(token, "[") == 0){
            //This is a stand alone braket
            // printf(" This is the remaining rest:  %s\n",  rest);
            // rest equal to everyhing after the  ']'
          }else{
            char *listName = calloc(MAX_VAR_LEN,sizeof(char));
            char *innertoken = calloc(MAX_VAR_LEN,sizeof(char));
            //, *innertoken = calloc(MAX_VAR_LEN,sizeof(char));
            innertoken = strtok_r(token, "[]", &token); // name of the list
            strcpy(listName,innertoken);
            result->right1_list_name = listName;
            // get the index value
            // printf(" inner token %s\n",  listName); // name of the list
            char *innerindex = calloc(MAX_VAR_LEN,sizeof(char));
            strcpy(innerindex,token);
            result->right1_list_index = innerindex;

            // printf(" token %s\n",  innerindex); // number of the index
          }
          // right_operand1 being like this means that it is an array
          result->right_operand1 = "[]";
          // now i can start to cut this up


        }else{
        // when we dont have brakets
          strcpy(operand,token);
          result->right_operand1 = operand;
        }


          int i = 0;
          // take this out for now
          while(rest[i] != '\0'){
              switch(rest[i++]){
                  case '+':
                      result->optype2 = ADD_OP;
                      break;
                  case '-':
                      result->optype2 = SUB_OP;
                      break;
                  case '*':
                      result->optype2 = MULT_OP;
                      break;
                  case '/':
                      result->optype2 = DIV_OP;
                      break;
                  default:        break;
              }
          }

          token = strtok_r(rest, " +-*/=", &rest);
          if(token!=NULL){
              operand = calloc(MAX_VAR_LEN,sizeof(char));
              strcpy(operand,token);
              result->right_operand2 = operand;
          }else{
              result->right_operand2 = NULL;
          }
        // }

        free(command);
        return result;
    }
}

#include "BOARD.h"
#include "stack.h"
#include "rpn.h"
int x;
#define MAX_INPUT_LENGTH 60

/* RPN_Evaluate() parses and evaluates a string that contains 
 * a valid Reverse Polish Notation string (no newlines!)  
 * @param:  rpn_string - a string in polish notation.  Tokens must be either 
 *          arithmetic operators or numbers.
 * @param:  result - a pointer to a double that will be modified to contain
 *          the return value of the rpn expression.
 * @return: error - if the rpn expression is invalid, 
 *          an appropriate rpn_error value is returned.
 * 
 * RPN_Evaluate supports the following basic arithmetic operations:
 *   + : addition
 *   - : subtraction
 *   * : multiplication
 *   / : division
 * Numeric tokens can be positive or negative, and can be integers or 
 * decimal floats.  RPN_Evaluate should be able to handle strings of 
 * at least 255 length.
 * */
int RPN_Evaluate(char * rpn_string, double * result) {
    char *token;
    strtok(rpn_string, "\n");
    token = strtok(rpn_string, " ");
    while (token != NULL) {
        for (x = 0; x < sizeof (token); x++) {

            if (token[x] != '0' && token[x] != '9' && token[x] != '8' &&
                    token[x] != '7' && token[x] != '6' && token[x] != '5' &&
                    token[x] != '4' && token[x] != '3' && token[x] != '2' &&
                    token[x] != '1' && token[x] != '+' && token[x] != '-' &&
                    token[x] != '/' && token[x] != '*') {
                return RPN_ERROR_INVALID_TOKEN;
            }
        }
    }
    token = strtok(NULL, " ");
    
}


/**
 * This function should read through an array of characters, checking for backspace characters. 
 * When it encounters a backspace character, it eliminates the backspace, the preceeding character
 * (if such a character exists), and shifts all subsequent characters as appropriate.
 * @param string_to_modify The string that will be processed for backspaces. 
 *        This string is modified "in place", so it is both an input and an output to the function.
 * @return Returns the size of the resulting string in "string_to_modify".
 *
 * ProcessBackspaces() should be able to handle multiple repeated backspaces and also
 * strings with more backspaces than characters. It should be able to handle strings of at least 255 length.
 * 
 * */
int ProcessBackspaces(char *rpn_sentence){
    return 0;
}

void MyFunc()
{
   int g = 6;
   {
      int q = g << 3;
      for (; q > 0;) {
          int b = q;
          g *= b;
          q--;
      }
        }
}

m->sideB = 7;

#include "mastermind.h"



#define CODE_LENGTH 4
#define MAX_GUESSES 10
#define NUM_COLORS 9

void generateCode(int* code) {
    srand(time(NULL));
    for (int i = 0; i < CODE_LENGTH; i++) {
        code[i] = rand() % NUM_COLORS;
    }
}

int isValidInput(char* input) {
    int len = strlen(input);
    if (len != CODE_LENGTH) {
        return 0;
    }
    for (int i = 0; i < len; i++) {
        if (input[i] < '0' || input[i] > '8') {
            return 0;
        }
    }
    return 1;
}


// int my_strlen(char *param_1) {

//     char* s;
//     const int chars;
//     for (s=param_1; *s; s++) {

//     return s-param_1;
//     };
//     return chars;
// }

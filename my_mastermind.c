#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

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

int main() {
    int code[CODE_LENGTH];
    generateCode(code);
    int guesses = 0;
    char input[CODE_LENGTH + 1];
    int exactMatches, misplaced;
    printf("Will you find the secret code?\n");
    while (guesses < MAX_GUESSES) {
        printf("Please enter a valid guess\n");
        int bytes_read = read(STDIN_FILENO, input, CODE_LENGTH + 1);
        if (bytes_read <= 0) {
            break;
        }
        input[bytes_read - 1] = '\0'; // remove the trailing newline
        if (!isValidInput(input)) {
            printf("Wrong Input!\n");
            continue;
        }
        // compare the input to the code and print the result
        exactMatches = 0;
        misplaced = 0;
        for (int i = 0; i < CODE_LENGTH; i++) {
            if (code[i] == input[i] - '0') {
                exactMatches++;
            } else {
                for (int j = 0; j < CODE_LENGTH; j++) {
                    if (i != j && code[i] == input[j] - '0') {
                        misplaced++;
                        break;
                    }
                }
            }
        }
        if (exactMatches == CODE_LENGTH) {
            printf("Congratz! You did it!\n");
            return 0;
        } else {
            printf("%d exact matches and %d misplaced pieces\n", exactMatches, misplaced);
        }
        guesses++;
    }
    printf("Sorry, you lost. The code was: %d %d %d %d\n", code[0], code[1], code[2], code[3]);
    return 0;
}

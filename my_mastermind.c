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

int main(int argc, char *argv[]) {
    int code[CODE_LENGTH];
    int max_guesses = MAX_GUESSES;
    if (argc > 1) {
        for (int i = 1; i < argc; i += 2) {
            if (strcmp(argv[i], "-c") == 0) {
                // parse the code from the argument
                if (strlen(argv[i+1]) != CODE_LENGTH) {
                    printf("Invalid code length. Using a random code.\n");
                    generateCode(code);
                } else {
                    for (int j = 0; j < CODE_LENGTH; j++) {
                        if (argv[i+1][j] < '0' || argv[i+1][j] > '8') {
                            printf("Invalid code. Using a random code.\n");
                            generateCode(code);
                            break;
                        }
                        code[j] = argv[i+1][j] - '0';
                    }
                }
            } else if (strcmp(argv[i], "-t") == 0) {
                // parse the number of guesses from the argument
                max_guesses = atoi(argv[i+1]);
                if (max_guesses <= 0) {
                    printf("Invalid number of attempts. Using the default value: %d\n", MAX_GUESSES);
                    max_guesses = MAX_GUESSES;
                }
            } else {
                printf("Unknown parameter: %s\n", argv[i]);
            }
        }
    } else {
        generateCode(code);
    }
    
    printf("Will you find the secret code?\n");
    
    int guesses = 0;
    char input[CODE_LENGTH + 1];
    int exactMatches, misplaced;

    while (guesses < max_guesses) {
        printf("Please enter a valid guess\n");
        int bytes_read = read(STDIN_FILENO, input, CODE_LENGTH + 1);
        if (bytes_read == 0) {
            printf("\nExit\n");
            return 0;
        } else if (bytes_read < 0) {
            printf("Error reading input. Exiting...\n");
            return 1;
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
            printf("Congratz! You did it!");
            return 0;
        } else {
            printf("\nWell placed pieces: %d\nMisplaced pieces: %d\n\n", exactMatches, misplaced);
        }
        guesses++;
    }
    
    printf("Sorry, you lost. The code was: %d %d %d %d\n", code[0], code[1], code[2], code[3]);
    return 0;
}


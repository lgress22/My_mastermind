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
    // Check for command line arguments
    if (argc > 1) {
        // Loop through the arguments
        for (int i = 1; i < argc; i += 2) {
            // If the argument is for the code
            if (strcmp(argv[i], "-c") == 0) {
                // parse the code from the argument
                // Check the length of the code
                if (strlen(argv[i+1]) != CODE_LENGTH) {
                    printf("Invalid code length. Using a random code.\n");
                    // Generate a random code if the length is not valid
                    generateCode(code);
                } else {
                    // Parse the code if the length is valid
                    for (int j = 0; j < CODE_LENGTH; j++) {
                        if (argv[i+1][j] < '0' || argv[i+1][j] > '8') {
                            printf("Invalid code. Using a random code.\n");
                            // Generate a random code if the code is not valid
                            generateCode(code);
                            break;
                        }
                        // Convert the character to an integer
                        code[j] = argv[i+1][j] - '0';
                    }
                }
            // If the argument is for the number of guesses
            } else if (strcmp(argv[i], "-t") == 0) {
                // parse the number of guesses from the argument
                // Convert the argument to an integer
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
        // Generate a random code if no arguments were given
        generateCode(code);
    }
    
    printf("Will you find the secret code?\n");
    
    int guesses = 0;
    char input[CODE_LENGTH + 1];
    int exactMatches, misplaced;


    while (guesses < max_guesses) { // loop until the user runs out of guesses
    printf("Please enter a valid guess\n");
    int bytes_read = read(STDIN_FILENO, input, CODE_LENGTH + 1); // read user input
    if (bytes_read == 0) { // user entered no input
        printf("\nExit\n"); // print exit message
        return 0; // exit program with success status code
    } else if (bytes_read < 0) { // error reading input
        printf("Error reading input. Exiting...\n"); // print error message
        return 1; // exit program with error status code
    }
    input[bytes_read - 1] = '\0'; // remove the trailing newline character from user input
    if (!isValidInput(input)) { // user input is not valid (not 4 digits)
        printf("Wrong Input!\n"); // print message notifying user of invalid input
        continue; // start the next iteration of the loop (skip the rest of the code block)
    }
    // compare the user's input to the code and print the result
    exactMatches = 0; // reset the exactMatches counter for this guess
    misplaced = 0; // reset the misplaced counter for this guess
    for (int i = 0; i < CODE_LENGTH; i++) { // loop over each digit in the code and user input
        if (code[i] == input[i] - '0') { // if the digits match exactly
            exactMatches++; // increment the exactMatches counter
        } else { // if the digits do not match exactly
            for (int j = 0; j < CODE_LENGTH; j++) { // loop over each digit in the user input again
                if (i != j && code[i] == input[j] - '0') { // if the digit appears elsewhere in the user input
                    misplaced++; // increment the misplaced counter
                    break; // break out of the inner loop
                }
            }
        }
    }
    if (exactMatches == CODE_LENGTH) { // if the user guessed the code correctly
        printf("Congratz! You did it!"); // print congratulatory message
        return 0; // exit program with success status code
    } else { // if the user did not guess the code correctly
        printf("\nWell placed pieces: %d\nMisplaced pieces: %d\n\n", exactMatches, misplaced); // print the number of exact and misplaced matches
    }
    guesses++; // increment the number of guesses the user has made
}

printf("Sorry, you lost. The code was: %d %d %d %d\n", code[0], code[1], code[2], code[3]); // print message telling user they lost and reveal the code
return 0; // exit program with success status code
}
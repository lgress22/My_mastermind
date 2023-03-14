#include "mastermind.h"


#define NUM_COLORS 9
#define CODE_LENGTH 4
#define MAX_ATTEMPTS 10

void generate_code(char* code) {
    int used[NUM_COLORS] = {0};
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < CODE_LENGTH; i++) {
        int color;
        do {
            color = rand() % NUM_COLORS;
        } while (used[color]);
        used[color] = 1;
        code[i] = '0' + color;
    }
    code[CODE_LENGTH] = '\0';
}



int validate_input(char* input_str) {
    // Check if input_str is exactly 4 characters long
    if (strlen(input_str) != CODE_LENGTH+1) {
        return -1;
    }
    
    // Check if each character in input_str is a digit
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (!isdigit((unsigned char)input_str[i]) || input_str[i] - '0' > NUM_COLORS - 1) {
            return -1;
        }
    }
    
    return 0;
}


int count_well_placed(char* guess, char* code) {
    int count = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        if (guess[i] == code[i]) {
            count++;
        }
    }
    return count;
}

int count_misplaced(char* guess, char* code) {
    int count = 0;
    for (int i = 0; i < CODE_LENGTH; i++) {
        for (int j = 0; j < CODE_LENGTH; j++) {
            if (i != j && guess[i] == code[j]) {
                count++;
            }
        }
    }
    return count;
}

int main(int argc, char** argv) {
    char code[CODE_LENGTH+1];
    int attempts_left = MAX_ATTEMPTS;
    generate_code(code);

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-c") == 0 && i < argc-1) {
            strncpy(code, argv[i+1], CODE_LENGTH+1);
        } else if (strcmp(argv[i], "-t") == 0 && i < argc-1) {
            attempts_left = atoi(argv[i+1]);
        }
    }

    // Main game loop
    printf("Secret Code: %s\n", code);
    printf("Will you find the secret code? \nPlease enter a valid guess.\n");
    while (attempts_left > 0) {
        char guess[CODE_LENGTH+2];
        //printf("\nPlease enter a valid guess: ");

        // Check the validity of the input
        if (read(STDIN_FILENO, guess, CODE_LENGTH+2) < CODE_LENGTH+1 || guess[CODE_LENGTH] != '\n' || validate_input(guess) != 0) {
            fprintf(stderr, "Wrong input!\n");
            continue;
        }

        // The input is valid, proceed with the game logic
        int well_placed = count_well_placed(guess, code);
        int misplaced = count_misplaced(guess, code);
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well_placed, misplaced);
        if(well_placed == CODE_LENGTH){
            printf("Congratz! You did it!");
            exit(0);
        }
        printf("Please enter a valid guess:\n");
        attempts_left--;
    }

    printf("Sorry, you ran out of attempts. The secret code was %s.\n", code);

return 0;
}
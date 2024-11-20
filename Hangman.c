#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 10
#define MAX_LENGTH 20

// List of words for the game
const char *wordList[MAX_WORDS] = {
    "programming", "hangman", "computer", "science", 
    "education", "keyboard", "development", "language", 
    "function", "variable"
};

// Function prototypes
void chooseWord(char *word);
void initialize(char *guessed, int length);
void displayWord(const char *word, const char *guessed);
int checkWin(const char *word, const char *guessed);
int processGuess(char *guessed, const char *word, char guess);
int playGame();  // Function to play the game

int main() {
    char playAgain;
    
    // Game loop for replay
    do {
        if (playGame()) {
            printf("\nCongratulations! You guessed the word correctly!\n");
        } else {
            printf("\nGame Over! You lost!\n");
        }
        
        // Ask the player if they want to play again
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain); // Leading space ensures to capture any leftover newline character
    } while (playAgain == 'y' || playAgain == 'Y');
    
    printf("Thanks for playing Hangman!\n");
    return 0;
}

// Function to start and play the game
int playGame() {
    char word[MAX_LENGTH];        // The selected word
    char guessed[MAX_LENGTH];     // Tracks correctly guessed letters
    int attempts = 6;             // Maximum incorrect guesses
    char guess;                   // Player's current guess
    int wordLength;
    int win = 0;

    // Seed random number generator
    srand(time(NULL));

    // Select a random word
    chooseWord(word);
    wordLength = strlen(word);

    // Initialize guessed letters
    initialize(guessed, wordLength);

    printf("\nWelcome to Hangman!\n");
    printf("You have %d attempts to guess the word.\n", attempts);

    // Main game loop
    while (attempts > 0) {
        printf("\nWord: ");
        displayWord(word, guessed);

        printf("\nAttempts remaining: %d\n", attempts);
        printf("Enter your guess: ");
        scanf(" %c", &guess);

        // Process the guess
        if (processGuess(guessed, word, guess)) {
            printf("Good guess!\n");
        } else {
            printf("Wrong guess!\n");
            attempts--;
        }

        // Check if the player has won
        if (checkWin(word, guessed)) {
            win = 1;
            break;
        }
    }

    // Return whether the player won or lost
    if (win) {
        return 1;  // Player wins
    } else {
        return 0;  // Player loses
    }
}

// Selects a random word from the word list
void chooseWord(char *word) {
    int index = rand() % MAX_WORDS;
    strcpy(word, wordList[index]);
}

// Initializes the guessed letters array
void initialize(char *guessed, int length) {
    for (int i = 0; i < length; i++) {
        guessed[i] = '_';
    }
    guessed[length] = '\0';
}

// Displays the current state of the word with guessed letters
void displayWord(const char *word, const char *guessed) {
    for (int i = 0; i < strlen(word); i++) {
        printf("%c ", guessed[i]);
    }
    printf("\n");
}

// Checks if the player has guessed the entire word
int checkWin(const char *word, const char *guessed) {
    return strcmp(word, guessed) == 0;
}

// Processes the player's guess and updates guessed letters
int processGuess(char *guessed, const char *word, char guess) {
    int correct = 0;

    for (int i = 0; i < strlen(word); i++) {
        if (word[i] == guess && guessed[i] != guess) {
            guessed[i] = guess;
            correct = 1;
        }
    }

    return correct;
}
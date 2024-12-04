#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORDS 100
#define MAX_LENGTH 50

// Function prototypes
void initialize(char *guessed, int length);
void displayWord(const char *word, const char *guessed);
int checkWin(const char *word, const char *guessed);
int processGuess(char *guessed, const char *word, char guess);
int playGame(const char *word);  // Function to play the game

int main() {
    char wordList[MAX_WORDS][MAX_LENGTH]; // Array to store user-defined words
    int wordCount = 0;                    // Number of words entered by the user
    char playAgain;
    char input[MAX_LENGTH];

    // Prompt the user to input words
    printf("Enter words for Hangman (type 'done' to finish):\n");
    while (wordCount < MAX_WORDS) {
        printf("Word %d: ", wordCount + 1);
        scanf("%s", input);

        // Break the loop if the user types 'done'
        if (strcmp(input, "done") == 0) {
            break;
        }

        // Store the word in the word list
        strcpy(wordList[wordCount], input);
        wordCount++;
    }

    if (wordCount == 0) {
        printf("No words entered. Exiting the game.\n");
        return 0;
    }

    // Show the total number of words entered
    printf("You entered %d words.\n", wordCount);

    // Seed random number generator
    srand(time(NULL));

    // Game loop for replay
    do {
        // Randomly select a word from the word list
        const char *selectedWord = wordList[rand() % wordCount];

        // Play the game with the selected word
        if (playGame(selectedWord)) {
            printf("\nCongratulations! You guessed the word correctly!\n");
        } else {
            printf("\nGame Over! You lost!\n");
            printf("The correct word was: %s\n", selectedWord);
        }

        // Ask the player if they want to play again
        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playAgain); // Leading space ensures to capture any leftover newline character
    } while (playAgain == 'y' || playAgain == 'Y');

    printf("Thanks for playing Hangman!\n");
    return 0;
}

// Function to start and play the game
int playGame(const char *word) {
    char guessed[MAX_LENGTH];  // Tracks correctly guessed letters
    int attempts = 6;          // Maximum incorrect guesses
    char guess;                // Player's current guess
    int wordLength = strlen(word);
    int win = 0;

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
    return win;
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
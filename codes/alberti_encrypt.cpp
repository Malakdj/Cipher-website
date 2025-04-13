#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 1000

// Function to encrypt text using Alberti cipher
void encryptAlberti(char *text, char key_char) {
    char outer_disk[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char inner_disk[] = "abcdefghijklmnopqrstuvwxyz";
    char rotated_inner[26];

    int rotation = key_char - 'a';

    // Prepare rotated inner disk
    for (int i = 0; i < 26; i++) {
        rotated_inner[i] = inner_disk[(i + rotation) % 26];
    }

    // Encrypt the message
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char upper_ch = toupper(text[i]);
            int index = upper_ch - 'A';
            text[i] = rotated_inner[index];
        }
    }
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open input file!\n");
        return 1;
    }

    char key_char;
    char message[MAX_LEN];

    // Read key and message from input file
    fscanf(inputFile, " %c", &key_char);
    fgetc(inputFile); // Consume newline
    fgets(message, MAX_LEN, inputFile);
    fclose(inputFile);

    // Check key validity
    if (key_char < 'a' || key_char > 'z') {
        printf("Error: Key must be a lowercase letter (a-z).\n");
        return 1;
    }

    // Encrypt the message
    encryptAlberti(message, key_char);

    // Print the encrypted message
    printf("Encrypted Message: %s", message);

    return 0;
}

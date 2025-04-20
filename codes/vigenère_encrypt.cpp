#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptVigenere(char *plaintext, char *key, char *ciphertext) {
    int i, j = 0;
    int textLen = strlen(plaintext);
    int keyLen = strlen(key);

    for (i = 0; i < textLen; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            char keyChar = tolower(key[j % keyLen]) - 'a';
            ciphertext[i] = ((tolower(plaintext[i]) - 'a' + keyChar) % 26) + base;
            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open input file!\n");
        return 1;
    }

    char plaintext[1000];
    char key[100];
    char ciphertext[1000];

    // Read plaintext from input file
    fgets(plaintext, sizeof(plaintext), inputFile);
    fclose(inputFile); // Close file after reading

    // Remove newline if exists
    plaintext[strcspn(plaintext, "\n")] = 0;

    // Get the key from the user
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    encryptVigenere(plaintext, key, ciphertext);

    printf("Encrypted text: %s\n", ciphertext);

    return 0;
}

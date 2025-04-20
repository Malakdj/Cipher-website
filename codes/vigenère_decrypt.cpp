#include <stdio.h>
#include <string.h>
#include <ctype.h>

void decryptVigenere(char *ciphertext, char *key, char *plaintext) {
    int i, j = 0;
    int textLen = strlen(ciphertext);
    int keyLen = strlen(key);

    for (i = 0; i < textLen; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char keyChar = tolower(key[j % keyLen]) - 'a';
            plaintext[i] = ((tolower(ciphertext[i]) - 'a' - keyChar + 26) % 26) + base;
            j++;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open input file!\n");
        return 1;
    }

    char ciphertext[1000];
    char key[100];
    char plaintext[1000];

    // Read ciphertext from file
    fgets(ciphertext, sizeof(ciphertext), inputFile);
    fclose(inputFile);

    // Remove newline if exists
    ciphertext[strcspn(ciphertext, "\n")] = 0;

    // Get key from user
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;

    decryptVigenere(ciphertext, key, plaintext);

    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

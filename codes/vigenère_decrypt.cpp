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
            plaintext[i] = ciphertext[i]; // Keep non-alphabetic characters
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char key[100];
    char ciphertext[1000];
    char plaintext[1000];

    // Read key (first line) and ciphertext (second line) from stdin
    if (!fgets(key, sizeof(key), stdin) || !fgets(ciphertext, sizeof(ciphertext), stdin)) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }

    // Remove newlines
    key[strcspn(key, "\n")] = 0;
    ciphertext[strcspn(ciphertext, "\n")] = 0;

    decryptVigenere(ciphertext, key, plaintext);
    printf("%s", plaintext);

    return 0;
}
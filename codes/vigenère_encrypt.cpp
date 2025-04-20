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
    char key[100];
    char plaintext[1000];
    char ciphertext[1000];
    
    // Read key (first line) and plaintext (second line)
    fgets(key, sizeof(key), stdin);
    fgets(plaintext, sizeof(plaintext), stdin);
    
    // Remove newlines
    key[strcspn(key, "\n")] = 0;
    plaintext[strcspn(plaintext, "\n")] = 0;
    
    encryptVigenere(plaintext, key, ciphertext);
    printf("%s", ciphertext);
    
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN 1000

// Function to encrypt text using Caesar cipher
void encryptCaesar(char *text, int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + key) % 26 + base;
        }
    }
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open input file!\n");
        return 1;
    }
    
    int key;
    char message[MAX_LEN];
    
    // Read key and message from input file
    fscanf(inputFile, "%d", &key);
    fgetc(inputFile); // Consume newline
    fgets(message, MAX_LEN, inputFile);
    fclose(inputFile);
    
    // Encrypt the message
    encryptCaesar(message, key);
    
    // Print the encrypted message
    printf("Encrypted Message: %s", message);
    
    return 0;
}

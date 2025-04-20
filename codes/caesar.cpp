#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LEN 1000

void encryptCaesar(char *text, int key) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + key) % 26 + base;
        }
    }
}

int main() {
    FILE *inputFile = fopen("input_caesar.txt", "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error opening input file\n");
        return 1;
    }

    // Read key (first line) and message (second line)
    char key_str[10];
    char message[MAX_LEN];
    
    if (!fgets(key_str, sizeof(key_str), inputFile)) {
        fprintf(stderr, "Error reading key\n");
        fclose(inputFile);
        return 1;
    }
    
    if (!fgets(message, sizeof(message), inputFile)) {
        fprintf(stderr, "Error reading message\n");
        fclose(inputFile);
        return 1;
    }
    
    fclose(inputFile);

    // Remove newlines
    key_str[strcspn(key_str, "\n")] = 0;
    message[strcspn(message, "\n")] = 0;

    int key = atoi(key_str);
    
    encryptCaesar(message, key);
    printf("%s", message);
    
    return 0;
}
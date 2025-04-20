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
    char key_str[10];
    char message[MAX_LEN];
    
    // Read key and message from stdin (piped from server)
    fgets(key_str, sizeof(key_str), stdin);
    fgets(message, sizeof(message), stdin);
    
    // Remove newlines
    key_str[strcspn(key_str, "\n")] = 0;
    message[strcspn(message, "\n")] = 0;
    
    int key = atoi(key_str);
    
    encryptCaesar(message, key);
    printf("%s", message);
    
    return 0;
}
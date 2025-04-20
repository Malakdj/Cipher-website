#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void decryptCaesar(char *message, int shift) {
    for (int i = 0; message[i] != '\0'; i++) {
        char ch = message[i];
        
        if (ch >= 'A' && ch <= 'Z') {
            ch = (ch - 'A' - shift + 26) % 26 + 'A';
        } else if (ch >= 'a' && ch <= 'z') {
            ch = (ch - 'a' - shift + 26) % 26 + 'a';
        }
        
        message[i] = ch;
    }
}

int main() {
    char key_str[10];
    char message[1000];
    
    // Read key and message from stdin
    fgets(key_str, sizeof(key_str), stdin);
    fgets(message, sizeof(message), stdin);
    
    // Remove newlines
    key_str[strcspn(key_str, "\n")] = 0;
    message[strcspn(message, "\n")] = 0;
    
    int shift = atoi(key_str);
    
    decryptCaesar(message, shift);
    printf("%s", message);
    
    return 0;
}
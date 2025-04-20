#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

void decryptCaesar(char *message, int shift) {
    for (int i = 0; message[i] != '\0'; i++) {
        if (isalpha(message[i])) {
            char base = isupper(message[i]) ? 'A' : 'a';
            message[i] = (message[i] - base - shift + 26) % 26 + base;
        }
    }
}

int main() {
    // Read from standard input (key on first line, message on second line)
    char key_str[10];
    char message[1000];
    
    if (!fgets(key_str, sizeof(key_str), stdin) || !fgets(message, sizeof(message), stdin)) {
        fprintf(stderr, "Error reading input\n");
        return 1;
    }
    
    // Remove newlines
    key_str[strcspn(key_str, "\n")] = 0;
    message[strcspn(message, "\n")] = 0;
    
    int shift = atoi(key_str);
    
    decryptCaesar(message, shift);
    printf("%s", message);
    
    return 0;
}
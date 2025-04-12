#include <stdio.h>
#include <string.h>

// Function to decrypt the message using Caesar Cipher
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
    char message[100];
    int shift;
    
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    
    fscanf(file, "%d", &shift);
    fgetc(file); // Consume newline
    fgets(message, sizeof(message), file);
    fclose(file);
    
    decryptCaesar(message, shift);
    
    printf("Decrypted message: %s", message);
    
    return 0;
}

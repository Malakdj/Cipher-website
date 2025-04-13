#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to decrypt the message using Alberti cipher
void decryptAlberti(char *message, char key_char) {
    char outer_disk[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char inner_disk[] = "abcdefghijklmnopqrstuvwxyz";
    char rotated_inner[26];

    int rotation = key_char - 'a';

    // Prepare rotated inner disk
    for (int i = 0; i < 26; i++) {
        rotated_inner[i] = inner_disk[(i + rotation) % 26];
    }

    // Decrypt the message
    for (int i = 0; message[i] != '\0'; i++) {
        char ch = message[i];
        if (islower(ch)) {
            for (int j = 0; j < 26; j++) {
                if (ch == rotated_inner[j]) {
                    message[i] = outer_disk[j];
                    break;
                }
            }
        }
    }
}

int main() {
    char message[100];
    char key_char;

    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    fscanf(file, " %c", &key_char);
    fgetc(file); // Consume newline
    fgets(message, sizeof(message), file);
    fclose(file);

    // Validate key
    if (key_char < 'a' || key_char > 'z') {
        printf("Error: Key must be a lowercase letter (a-z).\n");
        return 1;
    }

    decryptAlberti(message, key_char);

    printf("Decrypted message: %s", message);

    return 0;
}

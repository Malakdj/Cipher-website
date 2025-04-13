#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char outer_disk[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char inner_disk[] = "abcdefghijklmnopqrstuvwxyz";

int find_pos(const char *disk, char c) {
    for (int i = 0; i < 26; i++) {
        if (disk[i] == c) return i;
    }
    return -1;
}

void alberti_decrypt(const char *ciphertext, char *plaintext, char key, int rotate_interval) {
    int shift = find_pos(outer_disk, toupper(key));
    if (shift == -1) {
        printf("Invalid key! Use A-Z.\n");
        return;
    }

    int rotation_counter = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char lower_char = tolower(ciphertext[i]);
            int pos = find_pos(inner_disk, lower_char);
            plaintext[i] = outer_disk[(pos - shift + 26) % 26];
            
            rotation_counter++;
            if (rotation_counter % rotate_interval == 0) {
                shift = (shift + 1) % 26; // Rotate disk
            }
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[100], plaintext[100];
    char key;
    int rotate_interval;

    printf("=== Alberti Cipher Decryption ===\n");
    printf("Enter ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("Enter key (A-Z): ");
    scanf(" %c", &key);
    key = toupper(key);

    printf("Rotation interval: ");
    scanf("%d", &rotate_interval);

    alberti_decrypt(ciphertext, plaintext, key, rotate_interval);
    printf("Decrypted: %s\n", plaintext);

    return 0;
}
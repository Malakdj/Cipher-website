#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LEN 1000

const char outer_disk[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char inner_disk[] = "abcdefghijklmnopqrstuvwxyz";

int find_pos(const char *disk, char c) {
    c = toupper(c);
    for (int i = 0; i < 26; i++) {
        if (disk[i] == c) return i;
    }
    return -1;
}

void alberti_decrypt(const char *ciphertext, char *plaintext, char key, int rotate_interval) {
    // Initial shift should match encryption (A→e is +4)
    int shift = (find_pos(inner_disk, 'e') - find_pos(outer_disk, 'A') + 26) % 26;
    shift = (shift + find_pos(outer_disk, toupper(key))) % 26;

    int rotation_counter = 0;
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char lower_char = tolower(ciphertext[i]);
            int pos = find_pos(inner_disk, lower_char);
            plaintext[i] = outer_disk[(pos - shift + 26) % 26];
            
            rotation_counter++;
            if (rotation_counter % rotate_interval == 0) {
                shift = (shift + 1) % 26; // Rotate disk (must match encryption)
            }
        } else {
            plaintext[i] = ciphertext[i]; // Non-alphabetic
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open input file!\n");
        return 1;
    }
    
    char key_char;
    char key_line[10];
    int rotate_interval;
    char ciphertext[MAX_LEN];
    char plaintext[MAX_LEN];
    
    // Read key (first line)
    if (fgets(key_line, sizeof(key_line), inputFile) == NULL) {
        printf("Error reading key from file!\n");
        fclose(inputFile);
        return 1;
    }
    key_char = key_line[0];
    key_char = toupper(key_char);
    
    // Read rotation interval (second line)
    if (fscanf(inputFile, "%d", &rotate_interval) != 1) {
        printf("Error reading rotation interval from file!\n");
        fclose(inputFile);
        return 1;
    }
    fgetc(inputFile); // Consume newline
    
    // Read ciphertext (third line)
    if (fgets(ciphertext, MAX_LEN, inputFile) == NULL) {
        printf("Error reading ciphertext from file!\n");
        fclose(inputFile);
        return 1;
    }
    fclose(inputFile);
    
    // Remove newline if present
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    
    // Decrypt the message
    alberti_decrypt(ciphertext, plaintext, key_char, rotate_interval);
    
    // Print the decrypted message
    printf("%s", plaintext);
    
    return 0;
}
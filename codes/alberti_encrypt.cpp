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

void alberti_encrypt(const char *plaintext, char *ciphertext, char key, int rotate_interval) {
    // Key 'A' means outer A aligns with inner 'e' (shift of +4)
    int shift = (find_pos(inner_disk, 'e') - find_pos(outer_disk, 'A') + 26) % 26;
    shift = (shift + find_pos(outer_disk, toupper(key))) % 26;

    int rotation_counter = 0;
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char upper_char = toupper(plaintext[i]);
            int pos = find_pos(outer_disk, upper_char);
            ciphertext[i] = inner_disk[(pos + shift) % 26];
            
            rotation_counter++;
            if (rotation_counter % rotate_interval == 0) {
                shift = (shift + 1) % 26; // Rotate disk
            }
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
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
    char plaintext[MAX_LEN];
    char ciphertext[MAX_LEN];
    
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
    
    // Read plaintext (third line)
    if (fgets(plaintext, MAX_LEN, inputFile) == NULL) {
        printf("Error reading plaintext from file!\n");
        fclose(inputFile);
        return 1;
    }
    fclose(inputFile);
    
    // Remove newline if present
    plaintext[strcspn(plaintext, "\n")] = '\0';
    
    // Encrypt the message
    alberti_encrypt(plaintext, ciphertext, key_char, rotate_interval);
    
    // Print the encrypted message
    printf("%s", ciphertext);
    
    return 0;
}
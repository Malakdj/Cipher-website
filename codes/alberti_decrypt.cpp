#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

const char outer_disk[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char inner_disk[] = "abcdefghijklmnopqrstuvwxyz";

int find_pos(const char *disk, char c) {
    for (int i = 0; i < 26; i++) {
        if (disk[i] == c) return i;
    }
    return -1;
}

void alberti_decrypt(char *text, char key_char, int rotate_interval) {
    int shift = find_pos(outer_disk, toupper(key_char));
    if (shift == -1) {
        printf("Invalid key! Use A-Z.\n");
        return;
    }
    
    int rotation_counter = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char lower_char = tolower(text[i]);
            int pos = find_pos(inner_disk, lower_char);
            text[i] = outer_disk[(pos - shift + 26) % 26];
            
            rotation_counter++;
            if (rotation_counter % rotate_interval == 0) {
                shift = (shift + 1) % 26; // Rotate disk
            }
        }
    }
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Unable to open input file!\n");
        return 1;
    }

    char key_char;
    int rotate_interval;
    char message[MAX_LEN];

    // Read key, rotation interval, and message from input file
    fscanf(inputFile, " %c", &key_char);
    fscanf(inputFile, "%d", &rotate_interval);
    fgetc(inputFile); // Consume newline
    fgets(message, MAX_LEN, inputFile);
    fclose(inputFile);

    // Decrypt the message
    alberti_decrypt(message, key_char, rotate_interval);

    // Print the decrypted message
    printf("%s", message);

    return 0;
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 1000

void encryptAlberti(const char* input, char* output, char key_char) {
    char outer_disk[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char inner_disk[] = "abcdefghijklmnopqrstuvwxyz";

    int rotation = key_char - 'a';
    char rotated_inner[27];

    for (int i = 0; i < 26; ++i)
        rotated_inner[i] = inner_disk[(i + rotation) % 26];
    rotated_inner[26] = '\0';

    int j = 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        char ch = toupper(input[i]);
        if (ch >= 'A' && ch <= 'Z') {
            int index = ch - 'A';
            output[j++] = rotated_inner[index];
        } else {
            output[j++] = input[i];
        }
    }
    output[j] = '\0';
}

int main() {
    char message[MAX_LEN], key_char;

    // Step 1: Get input from user
    printf("Enter the message to encrypt: ");
    fgets(message, MAX_LEN, stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter the key (one lowercase letter a-z): ");
    scanf(" %c", &key_char);

    if (key_char < 'a' || key_char > 'z') {
        printf("Invalid key. It must be a lowercase letter from a to z.\n");
        return 1;
    }

    // Step 2: Save to input.txt
    FILE* fout = fopen("input.txt", "w");
    if (!fout) {
        printf("Failed to write to input.txt\n");
        return 1;
    }
    fprintf(fout, "%s\n%c\n", message, key_char);
    fclose(fout);

    // Step 3: Read back from input.txt
    FILE* fin = fopen("input.txt", "r");
    if (!fin) {
        printf("Failed to read from input.txt\n");
        return 1;
    }

    char input[MAX_LEN], key_line[10];
    fgets(input, MAX_LEN, fin);
    fgets(key_line, sizeof(key_line), fin);
    fclose(fin);

    input[strcspn(input, "\n")] = '\0';
    char key = key_line[0];

    // Step 4: Encrypt
    char output[MAX_LEN];
    encryptAlberti(input, output, key);

    // Step 5: Output result
    printf("Encrypted text: %s\n", output);

    return 0;
}

#include <iostream>
#include <string>
#include <cctype>

using namespace std;

string encryptVigenere(const string& plaintext, const string& key) {
    string ciphertext;
    int keyIndex = 0;
    
    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char keyChar = tolower(key[keyIndex % key.length()]) - 'a';
            // Corrected formula with proper parentheses
            ciphertext += static_cast<char>(((tolower(c) - 'a' + keyChar) % 26) + base);
            keyIndex++;
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

int main() {
    string key, plaintext;
    
    // Read key (first line) and plaintext (second line)
    getline(cin, key);
    getline(cin, plaintext);
    
    if (key.empty()) {
        cerr << "Error: Key cannot be empty" << endl;
        return 1;
    }
    
    string ciphertext = encryptVigenere(plaintext, key);
    cout << ciphertext;
    
    return 0;
}
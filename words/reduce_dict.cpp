#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_CHAR = 256;

bool unique_characters(string& str) {

    // If length is greater than 265,
    // some characters must have been repeated
    if (str.length() > MAX_CHAR)
        return false;

    bool chars[MAX_CHAR] = { 0 };
    for (int i = 0; i < str.length(); i++) {
        if (chars[int(str[i])] == true)
            return false;

        chars[int(str[i])] = true;
    }
    return true;
}

bool is_word(string word) {
    for (char const& c : word) {
        if (!isalpha(c)) {
            return false;
        }
    }
    return true;
}

int main(int argc, char const* argv[]) {
    ifstream input_file("words_5.txt");
    if (!input_file.is_open()) {
        cerr << "Problem opening input file." << endl;
        return 1;
    }
    ofstream output_file("words_5_unique.txt");
    if (!output_file.is_open()) {
        cerr << "Problem opening output file." << endl;
        return 1;
    }
    string word;
    while (getline(input_file, word)) {
        if (word.length() == 5 && is_word(word) && unique_characters(word)) {
            for (auto& c : word) c = toupper(c);
            output_file << word << endl;
        }
    }
    output_file.close();
    input_file.close();
    return 0;
}

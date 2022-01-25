#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include "read_csv.cpp"

using namespace std;

#define WORD_LENGTH 5

enum colour {
    NONE = 0, GRAY = 1, YELLOW = 2, GREEN = 3
};

const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

typedef struct remove_pattern {
    remove_pattern(string word, colour colours[]) {
        pattern_word = word;
        for (int i = 0; i < WORD_LENGTH; ++i) {
            pattern_colours[i] = colours[i];
            if (colours[i] == GRAY) gray_chars.insert(word[i]);
        }
    }

    set<char> gray_chars;
    string pattern_word;
    colour pattern_colours[5];

    bool removes(string& word) {
        // prepare the yellow chars that are in there
        map<char, bool> found_chars;
        for (int position = 0; position < WORD_LENGTH; ++position) {
            if (pattern_colours[position] == YELLOW) {
                found_chars[pattern_word[position]] = false;
            }
        }
        // look if the word matches the pattern
        for (int position = 0; position < WORD_LENGTH; ++position) {
            // if we found a green char that we already know is there, continue
            if (pattern_colours[position] == GREEN && word[position] == pattern_word[position]) {
                continue;
            }
            // if a gray char is found, pattern fails
            if (gray_chars.find(word[position]) != gray_chars.end()) {
                return true;
            }
            // if a green char is not found on position, pattern fails
            if (pattern_colours[position] == GREEN && word[position] != pattern_word[position]) {
                return true;
            }
            // if a yellow char is found on the same position, pattern fails
            if (pattern_colours[position] == YELLOW && word[position] == pattern_word[position]) {
                return true;
            }
            found_chars[word[position]] = true;
        }
        // if a yellow char was not found, pattern fails
        for (auto const& entry : found_chars) {
            if (entry.second == false) {
                return true;
            }
        }
        return false;
    }
} remove_pattern;

void remove_words(list<string>& words, vector<remove_pattern> patterns) {
    for (auto it = words.begin(); it != words.end();) {
        string word = *it;
        bool removed = false;
        for (auto& pattern : patterns) {
            if (pattern.removes(word)) {
                it = words.erase(it);
                removed = true;
                break;
            }
        }
        if (!removed) ++it;
    }
}

void print_words(list<string> words) {
    for (const string& word : words) {
        cout << word << endl;
    }
}

int main(int argc, char const* argv[]) {
    // get words
    ifstream input_file("words/en_full_5_long.txt");
    if (!input_file.is_open()) {
        cerr << "Problem opening input file." << endl;
        return 1;
    }
    list<string> words;
    string current_word;
    while (getline(input_file, current_word)) {
        words.push_back(current_word);
    }
    input_file.close();

    int n_items;
    map<string, vector<string>> results = read_csv("wordle.csv", n_items);

    vector<remove_pattern> patterns;
    for (int i = 0; i < n_items; ++i) {
        // get the word
        string word = results["word"][i];
        // get the colours
        colour colours[WORD_LENGTH];
        string s_colours = results["colour"][i];
        for (int c = 0; c < WORD_LENGTH; ++c) {
            colours[c] = static_cast<colour>(s_colours[c] - '0');
        }
        // remove the words
        remove_pattern pattern(word, colours);
        patterns.push_back(pattern);
    }
    remove_words(words, patterns);

    print_words(words);

    return 0;
}

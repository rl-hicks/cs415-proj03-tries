#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include "Trie.h"

using namespace std;

string cleanWord(const string& raw) {
    string result;
    for (char c : raw) {
        if (isalpha(c)) {
            result += tolower(c);
        }
    }
    return result;
}

vector<string> loadWords(const string& filename) {
    vector<string> words;
    ifstream fin(filename);

    if (!fin) {
        cerr << "Error opening file: " << filename << endl;
        return words;
    }

    string raw;
    while (fin >> raw) {
        string cleaned = cleanWord(raw);
        if (!cleaned.empty()) {
            words.push_back(cleaned);
        }
    }

    fin.close();
    return words;
}



int main (int argc, char* argv[]) {


    // We want 3 arguments
    if (argc < 2) {
        cerr << "You need to give a flag (1 or 2) and a file name." << endl;
        return 1;
    }

    // convert CL argument to integer
    int flag = atoi(argv[2]);

    if (flag != 1 && flag != 2) {
        cerr << "Error: flag must be 1 or 2." << endl;
        return 1;
    }

    string filename = argv[1];

    if (filename.find("data/") != 0) {
        filename = "data/" + filename;
    }

    ifstream file(filename);

    if (!file) {
        cerr << "Error opening file." << filename << endl;
        return 1;
    }

    file.close();

    
    vector<string> words = loadWords(filename);

    Trie trie;
    for (const string& word : words) {
        trie.insert(word);
    }

    cout << "Loaded words: " << words.size() << endl;
    cout << "Trie nodes: " << trie.getNodeCount() << endl;

    cout << "\nSearch test:\n";
    cout << "the -> " << trie.search("the") << endl;
    cout << "zzz -> " << trie.search("zzz") << endl;

    cout << "\nAutocomplete test for prefix 'th':\n";
    vector<string> results = trie.autocomplete("th");

    for (const string& word : results) {
        cout << word << endl;
    }








    // if (flag == 1) { ... }
    // else if (flag == 2) { ... }

    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

#include "Trie.h"
#include "BSTTrie.h"

using namespace std;

string cleanWord(const string& raw) {
    string result;

    for (char c : raw) {
        if (isalpha(static_cast<unsigned char>(c))) {
            result += tolower(static_cast<unsigned char>(c));
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

    return words;
}

void printResults(const vector<string>& results) {
    if (results.empty()) {
        cout << "(no matches)";
    } else {
        for (size_t i = 0; i < results.size(); i++) {
            cout << results[i];
            if (i + 1 < results.size()) {
                cout << ", ";
            }
        }
    }
    cout << endl;
}

void runFlag1(Trie& trie, BSTTrie& bstTrie) {
    string query;

    while (true) {
        cout << "\nEnter search string: ";
        cin >> query;

        if (query == "quit") {
            break;
        }

        query = cleanWord(query);

        if (query.empty()) {
            cout << "Please enter a valid search string." << endl;
            continue;
        }

        long long trieSearchOps = 0;
        trie.search(query, trieSearchOps);

        cout << "Time taken to search in the standard Trie is "
             << trieSearchOps << endl;

        long long trieAutoOps = 0;
        vector<string> trieResults = trie.autocomplete(query, trieAutoOps);

        cout << "Auto-complete results using standard Trie are: ";
        printResults(trieResults);

        cout << "Time taken to find auto-complete results in the standard Trie is "
             << trieAutoOps << endl;

        cout << endl;

        long long bstSearchOps = 0;
        bstTrie.search(query, bstSearchOps);

        cout << "Time taken to search in the BST based Trie is "
             << bstSearchOps << endl;

        long long bstAutoOps = 0;
        vector<string> bstResults = bstTrie.autocomplete(query, bstAutoOps);

        cout << "Auto-complete results using BST based Trie are: ";
        printResults(bstResults);

        cout << "Time taken to find auto-complete results in the BST based Trie is "
             << bstAutoOps << endl;
    }
}

void runFlag2(Trie& trie, BSTTrie& bstTrie, const vector<string>& words) {
    long long trieSearchAllOps = 0;
    for (const string& word : words) {
        trie.search(word, trieSearchAllOps);
    }

    long long bstSearchAllOps = 0;
    for (const string& word : words) {
        bstTrie.search(word, bstSearchAllOps);
    }

    cout << endl;
    cout << "Time taken to search all the strings in the standard Trie is "
         << trieSearchAllOps << endl;

    cout << "Time taken to search all the strings in the BST based Trie is "
         << bstSearchAllOps << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: ./autocomplete <filename> <flag>" << endl;
        cerr << "Flag must be 1 or 2." << endl;
        return 1;
    }

    int flag = atoi(argv[2]);

    if (flag != 1 && flag != 2) {
        cerr << "Error: flag must be 1 or 2." << endl;
        return 1;
    }

    string filename = argv[1];

    if (filename.find("data/") != 0) {
        filename = "data/" + filename;
    }

    vector<string> words = loadWords(filename);

    if (words.empty()) {
        cerr << "No valid words found in file." << endl;
        return 1;
    }

    Trie trie;
    long long trieBuildOps = 0;
    for (const string& word : words) {
        trie.insert(word, trieBuildOps);
    }

    BSTTrie bstTrie;
    long long bstBuildOps = 0;
    for (const string& word : words) {
        bstTrie.insert(word, bstBuildOps);
    }

    long long trieSpace = trie.getNodeCount() * 26;
    long long bstSpace = bstTrie.getNodeCount() * 3;

    cout << "Time taken to build the standard Trie is "
         << trieBuildOps
         << " and space occupied by it is "
         << trieSpace << endl;

    cout << "Time taken to build the BST based Trie is "
         << bstBuildOps
         << " and space occupied by it is "
         << bstSpace << endl;

    if (flag == 1) {
        runFlag1(trie, bstTrie);
    } else {
        runFlag2(trie, bstTrie, words);
    }

    return 0;
}
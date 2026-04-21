#include "Trie.h"

using namespace std;

TrieNode::TrieNode() {
    isEndOfWord = false;
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

Trie::Trie() {
    root = new TrieNode();
    nodeCount = 1;
}

Trie::~Trie() {
    destroy(root);
}

void Trie::destroy(TrieNode* node) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < 26; i++) {
        destroy(node->children[i]);
    }

    delete node;
}

void Trie::insert(const string& word, long long& ops) {
    TrieNode* curr = root;
    ops++;

    for (char c : word) {
        ops++;
        int index = c - 'a';
        ops++;

        ops++;
        if (curr->children[index] == nullptr) {
            curr->children[index] = new TrieNode();
            nodeCount++;
            ops++;
        }

        curr = curr->children[index];
        ops++;
    }

    curr->isEndOfWord = true;
    ops++;
}

bool Trie::search(const string& word, long long& ops) const {
    TrieNode* curr = root;
    ops++;

    for (char c : word) {
        ops++;
        int index = c - 'a';
        ops++;

        ops++;
        if (curr->children[index] == nullptr) {
            return false;
        }

        curr = curr->children[index];
        ops++;
    }

    ops++;
    return curr->isEndOfWord;
}

TrieNode* Trie::findPrefixNode(const string& prefix, long long& ops) const {
    TrieNode* curr = root;
    ops++;

    for (char c : prefix) {
        ops++;
        int index = c - 'a';
        ops++;

        ops++;
        if (curr->children[index] == nullptr) {
            return nullptr;
        }

        curr = curr->children[index];
        ops++;
    }

    return curr;
}

void Trie::dfs(TrieNode* node, string& current,
               vector<string>& results, long long& ops) const {
    ops++;
    if (node == nullptr) {
        return;
    }

    ops++;
    if (node->isEndOfWord) {
        results.push_back(current);
        ops++;
    }

    for (int i = 0; i < 26; i++) {
        ops++;
        if (node->children[i] != nullptr) {
            current.push_back('a' + i);
            ops++;

            dfs(node->children[i], current, results, ops);

            current.pop_back();
            ops++;
        }
    }
}

vector<string> Trie::autocomplete(const string& prefix, long long& ops) const {
    vector<string> results;

    TrieNode* start = findPrefixNode(prefix, ops);

    ops++;
    if (start == nullptr) {
        return results;
    }

    string current = prefix;
    ops++;

    dfs(start, current, results, ops);

    return results;
}

long long Trie::getNodeCount() const {
    return nodeCount;
}
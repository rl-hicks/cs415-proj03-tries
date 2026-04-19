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

void Trie::insert(const string& word) {
    TrieNode* curr = root;

    for (char c : word) {
        int index = c - 'a';

        if (curr->children[index] == nullptr) {
            curr->children[index] = new TrieNode();
            nodeCount++;
        }

        curr = curr->children[index];
    }

    curr->isEndOfWord = true;
}

bool Trie::search(const string& word) const {
    TrieNode* curr = root;

    for (char c : word) {
        int index = c - 'a';

        if (curr->children[index] == nullptr) {
            return false;
        }

        curr = curr->children[index];
    }

    return curr->isEndOfWord;
}

TrieNode* Trie::findPrefixNode(const string& prefix) const {
    TrieNode* curr = root;

    for (char c : prefix) {
        int index = c - 'a';

        if (curr->children[index] == nullptr) {
            return nullptr;
        }

        curr = curr->children[index];
    }

    return curr;
}

void Trie::dfs(TrieNode* node, string& current, vector<string>& results) const {
    if (node == nullptr) {
        return;
    }

    if (node->isEndOfWord) {
        results.push_back(current);
    }

    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            current.push_back('a' + i);
            dfs(node->children[i], current, results);
            current.pop_back();
        }
    }
}

vector<string> Trie::autocomplete(const string& prefix) const {
    vector<string> results;
    TrieNode* start = findPrefixNode(prefix);

    if (start == nullptr) {
        return results;
    }

    string current = prefix;
    dfs(start, current, results);

    return results;
}

long long Trie::getNodeCount() const {
    return nodeCount;
}
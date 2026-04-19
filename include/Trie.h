#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>

class TrieNode {
public:
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode();
};

class Trie {
private:
    TrieNode* root;
    long long nodeCount;

    void dfs(TrieNode* node, std::string& current, std::vector<std::string>& results) const;

public:
    Trie();
    ~Trie();

    void insert(const std::string& word);
    bool search(const std::string& word) const;
    TrieNode* findPrefixNode(const std::string& prefix) const;
    std::vector<std::string> autocomplete(const std::string& prefix) const;
    long long getNodeCount() const;

    void destroy(TrieNode* node);
};

#endif
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

    void dfs(TrieNode* node, std::string& current,
             std::vector<std::string>& results, long long& ops) const;

public:
    Trie();
    ~Trie();

    void insert(const std::string& word, long long& ops);
    bool search(const std::string& word, long long& ops) const;
    TrieNode* findPrefixNode(const std::string& prefix, long long& ops) const;
    std::vector<std::string> autocomplete(const std::string& prefix, long long& ops) const;

    long long getNodeCount() const;
    void destroy(TrieNode* node);
};

#endif
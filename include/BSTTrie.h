#ifndef BSTTRIE_H
#define BSTTRIE_H

#include <string>
#include <vector>

class BSTTrieNode;

class BSTChildNode {
public:
    char ch;
    BSTTrieNode* next;
    BSTChildNode* left;
    BSTChildNode* right;

    BSTChildNode(char c);
};

class BSTTrieNode {
public:
    BSTChildNode* childrenRoot;
    bool isEndOfWord;

    BSTTrieNode();
};

class BSTTrie {
private:
    BSTTrieNode* root;
    long long nodeCount;

    BSTChildNode* findChild(BSTChildNode* root, char c, long long& ops) const;
    BSTChildNode* insertChild(BSTChildNode*& root, char c, long long& ops);

    void dfs(BSTTrieNode* node, std::string& current,
             std::vector<std::string>& results, long long& ops) const;

    void traverseChildren(BSTChildNode* childRoot, std::string& current,
                          std::vector<std::string>& results, long long& ops) const;

    void destroyTrie(BSTTrieNode* node);
    void destroyBST(BSTChildNode* node);

public:
    BSTTrie();
    ~BSTTrie();

    void insert(const std::string& word, long long& ops);
    bool search(const std::string& word, long long& ops) const;
    BSTTrieNode* findPrefixNode(const std::string& prefix, long long& ops) const;
    std::vector<std::string> autocomplete(const std::string& prefix, long long& ops) const;

    long long getNodeCount() const;
};

#endif
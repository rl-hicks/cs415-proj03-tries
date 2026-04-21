#include "BSTTrie.h"

using namespace std;

BSTChildNode::BSTChildNode(char c) {
    ch = c;
    next = new BSTTrieNode();
    left = nullptr;
    right = nullptr;
}

BSTTrieNode::BSTTrieNode() {
    childrenRoot = nullptr;
    isEndOfWord = false;
}

BSTTrie::BSTTrie() {
    root = new BSTTrieNode();
    nodeCount = 1;
}

BSTTrie::~BSTTrie() {
    destroyTrie(root);
}

BSTChildNode* BSTTrie::findChild(BSTChildNode* root, char c, long long& ops) const {
    BSTChildNode* curr = root;
    ops++;

    while (curr != nullptr) {
        ops++; // compare for equality
        if (c == curr->ch) {
            return curr;
        }

        ops++; // compare for less-than
        if (c < curr->ch) {
            curr = curr->left;
            ops++;
        } else {
            curr = curr->right;
            ops++;
        }
    }

    return nullptr;
}

BSTChildNode* BSTTrie::insertChild(BSTChildNode*& root, char c, long long& ops) {
    ops++; // check if root is null
    if (root == nullptr) {
        root = new BSTChildNode(c);
        nodeCount += 2; // one BSTChildNode + one BSTTrieNode
        ops++;
        return root;
    }

    ops++; // equality compare
    if (c == root->ch) {
        return root;
    }

    ops++; // less-than compare
    if (c < root->ch) {
        return insertChild(root->left, c, ops);
    }

    return insertChild(root->right, c, ops);
}

void BSTTrie::insert(const string& word, long long& ops) {
    BSTTrieNode* curr = root;
    ops++;

    for (char c : word) {
        ops++; // process character
        BSTChildNode* child = insertChild(curr->childrenRoot, c, ops);
        ops++;

        curr = child->next;
        ops++;
    }

    curr->isEndOfWord = true;
    ops++;
}

bool BSTTrie::search(const string& word, long long& ops) const {
    BSTTrieNode* curr = root;
    ops++;

    for (char c : word) {
        ops++; // process character
        BSTChildNode* child = findChild(curr->childrenRoot, c, ops);
        ops++;

        if (child == nullptr) {
            return false;
        }

        curr = child->next;
        ops++;
    }

    ops++;
    return curr->isEndOfWord;
}

BSTTrieNode* BSTTrie::findPrefixNode(const string& prefix, long long& ops) const {
    BSTTrieNode* curr = root;
    ops++;

    for (char c : prefix) {
        ops++; // process character
        BSTChildNode* child = findChild(curr->childrenRoot, c, ops);
        ops++;

        if (child == nullptr) {
            return nullptr;
        }

        curr = child->next;
        ops++;
    }

    return curr;
}

void BSTTrie::traverseChildren(BSTChildNode* childRoot, string& current,
                               vector<string>& results, long long& ops) const {
    ops++;
    if (childRoot == nullptr) {
        return;
    }

    traverseChildren(childRoot->left, current, results, ops);

    current.push_back(childRoot->ch);
    ops++;

    dfs(childRoot->next, current, results, ops);

    current.pop_back();
    ops++;

    traverseChildren(childRoot->right, current, results, ops);
}

void BSTTrie::dfs(BSTTrieNode* node, string& current,
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

    traverseChildren(node->childrenRoot, current, results, ops);
}

vector<string> BSTTrie::autocomplete(const string& prefix, long long& ops) const {
    vector<string> results;

    BSTTrieNode* start = findPrefixNode(prefix, ops);

    ops++;
    if (start == nullptr) {
        return results;
    }

    string current = prefix;
    ops++;

    dfs(start, current, results, ops);

    return results;
}

void BSTTrie::destroyBST(BSTChildNode* node) {
    if (node == nullptr) {
        return;
    }

    destroyBST(node->left);
    destroyBST(node->right);
    destroyTrie(node->next);
    delete node;
}

void BSTTrie::destroyTrie(BSTTrieNode* node) {
    if (node == nullptr) {
        return;
    }

    destroyBST(node->childrenRoot);
    delete node;
}

long long BSTTrie::getNodeCount() const {
    return nodeCount;
}
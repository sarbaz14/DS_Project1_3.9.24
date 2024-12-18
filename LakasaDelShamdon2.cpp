// In the name of Allah

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int ALPHABET_SIZE = 256;

void print(vector<int> lps){
    cout << "!#!\n";
    for(int i : lps){
        cout << i << " ";
    }
    cout << "\n";
}

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    // TrieNode* children[ALPHABET_SIZE];
    vector<int> indices;
    // TrieNode() {
    //     for (int i = 0; i < ALPHABET_SIZE; i++)
    //         children[i] = nullptr;
    // }
};

void insert(TrieNode* root, string key, int index) {
    TrieNode* node = root;
    for (char c : key) {
        if (!node->children[c])
            node->children[c] = new TrieNode();
        node = node->children[c];
        node->indices.push_back(index);
    }
}

void search(TrieNode* root, string key, vector<int>& result) {
    TrieNode* node = root;
    for (char c : key) {
        if (!node->children[c])
            return;
        node = node->children[c];
    }
    result.insert(result.end(), node->indices.begin(), node->indices.end());
}

void buildSuffixTrie(string text, TrieNode* root) {
    for (int i = 0; i < text.length(); i++)
        insert(root, text.substr(i), i);
}

string findPassword(string text, vector<string>& patterns) {
    TrieNode* root = new TrieNode();
    buildSuffixTrie(text, root);

    string password = "";
    for (string pattern : patterns) {
        vector<int> indices;
        search(root, pattern, indices);
        // print(indices);
        if (!indices.empty()) {
            sort(indices.begin(), indices.end());
            for (int index : indices)
                password += to_string(index);
        }
    }

    return password;
}



int main() {
    string text;
    getline(cin, text);

    int n;
    cin >> n;
    cin.ignore();

    vector<string> patterns(n);
    for (int i = 0; i < n; i++)
        getline(cin, patterns[i]);

    string password = findPassword(text, patterns);
    cout << password << endl;

    return 0;
}

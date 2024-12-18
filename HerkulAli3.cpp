// In the name of Allah

#include <iostream>
#include <vector>
using namespace std;

class Hash
{
private:
    int prime = 31;
    int mod = 1638433;
    long long basePower = 1;

public:
    Hash(int patternLen);

    long long hashFunction(const string& str) {
        long long hash = 0;
        for (char c : str) {
            hash = (hash * prime + c) % mod;
        }
        return hash;
    }

    long long updateHash(long long currentHash, char first, char next){
        currentHash = (currentHash - first * basePower % mod + mod) % mod;
        currentHash = (currentHash * prime + next) % mod;
        return currentHash;
    }

};

Hash::Hash(int patternLen) {
    for (int i = 1; i < patternLen; i++) {
        basePower = (basePower * prime) % mod;
    }
}

vector<int> rabinKarp(const string text, const string pattern) {
    int textLen = text.length();
    int patternLen = pattern.length();
    Hash hash(patternLen);

    long long patternHash = hash.hashFunction(pattern);
    long long currentHash = hash.hashFunction(text.substr(0, patternLen));
    vector<int> result;


    for (int i = 0; i <= textLen - patternLen; ++i) {
        if (currentHash == patternHash && text.substr(i, patternLen) == pattern) {
            result.push_back(i);
        }

        if (i < textLen - patternLen) {
            currentHash = hash.updateHash(currentHash, text[i], text[i + patternLen]);
        }
    }

    return result;
}

int main() {
    string text;
    int n;
    
    getline(cin, text);
    cin >> n;

    vector<string> patterns(n);
    cin.ignore(); // پاک کردن کاراکتر اضافی '\n'
    for (int i = 0; i < n; i++) {
        getline(cin, patterns[i]);
    }

    for (int i = 0; i < n; i++) {
        vector<int> matches = rabinKarp(text, patterns[i]);
        if (matches.empty()) {
            cout << -1;
        } 
        else {
            for (int index : matches) {
                cout << index << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
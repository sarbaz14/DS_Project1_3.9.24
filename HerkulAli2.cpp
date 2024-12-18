// In the name of Allah

#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> computeLPS(const string pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0, i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } 
        else if (len != 0){
            len = lps[len - 1];
        }
        else {
            lps[i] = 0;
            i++;
        }
    }
    return lps;
}

void print(vector<int> lps){
    cout << "!#!\n";
    for(int i : lps){
        cout << i << " ";
    }
    cout << "\n";
}

vector<int> KMPSearch(const string& text, const string& pattern) {
    vector<int> result;
    int n = text.size(), m = pattern.size(), i = 0, j = 0;
    vector<int> lps = computeLPS(pattern);
    print(lps);
    while (i < n) {
        if (pattern[j] == text[i]) i++, j++;
        if (j == m) {
            result.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return result;
}

int main() {
    string text;
    int n;
    vector<string> patterns;
    getline(cin, text);
    cin >> n;
    cin.ignore();
    patterns.resize(n);
    for (int i = 0; i < n; i++) getline(cin, patterns[i]);
    for (const string& pattern : patterns) {
        vector<int> positions = KMPSearch(text, pattern);
        if (positions.empty()) cout << "-1" << endl;
        else {
            for (int pos : positions) cout << pos << " ";
            cout << endl;
        }
    }
    return 0;
}

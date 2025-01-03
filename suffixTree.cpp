// In the name of Allah

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Compare
{
private:
    vector<int> rank;
    int k;
    int n;
public:
    Compare(vector<int> rank, int k, int n) : rank(rank), k(k), n(n) {};

    bool cmp(int i, int j){
        if (rank[i] != rank[j]) return rank[i] < rank[j];
        int ri = i + k < n ? rank[i + k] : -1;
        int rj = j + k < n ? rank[j + k] : -1;
        return ri < rj;
    }
};

vector<int> buildSuffixArray(const string s) {
    int n = s.size();
    vector<int> saffix(n), rank(n), tempRank(n);
    for (int i = 0; i < n; ++i){
        saffix[i]=i;
        rank[i]=s[i];
    }
    for (int k = 1; k < n; k *= 2) {
        Compare compare(rank, k, n);
        sort(saffix.begin(), saffix.end(), [&](int i, int j) {
            return compare.cmp(i, j);
        });
        
        tempRank[saffix[0]] = 0;
        for (int i = 1; i < n; i++) {
            tempRank[saffix[i]] = tempRank[saffix[i - 1]] + (compare.cmp(saffix[i - 1], saffix[i]) ? 1 : 0);
        }
        swap(rank, tempRank);
    }
    return saffix;
}

vector<int> buildLCP(const string s, const vector<int> suffix) {
    int n = s.size();
    vector<int> lcp(n), rank(n);
    for (int i = 0; i < n; i++) {
        rank[suffix[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = suffix[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
            k++;
        }
        lcp[rank[i]] = k;
        if (k) k--;
    }
    return lcp;
}

vector<int> findPatternOccurrences(const string text, const string pattern, const vector<int> suffix, const vector<int> lcp) {
    int n = text.size();
    int m = pattern.size();
    vector<int> result;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = text.compare(suffix[mid], m, pattern);
        if (cmp < 0){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    if (low < n && text.compare(suffix[low], m, pattern) == 0) {
        int start = low;
        while (start > 0 && lcp[start - 1] >= m) {
            start--;
        }
        
        int end = low;
        while (end < n - 1 && lcp[end] >= m) {
            end++;
        }
        
        for (int i = start; i <= end; ++i) {
            result.push_back(suffix[i]);
        }
    }
    return result;
}
int main() {
    string text;
    int q;
    cin >> text >> q;
    vector<int> suffix = buildSuffixArray(text);
    vector<int> lcp = buildLCP(text, suffix);
    while (q--) {
        string pattern;
        cin >> pattern;
        vector<int> occurrences = findPatternOccurrences(text, pattern, suffix, lcp);  
        if (!occurrences.empty()) {
            for (int pos : occurrences) {
                cout << pos << " ";
            }
        } 
        cout << endl;
    }
    return 0;
}

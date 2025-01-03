// In the name of Allah

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
vector<int> buildSuffixArray(const string &s) {
    int n = s.size();
    vector<int> sa(n), rank(n), tempRank(n);
    for (int i = 0; i < n; ++i){
        sa[i]=i;
        rank[i]=s[i];
    }
    for (int k = 1; k < n; k *= 2) {
        auto cmp = [&](int i, int j) {
            if (rank[i] != rank[j]) return rank[i] < rank[j];
            int ri = i + k < n ? rank[i + k] : -1;
            int rj = j + k < n ? rank[j + k] : -1;
            return ri < rj;
        };   
        sort(sa.begin(), sa.end(), cmp);
        
        tempRank[sa[0]] = 0;
        for (int i = 1; i < n; ++i) {
            tempRank[sa[i]] = tempRank[sa[i - 1]] + (cmp(sa[i - 1], sa[i]) ? 1 : 0);
        }
        swap(rank, tempRank);
    }
    return sa;
}
vector<int> buildLCP(const string &s, const vector<int> &sa) {
    int n = s.size();
    vector<int> lcp(n), rank(n);
    for (int i = 0; i < n; ++i) {
        rank[sa[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (rank[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) {
            k++;
        }
        lcp[rank[i]] = k;
        if (k) k--;
    }
    return lcp;
}
vector<int> findPatternOccurrences(const string &text, const string &pattern, const vector<int> &sa, const vector<int> &lcp) {
    int n = text.size();
    int m = pattern.size();
    vector<int> result;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        int cmp = text.compare(sa[mid], m, pattern);
        if (cmp < 0){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    if (low < n && text.compare(sa[low], m, pattern) == 0) {
        int start = low;
        while (start > 0 && lcp[start - 1] >= m) {
            start--;
        }
        
        int end = low;
        while (end < n - 1 && lcp[end] >= m) {
            end++;
        }
        
        for (int i = start; i <= end; ++i) {
            result.push_back(sa[i]);
        }
    }
    return result;
}
int main() {
    string text;
    int q;
    cin >> text >> q;
    vector<int> sa = buildSuffixArray(text);
    vector<int> lcp = buildLCP(text, sa);
    while (q--) {
        string pattern;
        cin >> pattern;
        vector<int> occurrences = findPatternOccurrences(text, pattern, sa, lcp);  
        if (occurrences.empty()) {
        // dakhel in soal toye halati ke ebarat mored nazar daron matn ma nabashe nabayd hichi chap beshe
        } 
        else {
            for (int pos : occurrences) {
                cout << pos << " ";
            }
        }
        cout << endl;
    }
    return 0;
}

// In the name of Allah

#include <iostream>
#include <vector>
#include <string>
using namespace std;

long long hashFunction(const string& str) {
    long long hash = 0;
    int prime = 31;
    int mod = 1638433;
    
    for (char c : str) {
        hash = (hash * prime + c) % mod;
    }
    return hash;
}

// تابع اصلی برای جستجو
vector<int> rabinKarp(const string& text, const string& pattern) {
    int textLen = text.length();
    int patternLen = pattern.length();
    int prime = 31;
    int mod = 1638433;

    long long patternHash = hashFunction(pattern);
    long long currentHash = hashFunction(text.substr(0, patternLen));
    vector<int> result;

    // مقدار پایه برای به‌روز رسانی هش
    long long basePower = 1;
    for (int i = 1; i < patternLen; ++i) {
        basePower = (basePower * prime) % mod;
    }

    // بررسی تمام زیررشته‌های متن
    for (int i = 0; i <= textLen - patternLen; ++i) {
        // اگر مقدار هش برابر بود، مقایسه دقیق انجام شود
        if (currentHash == patternHash && text.substr(i, patternLen) == pattern) {
            result.push_back(i);
        }

        // به‌روز رسانی مقدار هش برای زیررشته بعدی
        if (i < textLen - patternLen) {
            currentHash = (currentHash - text[i] * basePower % mod + mod) % mod;
            currentHash = (currentHash * prime + text[i + patternLen]) % mod;
        }
    }

    return result;
}

int main() {
    string text;
    int n;
    cout << "Enter the main text: ";
    getline(cin, text);

    cout << "Enter the number of patterns: ";
    cin >> n;

    vector<string> patterns(n);
    cin.ignore(); // پاک کردن کاراکتر اضافی '\n'
    for (int i = 0; i < n; ++i) {
        cout << "Enter pattern " << i + 1 << ": ";
        getline(cin, patterns[i]);
    }

    for (int i = 0; i < n; ++i) {
        vector<int> matches = rabinKarp(text, patterns[i]);
        cout << "Pattern \"" << patterns[i] << "\" found at indices: ";
        if (matches.empty()) {
            cout << "None";
        } else {
            for (int index : matches) {
                cout << index << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
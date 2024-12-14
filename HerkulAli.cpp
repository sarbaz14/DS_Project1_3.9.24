// In the name of Allah

#include<iostream>
using namespace std;

struct Node {
    char character;
    int index;
};

class HashTable{
private:
    int size;
    Node* Arr;

public:
    HashTable(int s): size(s), Arr(new Node[s]) {}

};

int main(){
    string text;
    getline(cin, text);

}
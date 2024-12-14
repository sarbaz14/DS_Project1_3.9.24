// In the name of Allah

#include<iostream>
#include<vector>
using namespace std;

struct Node {
    char character;
    int index;
    Node* next;
    Node(char character) : character(character){}
};

class HashTable{
private:
    Node* Arr[131];

    int hashFunction(int c){
        return (c % 131);
    }

public:
    int Insert(char c) {
        int index = hashFunction(c);
        if (Arr[index] == nullptr) {
            Arr[index] = new Node(c);
        }
    }

};

int main(){
    string text;
    getline(cin, text);

}
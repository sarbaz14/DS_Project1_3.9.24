// In the name of Allah

#include<iostream>
#include<vector>
#include<string>
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
        else{
            Node* current = Arr[index];
            while(current->next != nullptr){
                current =current->next;
            }
            current->next = new Node(c); 
        }
    }

};

int main(){
    string text;
    getline(cin, text);
    for(int i=0 ; i<text.length() ;i++){

    }

}
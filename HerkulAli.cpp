// In the name of Allah

#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct Node {
    char character;
    int index;
    Node* next = nullptr;
    Node(char character, int index) : character(character), index(index) {}
};

class HashTable{
private:
    Node* Arr[131];

    int hashFunction(int c){
        return (c % 131);
    }

    void Insert(char c, int mainIndex) {
        int index = hashFunction(c);
        if (Arr[index] == nullptr) {
            Arr[index] = new Node(c, mainIndex);
        }
        else{
            Node* current = Arr[index];
            while(current->next != nullptr){
                current =current->next;
            }
            current->next = new Node(c, mainIndex); 
        }
    }

public:
    void Input(string text){
        for(int i = 0; i < text.length(); i++){
           Insert(text[i],i);
        }
    }

};

int main(){
    string text;
    getline(cin, text);
    

}
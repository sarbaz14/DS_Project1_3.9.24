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

    // int searchIndex(vector<int>* indexsInput, int size){
    //     for (int i = 0; i < size; i++){
    //         for (int j = 0; j < indexsInput[i].size(); j++){
    //             int index = indexsInput[i][j].index;
    //         }
    //     }
    // }

public:
    void Input(string text){
        for(int i = 0; i < text.length(); i++){
           Insert(text[i],i);
        }
    }

    void Search(string* inputs, int size){
        for (int i = 0; i < size; i++){
            string input = inputs[i];

            vector<int> indexsInput[input.length()];
            for (int j = 0; j < input.length(); j++){
                int index = hashFunction(input[j]);

                Node* current = Arr[index];
                while(current->next != nullptr){
                    indexsInput[j].push_back(current->index);
                    current =current->next;
                }
            }



        }

    }
};

int main(){
    HashTable hashTable;
    string text;
    getline(cin, text);

    hashTable.Input(text);
    
    int num;
    cin >> num;
    string inputs[num];
    for (int i = 0; i < num; i++){
        getline(cin, inputs[i]);
    }



}
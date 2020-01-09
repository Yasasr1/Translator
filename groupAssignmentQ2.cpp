#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include<bits/stdc++.h> 
#include <regex>

using namespace std;

int tableSize = 3000;

class HashNode{
    public:
        string english;
        string french;
        string spanish;

    HashNode(string eng, string fre, string spa){
        this->english = eng;
        this->french = fre;
        this->spanish = spa;
    }
};

class HashTable{
    public:
        list<HashNode> *hashTable;

    HashTable(){
        hashTable = new list<HashNode>[tableSize];
    }

    int hashFunction(string const& word){
        const int p = 31;
        int hash_value = 0;
        int p_pow = 1;
        for (char c : word) {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % tableSize;
            p_pow = (p_pow * p) % tableSize;
        }
        return hash_value;
    }

    void insert(string eng,string fre, string spa){
        int hash = hashFunction(eng);
        HashNode node(eng,fre,spa);
        hashTable[hash].push_back(node);
    }

    string search(string eng,string language){
        int hash = hashFunction(eng);
        string output;
        list<HashNode> :: iterator i;
        for(i = hashTable[hash].begin(); i != hashTable[hash].end(); i++){
            if(i->english == eng){
                if(language == "fre")
                    return i->french;
                else if(language == "spa")
                    return i->spanish;
                break;
            }
        }
        if(i->english != eng){
            return "["+eng+"]";
    
        }
    }

};

int main(int argc, char** argv){
    HashTable table;

    fstream dictionaryFile;

    dictionaryFile.open("dictionary.csv",ios::in);
    if(dictionaryFile.is_open()){
        string line;
        string word;
        vector<string> words;

        while(getline(dictionaryFile, line)){
            transform(line.begin(), line.end(), line.begin(), ::tolower); 
            for(int i=0; i<=line.length(); i++){
                if(line[i] == ',' || i == line.length()){
                    words.push_back(word);
                    word.erase();
                }
                else
                {
                    word=word+line[i];
                }
                
            }
            table.insert(words[0],words[1],words[2]);
            words.clear();
            line.erase();
        }
        dictionaryFile.close();
        
    }

    fstream englishText;
    regex reg1("(is\\s)|(the\\s)|(a\\s)|(an\\s)|(did\\s)|(it\\s)|(\\?)");  // Find double word.
    string replacement = ""; 

    if(argc<2)
        englishText.open("text.txt",ios::in);
    else
        englishText.open(argv[1],ios::in);
    if(englishText.is_open()){
       string engLine;
       
        while(getline(englishText, engLine)){
            cout << "English text: " << engLine << endl;
            string result = regex_replace(engLine, reg1, replacement);
            transform(result.begin(), result.end(), result.begin(), ::tolower);
            //cout << result; 
            string translation;
            string engWord = "";

            cout << "French translation: ";
            for(int i=0; i<=result.length(); i++){
                if(result[i] == ' ' || i == result.length()){
                    translation = table.search(engWord,"fre");
                    cout << translation << " ";
                    if(i == result.length()){
                        cout << endl;
                    }
                    engWord.erase();
                }
                else
                {
                    engWord=engWord+result[i];
                }   
            }

            cout << "Spanish translation: ";
            for(int i=0; i<=result.length(); i++){
                if(result[i] == ' ' || i == result.length()){
                    translation = table.search(engWord,"spa");
                    cout << translation << " ";
                    if(i == result.length()){
                        cout << endl;
                    }
                    engWord.erase();
                }
                else
                {
                    engWord=engWord+result[i];
                }    
            }
        }
        englishText.close();
    }
    return 0;
}
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
        //cout << "Hash value " << hash_value << endl; 
        return hash_value;
    }

    void insert(string eng,string fre, string spa){
        int hash = hashFunction(eng);
        HashNode node(eng,fre,spa);
        hashTable[hash].push_back(node);
    }

    string search(string eng){
        int hash = hashFunction(eng);
        list<HashNode> :: iterator i;
        for(i = hashTable[hash].begin(); i != hashTable[hash].end(); i++){
            if(i->english == eng){
                //cout << "french: " << i->french << " spanish: " << i->spanish << endl;
                return i->french;
                break;
            }
        }
        if(i->english != eng){
            //cout << "not found" << endl;
            return "["+eng+"]";
    
        }
    }

};

int main(){
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
            //cout << words[0] << " " << words[1] << " " << words[2] << endl;
            table.insert(words[0],words[1],words[2]);
            words.clear();
            line.erase();
        }
        dictionaryFile.close();
        /*string one = table.search("yasas");
        string two = table.search("bag");
        string three = table.search("your");
        string four = table.search("station");
        cout << one << " " << two << " " << three << " " << four;*/

        
        dictionaryFile.close();

        
    }

    fstream englishText;
    regex reg1("(is\\s)|(the\\s)|(a\\s)");  // Find double word.
    string replacement = ""; 

    englishText.open("text.txt",ios::in);
    if(englishText.is_open()){
       string engLine;
        while(getline(englishText, engLine)){
            //cout << engLine;
            string result = regex_replace(engLine, reg1, replacement);
            transform(result.begin(), result.end(), result.begin(), ::tolower);
            cout << result; 


        }
        englishText.close();


    }

    /*regex reg1("(is\\s)|(the\\s)|(a\\s)");  // Find double word.
         // Replace with one word.

    string target = "where is the train station";
    string result = regex_replace(target, reg1, replacement);
    std::cout << result << std::endl;*/
        

    return 0;

}
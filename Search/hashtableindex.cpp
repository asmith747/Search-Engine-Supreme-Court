#include "hashtableindex.h"
#include "cstring"
#include <algorithm>
#include <iomanip>
#include <dirent.h>
#include <sys/stat.h>

HashTableIndex::HashTableIndex()
{
}

HashTableIndex::~HashTableIndex()
{
    delete [] data;
}

void HashTableIndex::insert(Data& dat)
{

    size++;
    Data temp = dat;
    hash<string> Hash;
    size_t element = Hash(temp.getWord());
    int index = static_cast<int>(element);
    index = index % tableSize;
    if(index<0)
        index = index * -1;
//    for (int t = 0; t < data[index].size(); t++) {
//        if (data[index][t] == dat) {
//            cout << "INSERTED\n";
//            data[index][t] = dat;
//            return;
//        }
//    }
    data[index].push_back(temp);
}

bool HashTableIndex::find(Data& dat)
{

    Data temp = dat;
    hash<string> Hash;
    size_t element = Hash(temp.getWord());
    int index = static_cast<int>(element);
    index = index % tableSize;
    if(index<0)
        index = index * -1;
    for (int i = 0; i < data[index].size(); i++) {	//if not found, then just return the object passed to it
        if (data[index][i] == temp){
            return true;
        }
    }
    return false;
}

void HashTableIndex::addFiles(string path)
{

}

Data& HashTableIndex::update(Data dat)
{
    Data temp = dat;
    hash<string> Hash;
    size_t element = Hash(dat.getWord());
    int index = static_cast<int>(element);
    index = index % tableSize;
    if(index < 0)
        index = index * -1;
    for(int i=0; i < data[index].size(); i++){
        if(data[index][i] == dat)
            return data[index][i];
    }
}

Data HashTableIndex::getTop(string word)
{
    Data temp(word, 0);
    hash<string> Hash;
    size_t element = Hash(word);
    int index = static_cast<int>(element);
    index = index % tableSize;
    if(index < 0)
        index = index * -1;
    for(int i=0; i < data[index].size(); i++){
        if(data[index][i] == temp)
            return data[index][i];
    }
}

void HashTableIndex::printToFile(ofstream& out)
{
    for(int i=0; i< tableSize; i++){
        for(int j=0; j< data[i].size(); j++){
            out << data[i][j];
        }
    }
    out << "-1";
    return;
}


int HashTableIndex::printCommon(bool com)
{
    if(com){
        vector<tuple<int, string>> top;
        int count = 0;
        for(int i=0; i< tableSize; i++){
            for(int j=0; j< data[i].size(); j++){
                top.push_back(make_tuple(0, data[i][j].getWord()));
                for(auto const& x : data[i][j].getInfo())
                    get<0>(top[count]) += x.second;
                count++;
            }
        }
        sort(top.begin(), top.end());

        int counter = 1;
        cout << left;
        for(int i=top.size()-1; i>top.size()-51; i--){
            cout << " "<< setw(2) << counter <<": "<<setw(10)
                 <<get<1>(top[i]) << " (" << get<0>(top[i]) << ")";

            if((counter)%3 == 0)
                cout << endl;
            counter++;
        }
        return 0;
    } else
        return size;
}


bool HashTableIndex::readFromFile(char* const argv[])
{
    delete [] data;
    data = new vector<Data>[15000000];
    size = 0;
    ifstream index(argv[3]);


    bool empty = false;
    while(!index.eof()){
        map<int, int> caseValue;
        char str[1000000];
        index.getline(str, '1000000', '\n');
        char *toke = strtok(str, " ");

        if(toke == NULL){
            empty = true;
            break;
        }

        string word(toke);
        bool cont = false;
        bool first = true;
        int contInt = 0;
        int one = 0;
        int two = 0;
        bool add = false;

        while(toke != NULL){
            if(cont){
                if(first){
                    contInt = 1;
                    one = atoi(toke);
                    add = false;
                }
                if(!first){
                    contInt = 2;
                    two = atoi(toke);
                    add = true;
                }
                if(contInt == 1)
                    first = false;
                if(contInt == 2)
                    first = true;
            }
            if(add)
                caseValue[one] = two;
            cont = true;
            toke = strtok(NULL, " ");
        }
        Data intoHash(caseValue, word);
        insert(intoHash);
    }

    if(empty){
        cout << " -- INDEX HAS NOT YET BEEN CREATED\n\n"
             << " -- Go into maintenance mode to create\n\n";
        return true;
    }
    else
        return false;

}

void HashTableIndex::print()
{
    for(int i=0; i< tableSize; i++){
        for(int j=0; j< data[i].size(); j++){
            cout << data[i][j];
        }
    }
}

void HashTableIndex::getData(string word)
{
    Data temp(word, 0);
    hash<string> Hash;
    size_t element = Hash(temp.getWord());
    int index = static_cast<int>(element);
    index = index % tableSize;
    if(index<0)
        index = index * -1;
    for (int i = 0; i < data[index].size(); i++) {	//if not found, then just return the object passed to it
        if (data[index][i] == temp){
                cout << data[index][i];
                return;
            }
    }
    cout << "WORD NOT FOUND" << endl;
}

int HashTableIndex::getSize()
{
    int length = 0;
    for (int x = 0; x < tableSize; x++) {
        for (int y = 0; y < data[x].size(); y++) {
                length++;
            }
    }
    return size;
}

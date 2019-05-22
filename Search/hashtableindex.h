#ifndef HASHTABLEINDEX_H
#define HASHTABLEINDEX_H

#include <iostream>
#include <string>
#include <data.h>
#include "avltree.h"
#include <array>
#include <vector>


using namespace std;

class HashTableIndex : public IndexInterface
{
private:
    vector<Data>* data = new vector<Data>[15000000];
    int tableSize = 15000000;
    int size = 0;

public:
    HashTableIndex();
    ~HashTableIndex();
    void insert(Data&);
    int getSize();
    void print();
    bool readFromFile(char* const argv[]);
    void getData(string);
    void printToFile(ofstream&);
    bool find(Data&);
    Data& update(Data);
    Data getTop(string);
    int printCommon(bool);
    void addFiles(string);
};

#endif // HASHTABLEINDEX_H

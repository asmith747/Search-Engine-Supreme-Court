#ifndef INDEXINTERFACE_H
#define INDEXINTERFACE_H

#include <map>
#include "data.h"
#include <ostream>
#include <iostream>
#include <vector>

using namespace std;

class IndexInterface
{
public:
    IndexInterface();

//    virtual ~IndexInterface();
    virtual void insert(Data&) = 0;
    virtual void print() = 0;
    virtual bool find(Data&) = 0;
    virtual Data& update(Data) = 0;
    virtual void printToFile(ofstream&) = 0;
    virtual int getSize() = 0;
    virtual void getData(string) = 0;
    virtual bool readFromFile(char * const argv[]) = 0;
    virtual Data getTop(string) = 0;
    virtual int printCommon(bool) = 0;
    virtual void addFiles(string) = 0;
};
inline IndexInterface::IndexInterface(){}
//IndexInterface::~IndexInterface(){}


#endif // INDEXINTERFACE_H

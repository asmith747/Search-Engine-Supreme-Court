#ifndef INDEXHANDLER_H
#define INDEXHANDLER_H
#include "parse.h"
#include "indexinterface.h"
#include "data.h"
#include "avltree.h"
#include "avltreeindex.h"
#include "hashtableindex.h"
#include <ostream>
#include <fstream>

using namespace std;
class IndexHandler
{
public:
    IndexHandler();
    void print();
    void output();
    int getSize();
    void getData(string);
    void parseFiles(char * const argv[], int);
    bool readFromFile(char * const argv[]);
    int getDirSize(char * const argv[]);
    int printCommon(bool);
    void addFiles(char * const argv[], string, int);

    IndexInterface* indexAVL = new AVLTreeIndex;
    IndexInterface* indHash = new HashTableIndex;

    char dataSelect = '0';

private:
    Parse par;
    ofstream out;
    vector<string> anames;
    vector<string> fnames;
};

#endif // INDEXHANDLER_H

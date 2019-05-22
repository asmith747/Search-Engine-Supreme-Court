#ifndef PARSE_H
#define PARSE_H

#include <iostream>
#include <fstream>
#include <vector>
#include "manip.h"
#include "data.h"
#include "indexinterface.h"

using namespace std;

class Parse
{
public:
    Parse();
    void readDir(char * const argv[], bool, vector<string>&, string);
    void addWords(IndexInterface *&, bool, vector<string>);
    int getDirSize(char * const argv[]);
    void addStop(char * const argv);

private:
    AVLTree<string> stopWords;
  //  vector<string> fnames;
    ifstream fs;
    ifstream st;
    Manip man;
};

#endif // PARSE_H

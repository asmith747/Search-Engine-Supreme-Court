#ifndef MANIP_H
#define MANIP_H
#include <iostream>
#include <fstream>
#include <vector>
#include "indexinterface.h"
#include "data.h"
#include "avltree.h"
#include <sstream>


using namespace std;

class Manip
{
public:
    Manip();
    ~Manip();
    void addStop(char* const argv[]);
    void addHTML(string, int, IndexInterface*&);
    void addPlain(string, int, IndexInterface*&);
    void addWords(string, int, IndexInterface*&);
    void singleFile(string, bool);
    void parseCase(string, int, IndexInterface*&);

private:
    ifstream st;
    vector<string> stp;
    AVLTree<string> stopWords;

};

#endif // MANIP_H

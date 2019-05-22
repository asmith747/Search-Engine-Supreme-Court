#ifndef QUERYHANDLER_H
#define QUERYHANDLER_H
#include <iostream>
#include <vector>
#include <sstream>
#include "porter2_stemmer/porter2_stemmer.h"

using namespace std;
using namespace Porter2Stemmer;

class QueryHandler
{
private:
    vector<string> AND;
    vector<string> OR;
    vector<string> NOT;
    vector<string> ONE;

public:
    QueryHandler();
    bool userInput(string line);
    bool setAndOrNot(vector<string>, int);
    void printAndOrNot();

    vector<string> getAND();
    vector<string> getOR();
    vector<string> getNOT();
    vector<string> getONE();
};

#endif // QUERYHANDLER_H

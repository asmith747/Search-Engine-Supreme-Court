#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H

#include <vector>
#include <iostream>
#include "indexinterface.h"
#include "data.h"
#include <map>

using namespace std;

class SearchEngine
{
public:
    SearchEngine();
    void search(string);
    bool searchONE(IndexInterface*, vector<string>);
    bool searchAND(IndexInterface*, vector<string>, vector<string>, bool);
    bool searchOR(IndexInterface*, vector<string>, vector<string>, bool);
    bool printTop(vector<tuple<int, int, int>>, int);
    bool sortBySecond(const tuple<int, int, int>&, const tuple<int, int, int>&);
};

#endif // SEARCHENGINE_H

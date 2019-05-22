#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "indexhandler.h"
#include "searchengine.h"
#include "porter2_stemmer/porter2_stemmer.h"
#include "queryhandler.h"
#include <ostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <sstream>
#include "manip.h"


using namespace std;
using namespace Porter2Stemmer;

class UserInterface
{
public:
    UserInterface();
    void menu(char * const argv[], bool end);
    void interactive(char * const argv[]);
    void maintenance(char * const argv[]);
    void setIndex(char * const argv[], int);
    void getFile(char * const argv[], int);
    void binSearch(char * const argv[], int);
    void displayFile(char * const argv[], string, int, int);
    void searchAgain(char * const argv[], int);
    
private:
    string directory;
    IndexHandler ind;
    QueryHandler query;
    SearchEngine search;
    Manip man;
    vector<string> anames;

};

#endif // USERINTERFACE_H

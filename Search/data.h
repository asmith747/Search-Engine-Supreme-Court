#ifndef DATA_H
#define DATA_H
#include <map>
#include <iostream>
#include <fstream>


using namespace std;

class Data
{
public:
    Data();
    ~Data();
    Data(string, int);
    Data(map<int, int>, string);
    string getWord();
    void incrementMap(int);
    map<int, int> getInfo();
    void addOne(int);

    bool operator < (const Data&) const;
    bool operator > (const Data&) const;
    Data& operator+=(const Data&);
    bool operator== (const Data&);
    Data& operator =(const Data&);
    friend ostream& operator << (ostream&, const Data&);
    friend ofstream& operator << (ofstream&, const Data&);


private:
    map<int, int> info;
    string word;
};

#endif // DATA_H

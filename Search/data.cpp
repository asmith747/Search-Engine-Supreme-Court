#include "data.h"
#include "cstring"

Data::Data()
{

}

Data::Data(string wd, int id)
{
    word = wd;
    info[id] = 0;
}

Data::~Data(){}

Data::Data(map<int, int> values, string wd)
{
    word = wd;
    info = values;
}

void Data::addOne(int id)
{
    info[id] = 1;
}

bool Data::operator < (const Data& d) const
{
    if(word < d.word)
            return true;
        else
            return false;
}

string Data::getWord()
{
    return word;
}

map<int, int> Data::getInfo()
{
    return info;
}


bool Data::operator > (const Data& d) const
{
    if(word > d.word)
        return true;
    else
        return false;
}

void Data::incrementMap(int id){
    for(auto const& x : info){
        if(x.first == id){
            info[id]++;
            return;
        }else
            info[id] = 1;
    }
    return;
}

bool Data::operator==(const Data& equal)
{
    return word == equal.word;
}

Data& Data::operator=(const Data& assign)
{
    info = assign.info;
    word = assign.word;
    return *this;
}

Data& Data::operator+= (const Data& dat)
{
    for(auto const& x : dat.info){
        info[x.first] = x.second;
    }
    return *this;
}

//Console output
ostream& operator << (ostream& out, const Data& in)
{
    int sum = 0;
    out << "Found: '" << in.word << "' in:\n";
    for(auto const& x : in.info){
        sum += x.second;
         out << " - Case: " << x.first << ", " << x.second << " times\n";
    }
    cout << "Total: " << sum << " times" << endl;
    return out;
}


//Output file
ofstream& operator << (ofstream& out, const Data& in)
{
    out << in.word << " ";
    for(auto const& x : in.info){
         out<< x.first << " " << x.second << " ";
    }
    out << "\n";
    return out;
}

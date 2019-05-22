#include "queryhandler.h"

QueryHandler::QueryHandler()
{

}

bool QueryHandler::userInput(string input)
{
    AND.clear();
    OR.clear();
    NOT.clear();
    ONE.clear();
    vector<string> search;
    stringstream strstr(input);
    bool one = false;
    while(strstr.good()){
        string word;
        getline(strstr, word, ' ');
        if(word != "NOT" && word != "OR" && word!= "AND" && word.size() >1){
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            stem(word);
        }
        search.push_back(word);
    }
    return setAndOrNot(search, 0);
}

void QueryHandler::printAndOrNot()
{
    cout << "AND: ";

    for(int i=0; i<AND.size(); i++)
        cout << AND[i] << " ";
    cout << endl;

    cout << "OR: ";
    for(int i=0; i<OR.size(); i++)
        cout << OR[i] << " ";
    cout << endl;

    cout << "NOT: ";
    for(int i=0; i<NOT.size(); i++)
        cout << NOT[i] << " ";
    cout << endl;

    cout << "ONE: ";
    for(int i=0; i<ONE.size(); i++)
        cout << ONE[i] << " ";
    cout << endl;
}

bool QueryHandler::setAndOrNot(vector<string> inp, int ind)
{
    bool valid = true;
    if(ind <= inp.size()-1){
        if(inp[ind] == "AND"){
            int j = ind;
            while(inp[j] != "OR" && inp[j] != "NOT"  && j < inp.size()-1){
                j++;
                if(inp[j] != "OR" && inp[j] != "NOT" && j < inp.size()){
                    AND.push_back(inp[j]);
                }else{
                     return setAndOrNot(inp,j);
                }
            }
        }else if(inp[ind] == "OR"){
            int j = ind;
            while(inp[j] != "AND" && inp[j] != "NOT" && j < inp.size()-1){
                j++;
                if(inp[j] != "AND" && inp[j] != "NOT" && j < inp.size()){
                    OR.push_back(inp[j]);
                }else{
                     return setAndOrNot(inp,j);
                }
            }
        }else if(inp[ind] == "NOT"){
            int j = ind;
            while(inp[j] != "AND" && inp[j] != "OR" && j < inp.size()-1){
                j++;
                if(inp[j] != "AND" && inp[j] != "NOT" && j < inp.size()){
                    NOT.push_back(inp[j]);
                }else{
                     return setAndOrNot(inp,j);
                }
            }
        }else if(ind == 0 && inp[0]!= "OR" && inp[0]!= "AND" && inp[0]!= "NOT"){
            ONE.push_back(inp[0]);
            if(inp.size() > 1){
                cout << "\nInput without AND or OR must be one word\n";
                valid = false;
            }
        }
    }
    return valid;
}

vector<string> QueryHandler::getAND()
{
    return AND;
}

vector<string> QueryHandler::getOR()
{
    return OR;
}

vector<string> QueryHandler::getNOT()
{
    return NOT;
}

vector<string> QueryHandler::getONE()
{
    return ONE;
}

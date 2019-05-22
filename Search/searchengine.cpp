#include "searchengine.h"
#include <algorithm>

SearchEngine::SearchEngine()
{

}

bool SearchEngine::searchONE(IndexInterface* data, vector<string> ONE)
{
    if(ONE.size() >1){
        cout << "\nWithout AND or OR search, input must be one word\n";
        return false;
    }
    vector<tuple<int, int, int>> info;

    for(auto const& x : data->getTop(ONE[0]).getInfo())
        info.push_back(make_tuple(x.first, x.second, 1));

    return printTop(info, 1);
}

bool SearchEngine::searchAND(IndexInterface* data, vector<string> AND, vector<string> NOT, bool andNOT)
{
    if(AND.size()<=1){
        cout << "\nFor AND input more than one word is required\n";
        return false;
    }

    vector<Data> words;
    vector<Data> wordsNOT;
    for(int i=0; i< AND.size(); i++)
        words.push_back(data->getTop(AND[i]));
    for(int i=0; i< NOT.size(); i++)
        wordsNOT.push_back(data->getTop(NOT[i]));

    vector<tuple<int, int, int>> info;
    for(auto const& x : words[0].getInfo()){
        info.push_back(make_tuple(x.first, x.second, 1));

        for(int j=1; j<words.size(); j++){
            for(auto const& y : words[j].getInfo()){
                if(y.first == x.first){
                    for(int h=0; h<info.size(); h++){
                        if(y.first == get<0>(info[h])){
                            get<1>(info[h]) += y.second;
                            get<2>(info[h])++;
                        }
                    }
                }
            }
        }
    }
    if(andNOT){
        for(int i=0; i<wordsNOT.size(); i++){
            for(auto const& x : wordsNOT[i].getInfo()){
                for(int h=0; h<info.size(); h++){
                    if(x.first == get<0>(info[h]))
                        get<0>(info[h]) = 0;
                }
            }
        }
    }
    return printTop(info, words.size());
}


bool SearchEngine::searchOR(IndexInterface* data, vector<string> OR, vector<string> NOT, bool andNOT)
{
    if(OR.size()<=1){
        cout << "For OR input more than one word is required\n";
        return false;
    }

    vector<Data> words;
    vector<Data> wordsNOT;
    for(int i=0; i< OR.size(); i++)
        words.push_back(data->getTop(OR[i]));
    for(int i=0; i< NOT.size(); i++)
        wordsNOT.push_back(data->getTop(NOT[i]));

    vector<tuple<int, int, int>> info;

    for(int i=0; i<words.size(); i++){
        for(auto const& x : words[i].getInfo()){
            bool found = false;
            for(int j=0; j<info.size(); j++){
                if(get<0>(info[j]) == x.first){
                    get<1>(info[j]) += x.second;
                    found = true;
                    break;
                }
            }
            if(!found)
                info.push_back(make_tuple(x.first, x.second, 1));
        }
    }

    if(andNOT){
        for(int i=0; i<wordsNOT.size(); i++){
            for(auto const& x : wordsNOT[i].getInfo()){
                for(int h=0; h<info.size(); h++){
                    if(x.first == get<0>(info[h]))
                        get<0>(info[h]) = 0;
                }
            }
        }
    }

    return printTop(info, 1);
}


bool SearchEngine::printTop(vector<tuple<int, int, int>> info, int min)
{
    bool sortBySecond(const tuple<int, int, int>& a, const tuple<int, int, int>& b);
    cout << "\n ---------------------\n"
         << " ---- TOP RESULTS ----\n\n";

    sort(info.begin(), info.end(), sortBySecond);

    int count = 0;
    for(int i=0; i<info.size(); i++){
        if(get<0>(info[i]) != 0 && get<2>(info[i]) >= min){
            count++;
            cout<<" "<<count<<" -> "<<"ID: "<<get<0>(info[i])<<" ("<<get<1>(info[i])<<" matches)\n";
        }
        if(count == 15)
            break;
    }
    if(count > 0)
        return true;

    if(count == 0){
        cout << " - No Relevant Cases\n";
        return false;
    }
}

bool sortBySecond(const tuple<int, int, int>& a, const tuple<int, int, int>& b)
{
    return (get<1>(a) > get<1>(b));
}



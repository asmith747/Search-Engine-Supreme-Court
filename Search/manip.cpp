#include "manip.h"
#include <algorithm>
#include <cstring>
#include "data.h"
#include <cstring>
#include "porter2_stemmer/porter2_stemmer.h"
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
#include <stdio.h>
#include <regex>

using namespace std;

Manip::Manip()
{

}

Manip::~Manip(){

}


void Manip::addStop(char* const file[]){
    st.open(file[2]);
    string word;
    while(!st.eof()){
        st >> word;
        stopWords.insert(word);
    }
    st.close();
}


void Manip::addHTML(string inp, int id, IndexInterface *& ind)
{
    if(inp.size() > 1){
    //Take out all tags
    while (inp.find("<") != string::npos){
        auto startpos = inp.find("<");
        auto endpos = inp.find(">") + 1;

        if (endpos != string::npos){
            inp.erase(startpos, endpos - startpos);
        }

    }

    //Take out punctuation
    for (int i = 0; i < inp.size(); i++){
        if(inp[i] == '\n')
            inp[i] = ' ';
        if(inp[i] == '\t')
            inp[i] = ' ';
        if (ispunct(inp[i])){
            inp[i] = ' ';
       //     inp.erase(i--, 1);
        }
        if(!isascii(inp[i])){
            inp[i] = ' ';
       //     inp.erase(i--, 1);
        }
        if(isdigit(inp[i]))
            inp.erase(i--, 1);
//        if(isalpha(inp[i]) && inp[i] != ' ')
//            inp.erase(i--, 1);
    }

    //convert to lower case
    transform(inp.begin(), inp.end(), inp.begin(), ::tolower);

    addWords(inp, id, ind);

    }
}


void Manip::addPlain(string inp, int id, IndexInterface *& ind)
{
    if(inp.size() > 1){
        for (int i = 0; i < inp.size(); i++){
            if(inp[i] == '\n')
                inp[i] = ' ';
            if(inp[i] == '\t')
                inp[i] = ' ';
            if (ispunct(inp[i])){
                inp[i] = ' ';
           //     inp.erase(i--, 1);
            }
            if(!isascii(inp[i])){
                inp[i] = ' ';
           //     inp.erase(i--, 1);
            }
            if(isdigit(inp[i]))
                inp.erase(i--, 1);
//            if(isalpha(inp[i]) && inp[i] != ' ')
//                inp.erase(i--, 1);
        }
        transform(inp.begin(), inp.end(), inp.begin(), ::tolower);

        addWords(inp, id, ind);
    }
}

void Manip::parseCase(string inp, int id, IndexInterface *& ind)
{
//    regex e("<[^<]*>|\d"); //\x00-\x7F
//    string input;
//    regex_replace(std::back_inserter(input), inp.begin(), inp.end(), e, "");

//    istringstream str{(input)};
//    string temp;
//    int count = 0;//keep track of number of wordToFind appears in document
//    while(str >> temp)
//    {
////            temp.erase(std::remove_if (temp.begin (), temp.end (),
////                                       [](unsigned char x){return ispunct(x);}), temp.end ());
////            temp.erase(std::remove_if (temp.begin (), temp.end (),
////                                       [](unsigned char x){return isdigit(x);}), temp.end ());
////            temp.erase(std::remove_if (temp.begin (), temp.end (),
////                                       [](unsigned char x){return isascii(x);}), temp.end ());
//            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
//            if(stopWords.contains(temp)){
//                temp = "";
//                continue;
//            }
//            Porter2Stemmer::stem(temp);
//            Data node(temp, id);
//            if (ind->find(node)){
//                Data node(temp, id);
//                ind->update(node).incrementMap(id);
//            } else if(temp.size() > 1) {
//                ind->insert(node);
//          }
//     }

}


void Manip::addWords(string inp, int id, IndexInterface *& ind)
{
    char str[1000000];
    strcpy(str, inp.c_str());
    char *toke = strtok(str, " ");
    while(toke != NULL){

        string tokStr(toke);
        Porter2Stemmer::stem(tokStr);

//        //check for stop words and numbers and size of 1-2
        if(!stopWords.contains(tokStr) && !tokStr[1] == '\0'){

//                //&& !tokStr[2] == '\0'){// && tokStr[tokStr.size()-1] != ){
            Data node(tokStr, id);

            //if already in index, increment # of times found
            if(ind->find(node)){
            //    cout << "Updating: " << tokStr << "\n";
                ind->update(node).incrementMap(id);

//            //if not found insert new node
            }else{
        //        cout << "Inserting: " << tokStr << "\n";
                node.addOne(id);
                ind->insert(node);
            }
        }else ;//Do nothing (word doesn't meet requirments)

        toke = strtok(NULL, " "); //iterate to next word
    }
}


void Manip::singleFile(string text, bool plain)
{
    if(text.size() > 1){
        if(!plain){
            //Take out all tags
            while (text.find("<") != string::npos){
                auto startpos = text.find("<");
                auto endpos = text.find(">") + 1;

               if (endpos != string::npos){
                    text.erase(startpos, endpos - startpos);
                }
            }
        }
        int count = 0;
        stringstream ss(text);
        do{
            count++;
            string word;
            ss >> word;
            cout << word << " ";
        } while(ss && count < 300);
    }

}

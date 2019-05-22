#include "parse.h"
#include <dirent.h>
#include <sys/stat.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <cstring>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include <sstream>
#include <chrono>
#include <algorithm>
#include "porter2_stemmer/porter2_stemmer.h"

using namespace std;
using namespace rapidjson;
using namespace chrono;


Parse::Parse(){

}

void Parse::addStop(char* const argv){
    st.open(argv);
    string word;
    while(!st.eof()){
        st >> word;
        stopWords.insert(word);
    }
    st.close();
}


void Parse::readDir(char * const argv[], bool add, vector<string>& paths, string input)
{
    man.addStop(argv);
    addStop(argv[2]);
    DIR *dir;
    struct dirent *ent;
    const char* cpath;
    string path;

    if(add){
        path = getenv("HOME");
        path += "/Desktop/" + input;
        cpath = path.c_str();
        cout << cpath << endl;
    } else if(!add)
        cpath = argv[1];

    if((dir = opendir(cpath)) != NULL){
        while((ent = readdir(dir)) != NULL){
            string fname = cpath;
            if(ent->d_name[0] != '.'){
                fname.append("/");
                fname.append(ent->d_name);

                paths.push_back(fname);
            }
        }
        closedir(dir);
    }
    else{
        cout << "\nDirectory failed to open, try again\n" << endl;
        return;
    }
}


int Parse::getDirSize(char * const argv[])
{
    DIR *dir;
    struct dirent *ent;

    int count = 0;
    if((dir = opendir(argv[1])) != NULL){
        while((ent = readdir(dir)) != NULL){
            string fname = argv[1];
            count++;
        }
        closedir(dir);
    }
    return count;
}


void Parse::addWords(IndexInterface *& ind, bool add, vector<string> paths)
{
    cout << " - Parsing files..."<< endl;
    auto start = high_resolution_clock::now();

    int d = 5000;
    int iter = 0;
    if(add)
        iter = paths.size();
    if(!add){
        cout << "DEMO: Not creating new index\n";
        return;
        iter = 0;
    }


int c1=0, c2=0, c3=0, c4=0;
    for(int i=0; i<paths.size(); i++){
        bool cont = true;

    //    cout << paths[i] << endl;
        string plain = "", html = "", html1 = "", html3 = "";
        fs.open(paths[i]);

    //    string toke = "";

        //USING RAPIDJSON

        stringstream strstr;
        strstr << fs.rdbuf();
        string jstr = strstr.str();
        fs.close();
        rapidjson::Document doc;
        const char* jcstr = jstr.c_str();
        doc.Parse(jcstr);



        int id = doc["id"].GetInt();
    //    string text = "";
        if(!doc["plain_text"].IsNull() && strcmp(doc["plain_text"].GetString(), "") != 0){
            plain = doc["plain_text"].GetString();
            man.addPlain(plain, id, ind);
            c1++;
            cont = false;
        }

        if(!doc["html"].IsNull() && strcmp(doc["html"].GetString(), "") != 0 && cont){
            html = doc["html"].GetString();
            man.addHTML(html, id, ind);
            c2++;
            cont = false;
        }

        if(!doc["html_lawbox"].IsNull() && strcmp(doc["html_lawbox"].GetString(), "") != 0 && cont){
            html1 = doc["html_lawbox"].GetString();
            man.addHTML(html1, id, ind);
            c3++;
            cont = false;
        }

        if(!doc["html_with_citations"].IsNull() && strcmp(doc["html_with_citations"].GetString(), "") != 0 && cont){
            html3 = doc["html_with_citations"].GetString();
            man.addHTML(html3, id, ind);
            c4++;
        }

        cout << i << "\n";
        fs.close();
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "TIME: " << float(duration.count())/float(1000000) << " seconds\n";
}


//        char str[500000];
//        strcpy(str, text.c_str());
//        char *toke = strtok(str, " ");
//        while(toke != NULL){

//          //  string tokStr(toke);
//            int c = 0;
//            int cx = 0;
//            while(toke[c]){
//                if(ispunct(toke[c])) cx++;
//                c++;
//                if(cx == 2){break;}
//            }

//            if((toke.size() >= 20) || (toke.size() <= 3) || (cx >= 2) || !stopWords.contains(tokStr)){
//                continue;
//            }
//            cout << toke << endl;

//            transform(toke.begin(), toke.end(), toke.begin(), ::tolower);
//            toke.erase(remove_if(toke.begin(), toke.end(), ::ispunct), toke.end());
//            Porter2Stemmer::stem(toke);
//            //cout << word << endl;
//            Data node(toke, id);
//            if (ind->find(node)){
//                Data node(toke, id);
//                ind->update(node).incrementMap(id);
//            } else if(toke.size() > 1) {
//                ind->insert(node);
//          }

//            toke = strtok(NULL, " "); //iterate to next word
//        }




//    for(int i=0; i<1000;i++){//i<fnames.size(); i++){
//     //   bool cont = true;

//    //    string plain = "", html = "", html1 = "", html3 = "";
//        fs.open(fnames[i]);

//        string toke = "";

//        while(fs >> toke){

//          //  string tokStr(toke);
//            int c = 0;
//            int cx = 0;
//            while(toke[c]){
//                if(ispunct(toke[c])) cx++;
//                c++;
//                if(cx == 2){break;}
//            }

//            if((toke.size() >= 20) || (toke.size() <= 3) || (cx >= 2) || !stopWords.contains(toke)){
//                continue;
//            }

//            transform(toke.begin(), toke.end(), toke.begin(), ::tolower);
//            toke.erase(remove_if(toke.begin(), toke.end(), ::ispunct), toke.end());
//            Porter2Stemmer::stem(toke);
//            Data node(toke, i);
//            if (ind->find(node)){
//                Data node(toke, i);
//                ind->update(node).incrementMap(i);
//            } else if(toke.size() > 1) {
//                ind->insert(node);
//          }
//        }




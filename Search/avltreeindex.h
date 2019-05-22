#ifndef AVLTREEINDEX_H
#define AVLTREEINDEX_H
#include "avltree.h"
#include "data.h"
#include <ostream>
#include <map>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>

class AVLTreeIndex : public IndexInterface
{
public:
    AVLTreeIndex(){

    }

    ~AVLTreeIndex(){
        avl.~AVLTree();
    }

    void insert(Data& dat){
            avl.insert(dat);
    }

    void print(){

    }

    bool find(Data& dat){
        if(avl.contains(dat)){
            return true;
        }
        else{
            return false;
        }
    }

    void printToFile(ofstream& out){
        avl.printOut(out);
        out << "-1";
        return;
    }

    int getSize(){
        return avl.getSize();
    }

    void getData(string word){
        Data temp(word, 0);
        avl.getData(temp);
    }
    Data getTop(string word){
        Data temp(word, 0);
        return avl.getTop(temp);
    }

    Data& update(Data dat){
        return avl.update(dat);
    }

    void addFiles(string path){

    }


    int printCommon(bool com){
        if(!com){
            common.clear();
            common = avl.printCommon();
        }

        if(com){
            vector<tuple<int, string>> top;

            int count = 0;
            for(int i=0; i< common.size(); i++){
                top.push_back(make_tuple(0, common[i].getWord()));

                for(auto const& x : common[i].getInfo())
                    get<0>(top[count]) += x.second;
                count++;
            }
            sort(top.begin(), top.end());

            int counter = 1;
            cout << left;

            for(int i=top.size()-1; i>top.size()-51; i--){
                cout << " "<< left << setw(2) << counter <<": "<<setw(10)
                     <<get<1>(top[i]) << " (" << get<0>(top[i]) << ")";

                if((counter)%3 == 0)
                    cout << endl;
                counter++;
            }
            return 0;
        } else {
            int sum = 0;
            for(int i=0; i< common.size(); i++){
                for(auto const& x : common[i].getInfo())
                    sum += x.second;
            }
            return sum;
        }
    }

    bool readFromFile(char * const argv[]){



        ifstream index(argv[3]);

        bool empty = false;

        while(!index.eof()){
            map<int, int> caseValue;
            char str[500000];
            index.getline(str, '500000', '\n');
            char *toke = strtok(str, " ");

            if(toke == NULL){
                empty = true;
                break;
            }

            string word(toke);
            bool cont = false;
            bool first = true;
            int contInt = 0;
            int one = 0;
            int two = 0;
            bool add = false;

            while(toke != NULL){
                if(cont){
                    if(first){
                        contInt = 1;
                        one = atoi(toke);
                        add = false;
                    }
                    if(!first){
                        contInt = 2;
                        two = atoi(toke);
                        add = true;
                    }
                    if(contInt == 1)
                        first = false;
                    if(contInt == 2)
                        first = true;
                }
                if(add)
                    caseValue[one] = two;
                cont = true;
                toke = strtok(NULL, " ");
            }
            Data intoTree(caseValue, word);
            avl.insert(intoTree);
        }

        if(empty){
            cout << " -- INDEX HAS NOT YET BEEN CREATED\n\n"
                 << " -- Go into maintenance mode to create\n\n";
            return true;
        }
        else
            return false;

    }


private:
    AVLTree<Data> avl;
    vector<Data> common;
};


#endif // AVLTREEINDEX_H

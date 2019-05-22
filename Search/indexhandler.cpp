#include "indexhandler.h"
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>

IndexHandler::IndexHandler()
{

}

void IndexHandler::parseFiles(char * const argv[], int sel)
{
    if(sel == 0){
        par.readDir(argv, false, fnames, " ");
        if(dataSelect == '1')
            par.addWords(indexAVL, false, fnames);
        if(dataSelect == '2')
            par.addWords(indHash, false, fnames);
    }

    out.open("index.txt", ios::out);
    if(!out.is_open())
        cout << "Index file could not be opened" << endl;

    if(sel == 1)
        out.close();
}

void IndexHandler::print()
{
    if(dataSelect == '1')
        indexAVL->print();
    if(dataSelect == '2')
        indHash->print();
}

void IndexHandler::output()
{
    if(dataSelect == '1')
        indexAVL->printToFile(out);
    if(dataSelect == '2')
        indHash->printToFile(out);
    out.close();
}

int IndexHandler::getSize()
{
     return max(indexAVL->getSize(), indHash->getSize());
}

void IndexHandler::getData(string word)
{
    if(dataSelect == '1')
        indexAVL->getData(word);
    if(dataSelect == '2')
        indHash->getData(word);
}

int IndexHandler::printCommon(bool com)
{
    if(dataSelect == '1')
        return indexAVL->printCommon(com);
    if(dataSelect == '2')
        return indHash->printCommon(com);
}

bool IndexHandler::readFromFile(char * const argv[])
{
    if(dataSelect == '1')
        return indexAVL->readFromFile(argv);
    if(dataSelect == '2')
        return indHash->readFromFile(argv);
}


int IndexHandler::getDirSize(char * const argv[])
{
    return par.getDirSize(argv);
}

void IndexHandler::addFiles(char * const argv[], string input, int currentState)
{
    if(dataSelect == '0'){
        cout << "The Index has not been created yet\n";
        return;
    }


    par.readDir(argv, true, anames, input);

    out.open("index.txt", ios::out);

    if(dataSelect == '1'){
        par.addWords(indexAVL, true, anames);
        indexAVL->printToFile(out);
    }

    if(dataSelect == '2'){
        cout << "ADDING\n";
        par.addWords(indHash, true, anames);
        indHash->printToFile(out);
    }

     out.close();
}


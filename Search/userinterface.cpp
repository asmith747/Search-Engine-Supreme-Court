#include "userinterface.h"
#include <iostream>
#include <fstream>
#include <chrono>


using namespace chrono;

UserInterface::UserInterface()
{

}


void UserInterface::menu(char * const argv[], bool end)
{
    directory = argv[1];

    cout << " -----------------------------------------\n"
         << " -- Welcome to the SCOTUS Search Engine --\n"
         << " -----------------------------------------\n"
         << "Choose a mode: \n"
         << " - Press 1 for maintenence mode\n"
         << " - Press 2 for interactive mode\n"
         << " - Press E to exit\n"
         << "Enter Choice: ";
    char select;
    cin >> select;
    cout << endl;

    if(select == '1'){
        maintenance(argv);
    } else if(select == '2'){
       interactive(argv);
    } else if(select == 'E' || select == 'e'){

    } else {
        cout << "Wrong input, try again\n\n";
        menu(argv, false);
    }

    if(end){
        cout << "\n\n\n ----------------------------------------------\n"
            << " -- THANK FOR USING THE SCOTUS SEARCH ENGINE --\n"
            << " ----------------------------------------------\n";
    }
}


void UserInterface::maintenance(char * const argv[])
{
    char select;
    cout << " ---------------------------\n"
         << " ----  MAINTENANCE MODE ---- \n"
         << "Choose option: \n"
         << " - Press 1 to create new index\n"
         << " - Press 2 to add more files to current index\n"
         << " - Press 3 to clear index completely\n"
         << " - Press 4 to go back to menu\n"
         << " - Press E to exit\n"
         << "Enter Choice: ";
    cin >> select;
    cout << endl;


    //OPTION 1 CREATE NEW INDEX
    if(select == '1'){
        cout << " -----------------------------\n"
             << " ----  Creating New Index ---- \n"
             << "Choose option: \n"
             << " - Press 1 to create index using AVL Tree\n"
             << " - Press 2 to create index using Hash Table\n"
             << " - Press 3 to go back\n"
             << " - Press E to exit\n"
             << "Enter Choice: ";
        cin >> select;
        cout << endl;

        //2 CREATE INDEX WITH AVL or HASH
        if(select == '1'||select == '2'){
            ind.dataSelect = select;
            ind.parseFiles(argv, 0);
            ind.output();
            cout << "\nIndex created\n\n";
            maintenance(argv);
            return;
        } else if(select == '3'){
            maintenance(argv);
            return;
        }if(select == 'E' || select == 'e'){
            return;
        } else {
            cout << "Wrong input, try again\n\n";
            maintenance(argv);
            return;
        }



    } else if(select == '2'){
        char choice[500];
        cout << " --------------------\n"
             << " ----  ADD FILES ---- \n"
             << "Choose option: \n"
             << " - Type in the directory path\n OR \n"
             << " - Press 1 to cancel\n"
             << " - Press 2 to go to menu\n"
             << " - Press E to exit\n"
             << "Path-> "<< getenv("HOME") << "/Desktop/";
        cin >> choice;
        cout << endl;



        if(choice[0] == 'E' || choice[0] == 'e'){
            return;
        } else if (strlen(choice) > 1){
            ind.addFiles(argv, choice, 10);
            menu(argv, false);
            return;
        } else if (choice[0] == '1'){
            maintenance(argv);
            return;
        } else if (choice[0] == '2'){
            menu(argv, false);
            return;
        } else {
            cout << "Wrong input, try again\n\n";
            maintenance(argv);
            return;
        }


    } else if(select == '3'){
        ind.parseFiles(argv, 1);
        cout << "Index cleared\n\n";
        maintenance(argv);
        return;
    } else if(select == '4'){
        menu(argv, false);
        return;
    } else if(select == 'E' || select == 'e'){
        return;
    } else {
        cout << "Wrong input, try again\n\n";
        maintenance(argv);
        return;
    }
}


void UserInterface::interactive(char * const argv[])
{
    char select;
    cout << " ---------------------------\n"
         << " ---- INTERACTIVE MODE ----- \n"
         << "Choose option: \n"
         << " - Press 1 to load index into AVL Tree\n"
         << " - Press 2 to load index into Hash Table\n"
         << " - Press 3 to go to back to menu\n"
         << " - Press E to exit\n"
         << "Enter Choice: ";
    cin >> select;
    cout << endl;

    if(select == 'E' || select == 'e'){
        return;
    } else if(select == '1' || select == '2'){
        ind.dataSelect = select;
        bool clear = true;
        clear = ind.readFromFile(argv);
        if(clear){
            menu(argv, false);
            return;
        }

        char sel;
        cout << " ---------------------------\n"
             << " ---- INTERACTIVE MODE ----- \n"
             << "Choose option: \n"
             << " - Press 1 to SEARCH\n"
             << " - Press 2 to show statistics of Search Engine\n"
             << " - Press 3 to go back\n"
             << " - Press E to exit\n"
             << "Enter Choice: ";
        cin >> sel;
        cout << endl;

        //1 SEARCH
        if(sel == '1'){
            binSearch(argv, select);
            return;
        } else if(sel == '2'){
            int dirSize = ind.getDirSize(argv);
            int numOfWords;
            char choice;
            cout << " --------------------\n"
                 << " ---- STATISTICS ---- \n"
                 << " - Total Documents: "<< dirSize
                 << "\n - Total Words: " << ind.getSize()
                 << "\n - Average # Opinions per Case: ";

            numOfWords = ind.printCommon(false);
            cout << float(numOfWords)/float(dirSize)
                 << "\n - 50 Most Common Words (lines of 3)\n";
            numOfWords = ind.printCommon(true);
            cout << "\nChoose option: \n"
                 << " - Press 1 to search\n"
                 << " - Press 2 to return to menu\n"
                 << " - Press E to exit\n"
                 << "Enter Choice: ";
            cin >> choice;
            cout << "\n";

            if(choice == '1'){
                binSearch(argv, select);
                return;
            } else if(choice == '2'){
                menu(argv, false);
                return;
            } else if(choice == 'e' || choice == 'E'){
                return;
            } else {
                cout << "Wrong input, try again\n\n";
                interactive(argv);
                return;
            }

        } else if(sel == '3'){
            interactive(argv);
            return;
        } else if(sel == 'E' || select == 'e'){
            return;
        } else {
            cout << "Wrong input, try again\n\n";
            interactive(argv);
            return;
        }
    } else if(select == '3'){
        menu(argv, false);
        return;
    } else {
        cout << "Wrong input, try again\n\n";
        interactive(argv);
        return;
    }
}


void UserInterface::binSearch(char * const argv[], int select)
{

    bool valid = true;
    cout << " -----------------------\n"
         << " ---- BINARY SEARCH ---- \n"
         << "Enter The Words You Want to Search (Greater than 3 characers)\n"
         << "-> ";
    cin.ignore();
    string input;
    getline(cin, input);
    if(input.size()<=1 || input == "and" || input == "not" || input == "AND" || input == "NOT"){
        cout << "\nInvalid input, try again\n\n";
        binSearch(argv, select);
        return;
    }

    valid = query.userInput(input);

    bool NOT=false, AND=false, OR=false, ONE=false;
    if(query.getONE().size() > 0)
        ONE = true;
    if(query.getNOT().size() > 0)
        NOT = true;
    if(query.getAND().size() > 0)
        AND = true;
    if(query.getOR().size() > 0)
        OR = true;

    bool results = false;
    if(select == '1'){
        if(ONE && valid)
            results = search.searchONE(ind.indexAVL, query.getONE());
        if(AND)
            results = search.searchAND(ind.indexAVL, query.getAND(), query.getNOT(), NOT);
        if(OR)
            results = search.searchOR(ind.indexAVL, query.getOR(), query.getNOT(), NOT);
    }
    if(select == '2'){
        if(ONE && valid)
           results =  search.searchONE(ind.indHash, query.getONE());
        if(AND)
            results = search.searchAND(ind.indHash, query.getAND(), query.getNOT(), NOT);
        if(OR)
            results = search.searchOR(ind.indHash, query.getOR(), query.getNOT(), NOT);
    }

    if(results && valid)
        getFile(argv, select);

    else{
        char sel;
        cout << "\n --------------------------\n"
             << " ---- NO MATCHES FOUND ----\n"
             << "Choose Option:\n"
             << " - Press 1 to search again\n"
             << " - Press 2 to go to menu\n"
             << " - Press E to exit\n"
             << "Enter Choice: ";
        cin >> sel;
        cout << endl;

        if(sel == '1'){
            binSearch(argv, select);
            return;
        } else if(sel == '2'){
            menu(argv, false);
            return;
        } else if(sel == 'e' || sel =='E')
            return;
        else {
            cout << "Invalid input, try again\n\n";
            binSearch(argv, select);
            return;
        }
    }
    return;
}


void UserInterface::getFile(char * const argv[], int sel)
{
    char choice[15];
    cout << "\n ------------------------\n"
         << " ---- FILE SELECTION ----\n"
         << "Choose Option:\n"
         << " - To open a file, type the file ID\n OR \n"
         << " - Press 1 to search again\n"
         << " - Press 2 to go back to menu\n"
         << " - Press E to exit\n"
         << "Enter Choice/ID: ";
    cin >> choice;

    if (choice[0] == 'e' || choice[0] == 'E'){
        return;
    } else if(strlen(choice) > 1){
        int num = atoi(choice);
        string path = directory;
        path.append("/" + to_string(num) + ".json");
        displayFile(argv, path, sel, num);
        return;
    } else if(choice[0] == '1'){
        cout << endl;
        binSearch(argv, sel);
        return;
    } else if(choice[0] == '2'){
        cout << "\n";
        menu(argv, false);
        return;
    } else{
        cout << "Invalid input, try again\n\n";
        getFile(argv, sel);
        return;
    }
}


void UserInterface::displayFile(char * const argv[], string path, int sel, int ID)
{
    ifstream fs;
    fs.open(path);
    if(!fs.is_open()){
        cout << "\nIncorect Case ID, Try Again\n";
        getFile(argv, sel);
        return;
    }

    cout << "\n -- Displaying Case #" << ID << " --\n\n  --> ";
    stringstream str;
    str << fs.rdbuf();
    string jstr = str.str();
    fs.close();
    rapidjson::Document doc;
    const char* jcstr = jstr.c_str();
    doc.Parse(jcstr);

    string text = "";

    bool plain = false;
    bool cont = true;
    if(!doc["plain_text"].IsNull() && strcmp(doc["plain_text"].GetString(), "") != 0){
        text = doc["plain_text"].GetString();
        plain = true;
        cont = false;
    }

    if(!doc["html"].IsNull() && strcmp(doc["html"].GetString(), "") != 0 && cont){
        text = doc["html"].GetString();
        cont = false;
    }

    if(!doc["html_lawbox"].IsNull() && strcmp(doc["html_lawbox"].GetString(), "") != 0 && cont){
        text = doc["html_lawbox"].GetString();
        cont = false;
    }

    if(!doc["html_with_citations"].IsNull() && strcmp(doc["html_with_citations"].GetString(), "") != 0 && cont)
        text = doc["html_with_citations"].GetString();

        man.singleFile(text, plain);
        fs.close();
        searchAgain(argv, sel);
        return;
}


void UserInterface::searchAgain(char * const argv[], int sel)
{
    char choice;
    cout << "\n\n ------------------------\n"
         << " ---- WHERE TO? ----\n"
         << "Choose Option:\n"
         << " - Press 1 to search again\n"
         << " - Press 2 to go to interactive menu\n"
         << " - Press 3 to open another file\n"
         << " - Press E to exit\n"
         << "Enter Choice: ";
    cin >> choice;

    if(choice == '1'){ //CHOICE 1
        cout << endl;
        binSearch(argv, sel);
        return;
    } else if(choice == '2'){ //CHOICE 2
        cout << endl;
        interactive(argv);
        return;
    } else if(choice == '3'){ //CHOICE 3
        getFile(argv, sel);
        return;
    } else if(choice == 'e' || choice == 'E') //CHOICE 4
        return;
    else {
        cout << "\nInvalid input, try again";
        searchAgain(argv, sel);
        return;
    }
}


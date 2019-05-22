/*
 * Austin Smith, Richmond Aisabor
 * Search Engine - Programming Assignment 5
 */

#include <iostream>

#include <dirent.h>
#include <sys/stat.h>
#include "userinterface.h"
#include "data.h"
#include "hashtableindex.h"
#include <vector>
#include <map>
#include <fstream>

using namespace std;

int main(int argc, char* const argv[])
{
    UserInterface user;
    user.menu(argv, true);

    cout << "\n\n-- END OF PROGRAM --" << endl;
    return 0;
}

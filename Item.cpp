#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "functions.h"
#include "Item.h"

using namespace std;

//prints menu options
void item::display_()
{
    cout.width(y + (name.size()));
    cout << name << "  \n";
}

//highlights the selected menu option by making it bold and making the background white and letters black
void item::display_selected()
{
    cout.width(y+10);
    cout<<"\033[30;1;47m" << name <<"\033[0m\n";
}
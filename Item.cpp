#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "functions.h"
#include "Item.h"

using namespace std;

//CONSTRUCTOR
item::item()
{
    name = " ";
    description = " ";
    y = 0;
    returnval = 0;
}
item::item(string s1, int a, string s2)
{
    name = s1;
    description = s2;
    returnval = a;
}
item::~item()
{
    
}

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

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "functions.h"
#include "Item.h"

using namespace std;

void item::display_()
{
    cout.width(y + (name.size()));
    cout << name << "  \n";
}

void item::disp_selected()
{
    cout.width(y+10);
    cout<<"\033[30;1;47m" << name <<"\033[0m\n";
}
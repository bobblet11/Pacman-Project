#include "Item.h"

Item :: Item(std::string s1, int a, std::string s2)
{
    name = s1;
    description = s2;
    ret = a;
}

Item :: Item()
{
    name = " ";
    description = " ";
    y = 0;
    ret = 0;
}

void Item::display()
{
    //cout.width(y + (name.size()));
    //cout << name << "  \n";
}

void Item::disp_selected()
{
    //cout.width(y+10);
    //cout<<"\033[30;1;47m" << name <<"\033[0m\n";

}
//HEADER GUARDS
#pragma once
#ifndef _ITEM_
#define _ITEM_
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "functions.h"

using namespace std;

class item
{
public:
    string name, description;
    int returnval;
    int y;
    item()
    {
        name = " ";
        description = " ";
        y = 0;
        returnval = 0;
    }
    item(string s1, int a, string s2)
    {
        name = s1;
        description = s2;
        returnval = a;
    }
    void display_();
    void display_selected();
};

#endif
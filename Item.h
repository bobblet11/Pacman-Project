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

//item class for menu options and description
class item
{
public:
    //constructors
    item();
    item(string s1, int a, string s2);
    //deconstructors
    ~item();
    string name, description;
    int returnval;
    int y;
    void display_();
    void display_selected();
};

#endif
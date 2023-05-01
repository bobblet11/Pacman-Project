//HEADER GUARDS
#pragma once
#ifndef _MENU_
#define _MENU_
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "functions.h"
#include "Item.h"

using namespace std;

class menu
{
    item head;
    vector<item> elements;
    int num;
public:
    menu()
    {
        num=0;
    };
    void add(string,int,string);
    void menu_head(string);
    int display();
};

#endif
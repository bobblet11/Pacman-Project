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
    string name, desc;
    int ret;
    int y;
    item()
    {
        name = " ";
        desc = " ";
        y = 0;
        ret = 0;
    }
    item(string s1, int a, string s2)
    {
        name = s1;
        desc = s2;
        ret = a;
    }
    void display_();
    void disp_selected();
};

#endif
#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "functions.h"

class Item
{
    public:
        //CONSTRUCTORS
        Item();
        Item(std::string s1, int a, std::string s2);
      
        //MEMBER VARIABLES
        std::string name, description;
        int ret;
        int y;

        //EXTERNAL MEMBER FUNCTIONS
        void display();
        void disp_selected();
};
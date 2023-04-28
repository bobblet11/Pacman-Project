#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "functions.h"
#include "Item.h"


class Menu
{
    public:
        Menu();
        void add(std::string,int,std::string);
        void menu_head(std::string);
        int display();
    private:
        Item head;
        std::vector<Item> entries;
        int num = 0;
};

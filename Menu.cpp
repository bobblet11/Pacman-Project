//INCLUDES
#include <iostream>
#include "functions.h"
#include "middle.h"

#include "Menu.h"



Menu::Menu()
{

}

void Menu::add(std::string s, int r = 0, std::string d = " ")
{
    num++;
    if(r == 0)
        r = num;
    entries.push_back(Item(s, r, d));
}


void Menu::menu_head(std::string s)
{
    head.name = s;
    return;
}


int Menu::display()
{
    system("clear");
    int selected = 0, opt=66, last_x = getmax_x(), last_y = getmax_y();
    while(true)
    {
        int max_y = getmax_y(), i;
        head.y = (max_y - head.name.size())/2;
        for(Item &a : entries)
        {
            a.y = (max_y - a.name.size())/2;
        }
        int max_x = getmax_x();
        if (!(max_x == last_x && max_y == last_y))
        {
            system("clear");
            last_x = max_x;
            last_y = max_y;
        }
        int x = (max_x - num)/2 - 2;
        gotoxy(0, 0);
        for(i = 2; i < x; i++)
            cout<<endl;
        head.display();
        cout<<"\n\n";
        for(i=0;i<(int)entries.size();i++)
        {
            if ( i == selected)
                entries[i].disp_selected();
            else
                entries[i].display();
        }
        cout << "\n\n\n\n\n\n\n";
        cout << ">>> " << entries[selected].description;
        int previous = (opt==66)?(selected-1):(selected+1);
        if (previous < 0)
            previous = num-1;
        if(previous == num)
            previous = 0;
        int temp = (entries[previous].description.length() - entries[selected].description.length());
        for(int i=0;i<temp;i++)
            cout << " ";
        cout<<'\n';
        opt = getch();
        if (opt == 10)
            return entries[selected].ret;
        switch(opt)
        {
            case 66:
                selected++;
                break;
            case 65:
                selected--;
                break;
        }
        if(selected == num)
            selected = 0;
        if(selected == -1)
            selected = num -1;
    }
}


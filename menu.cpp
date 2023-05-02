#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include "functions.h"
#include "menu.h"
#include "Item.h"

using namespace std;

//adds menu options to the vector
void menu::add(string s, int r = 0, string d = " ")
{
    num++;
    if(r == 0)
    {
        r = num;
    }
    elements.push_back(item(s, r, d));
}

//Sets the name of the pacman head in main menu to the item class
void menu::menu_head(string s)
{
    head.name = s;
    return;
}

int menu::display()
{
    //Clears the console screen
    system("clear");

    //Initialize variables
    int selected = 0, opt=66, last_x = getmax_x(), last_y = getmax_y();
    
    //Main menu display loop
    while(true)
    {
        int MAX_Y = getmax_y(), i;
        head.y = (MAX_Y - head.name.size())/2;

        //loop through each menu elements in menu class vector
        for(item &a : elements)
        {
            a.y = (MAX_Y - a.name.size())/2;
        }

        int MAX_X = getmax_x();

        if (!(MAX_X == last_x && MAX_Y == last_y))
        {
            system("clear");
            last_x = MAX_X;
            last_y = MAX_Y;
        }
        int x = (MAX_X - num)/2 - 2;

        //Moves the cursor to the top-left of the console screen
        gotoxy(0, 0);

        //loop to print newlines before the menu elements
        for(i = 2; i < x; i++)
        {
            cout << endl;
        }
        //Displays the pacman head as menu header
        head.display_();

        cout<<"\n\n";

        for(i = 0; i<(int)elements.size(); i++)
        {
            //Checks if the current menu item is selected
            if (i == selected)
            {
                //Displays the selected menu item highlighted
                elements[i].display_selected();
            }
            else
            {
                //Displays the unselected menu item normally
                elements[i].display_();
            }
        }

        cout << "\n\n\n\n\n\n\n";

        //Prints the selected menu item's description
        cout << ">>> " << elements[selected].description;

        int previous = (opt==66)?(selected-1):(selected+1);

        if (previous < 0)
        {
            previous = num-1;
        }
        if (previous == num)
        {
            previous = 0;
        }

        int temp = (elements[previous].description.length() - elements[selected].description.length());
        
        for (int i=0; i < temp; i++)
        {
            cout << " ";
        }

        cout << '\n';

        //Gets the user's keyboard input
        opt = GETCH();

        if (opt == 10)
        {
            return elements[selected].returnval;
        }
        //Checks the user's keyboard input
        switch(opt)
        {
            //Moves the selection down
            case 66:
                selected++;
                break;
            //Moves the selection up
            case 65:
                selected--;
                break;
        }

        if (selected == num)
        {
            selected = 0;
        }

        if (selected == -1)
        {
            selected = num -1;
        }
    }
}
#include "Screen.h"
#include "functions.h"

//CONSTRUCTOR
Screen::Screen()
{
    
}

//CONSTRUCTOR
//width and height are the dimensions of the rendered frame
//map is the playable map object
Screen :: Screen (int width, int height, PlayableMap & map)
{
    this->width = width+2; //+2 for the side walls
    this->height = height+2; //+2 for the top and bottom walls
    this->map_ptr = map; //set pointer to point at map object

   //if the size set is too large, exit the initialisation and close program.
   if (width < 0 || width > 200 || height < 0 || height > 200)
   {
        printw("[ERROR] Invalid Screen parameters...");
        refresh();
        exit(-1);
   }
    
    //dynamically allocate 2D array using dimensions
   frame = new std::string*[getHeight()];
   for (int i = 0; i<getHeight(); i++)
   {
        frame[i] = new std::string[getWidth()];
   }
    //reset the frame for printing
    resetFrame();
}

Screen :: ~Screen()
{
    for (int i = 0; i<getHeight(); i++)
   {
        delete[] frame[i];
   }
   delete[] frame;
}

//getters
int Screen::getWidth()
{
    return width; //returns the width dimension of the rendered frame
}
int Screen::getHeight()
{
    return height; //returns the height dimension of the rendered frame
}

//frame functions
//resets the strings stored in the frame to their default values
void Screen::resetFrame()
{
    for(int i=0;i<getHeight();i++)
    {
        for(int j=0;j<getWidth();j++)
        {
            //checks if the coordinates are at the edge of the frame
            //so that edge and corner characters can be used
            if ((i==0 || i == getHeight()-1 ) && (j > 0 && j < getWidth()-1))
            {
                //horiz
                frame[i][j] = BORDER_HORIZ; 
            }
            else if ((j==0 || j == getWidth()-1) && (i > 0 && i < getHeight()-1))
            {
                //vertic
                frame[i][j] = BORDER_VERT;
            }
            else if ((i==0 && j==0) || (i==0 && j == getWidth()-1) || ( i == getHeight()-1 && j==0) || (i==getHeight()-1 && j==getWidth()-1))
            {
                std::string BORDER_CORNER =  (i==0 && j==0) ? BORDER_CORNER_TL : (i==0 && j == getWidth()-1) ? BORDER_CORNER_TR : ( i == getHeight()-1 && j==0)  ?  BORDER_CORNER_BL : BORDER_CORNER_BR;
                frame[i][j] = BORDER_CORNER;
            }
            else if (i>1 && i < getHeight()) //if the i,j is in the range of the playbable map render area, render the map
            {
                frame[i][j] = map_ptr.getCharAtPos(j-1,i-2);
            }
            else //if the x,y is random coordinates outside of the playable map, and within the bounds of the borders, set to empty value
            {
                frame[i][j] = "  "; //2 spaces because of font issue, 
            }

        }
    }
}

//handle is the vector containing pointers to all active gameobjects
//prints the frame and all active gameobjects
void Screen::printCurrentFrame(std::vector<GameObject*> &handle)
{
    //draw map
    for(int i=0;i<getHeight();i++)
    {
        move(i+(getmax_x()/2-16),(getmax_y()/2-30));
        for(int j=0;j<getWidth();j++)
        {
            if (i > 0 && i < getHeight()-1 && j >0 && j < getWidth()-1) //if the x,y is not a border or corner
            {
                attron(COLOR_PAIR(2)); //set colour to blue
                printw("%s", frame[i][j].c_str()); //print the frame string at the x,y
                attroff(COLOR_PAIR(2)); //unset colour to blue
            }
            else //if its a border or corner, no colour change
            {
                printw("%s", frame[i][j].c_str());
            }
            
        } 
    }   
    
    //draw the all gameojects
    for (int i=0; i < handle.size(); i++)
    {
        //accesses the gameobject functions through the pointer
        handle.at(i)->printCharacterAtPosition();
    }

    //reset cursor position
    move(0,0);
}

//resets the frame to default, prints frame and gameobject, refreshes to display
//handle is the vector containing pointers to all active gameobjects
void Screen::render(std::vector<GameObject*> &handle)
{   
    resetFrame();
    printCurrentFrame(handle);
    refresh();
}


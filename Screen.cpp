#include "Screen.h"
#include "functions.h"

Screen::Screen()
{
    
}

Screen :: Screen (int width, int height, PlayableMap & map)
{
    this->width = width+2; //2 for the side walls, 20 for the gap
    this->height = height+2;
    this->map_ptr = map;

    //parameter width and height is internal area, the class member width, height include borders
    //initialisation

   if (width < 0 || width > 200 || height < 0 || height > 200)
   {
        printw("[ERROR] Invalid Screen parameters...");
        refresh();
        exit(-1);
   }
    
   frame = new std::string*[getHeight()];
   for (int i = 0; i<getHeight(); i++)
   {
        frame[i] = new std::string[getWidth()];
   }

    resetFrame();
    refresh();

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
    return width;
}
int Screen::getHeight()
{
    return height;
}

//frame functions
void Screen::resetFrame()
{
    for(int i=0;i<getHeight();i++)
    {
        for(int j=0;j<getWidth();j++)
        {
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
            else if (i>1 && i < getHeight())
            {
                frame[i][j] = map_ptr.getCharAtPos(j-1,i-2);
            }
            else
            {
                frame[i][j] = "  ";
            }

        }
    }
}

void Screen::printCurrentFrame(std::vector<GameObject*> &handle)
{
    //draw map
    for(int i=0;i<getHeight();i++)
    {
        move(i+(getmax_x()/2-16),(getmax_y()/2-30));
        for(int j=0;j<getWidth();j++)
        {
            if (i > 0 && i < getHeight()-1 && j >0 && j < getWidth()-1)
            {
                attron(COLOR_PAIR(2));
                printw("%s", frame[i][j].c_str());
                attroff(COLOR_PAIR(2));
            }
            else
            {
                printw("%s", frame[i][j].c_str());
            }
            
        } 
    }   
    
    for (int i=0; i < handle.size(); i++)
    {
        handle.at(i)->printCharacterAtPosition();
    }


    move(0,0);
}

void Screen::render(std::vector<GameObject*> &handle)
{   
    resetFrame();
    printCurrentFrame(handle);
}


#include "Screen.h"

Screen :: Screen (int width, int height, PlayableMap & map)
{
    this->width = width+2;
    this->height = height+2;
    this->map_ptr = map;
    //parameter width and height is internal area, the class member width, height include borders
    //initialisation

   if (width < 0 || width > 100 || height < 0 || height > 100)
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
    printCurrentFrame();
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
            if ((i==0 || i == getHeight()-1) && (j > 0 && j < getWidth()-1))
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
            else
            {
                //empty
                //replace this with a map_layout_get char at position
                frame[i][j] = map_ptr.getCharAtPos(j-1,i-1);
            }

        }
    }
}

void Screen::printCurrentFrame()
{
    for(int i=0;i<getHeight();i++)
    {
        move(i,0);
        for(int j=0;j<getWidth();j++)
        {
            printw("%s", frame[i][j].c_str());
        } 
        
    }   

    for (int a=0; a<object_list.size(); a++)
    {
        object_list[a]->printCharacterAtPosition();
    }

    refresh();
    move(0,0);
}

void Screen::addObject(GameObject* object)
{
    object_list.push_back(object);
}

void Screen::updateObjectsIntoFrame()
{
    resetFrame();
    int x_pos,y_pos;
    for (int a=0; a<object_list.size(); a++)
    {
        int obj_width = object_list[a]->getWidth();
        std::string sprite = object_list[a]->getCurrentSprite();
        frame[object_list[a]->getY()][object_list[a]->getX()] = sprite;
    }
}

void Screen::render()
{   
    resetFrame();
    printCurrentFrame();
}


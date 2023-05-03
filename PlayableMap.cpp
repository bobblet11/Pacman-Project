#include "PlayableMap.h"
//CONSTRUCTORS
PlayableMap :: PlayableMap()
{

}
PlayableMap :: PlayableMap(std::vector<GameObject*> &handle)
{
    //loads the map from txt and allocated pill objects
    initPill(handle);
}


//DECONSTRUCTORS
PlayableMap :: ~PlayableMap()
{
}


//EXTERNAL MEMBER FUNCTIONS
//handle is the vector containing pointers to all gameobjects
void PlayableMap :: initPill(std::vector<GameObject*>& handle)
{
    //opens the txt containing map data
    std::string line;
    std::fstream file;
    file.open(LAYOUT_SPRITE_SHEET);
    if (!file)
    {
        std::cout << "[ERROR] Failed to open sprite sheet." << std::endl;
        exit(1);
    }
    //count is the y value
    int count = 0;
    while(getline(file,line))
    {
        //i is the x value
        for (int i = 0; i < line.length();i++)
        {
            //if else blocks check which type of character the current x,y position in the file is
            //reads which character it is and then substitutes a string in its place to render.
            if (line[i] == '#')
            {
                map_layout[count][i] = DEFAULT_WALL_CHAR;
            }
            else if (line[i] == ' ')
            {
                map_layout[count][i] = DEFAULT_EMPTY_CHAR;
            }
            else if (line[i] == '-')
            {
                map_layout[count][i] = DEFAULT_HORIZ_DOOR;
            }
            else if (line[i] == '.') //if a pill is read
            {
                // make a pill object at this pos   
                map_layout[count][i] = DEFAULT_EMPTY_CHAR;
                GameObject * pill_ptr = new Pill(PILL_SPRITE_SHEET, i+1,count+1, 3,SMALL_PILL,SMALL_PILL_PTS);
                //push the ptr into the handle vector so that it can be accessed by other functions
                handle.push_back(pill_ptr);

            }
            else if (line[i] == '@') //if a super pill is read
            {
                // make a super pill object at this pos
                map_layout[count][i] = DEFAULT_EMPTY_CHAR;
                GameObject * pill_ptr = new Pill(PILL_SPRITE_SHEET, i+1,count+1, 3,LARGE_PILL,LARGE_PILL_PTS);
                //push the ptr into the handle vector so that it can be accessed by other functions
                handle.push_back(pill_ptr);
            }
            else //if a character that is not in the set of valid characters, then render an unknown character
            {
                map_layout[count][i] = DEFAULT_UNKNOWN;
            }
        }
        count++;
    }
    file.close();
}
//returns the string at a particular position x,y
//x and y are the coordinates that we want to read.
std::string PlayableMap :: getCharAtPos(int x, int y)
{
    return map_layout[y][x];
}

//returns a bool for whether the position x,y is moveable
//x,y is the coordinate we want to read
//object_type is the object that is accesing this function.
//object_type is used to determine what movement privelledges can be granted
//ghosts can move past the ghost spawn door, but player cannot
bool PlayableMap :: IsMoveable(int x, int y, int object_type)
{
    //if the coordinate on the map is not an empty space and isnt connected to the tunnel
    if (map_layout[y][x] != DEFAULT_EMPTY_CHAR && !((y == 14) && (x == -1 || x == 28)))
    {
        //if the object type is a ghost ie not a character, then allow the movement
        if ( map_layout[y][x] == DEFAULT_HORIZ_DOOR && object_type != 1)
        {
            //then accept movement, returns true
            return true;
        }
        //then reject the movement, returns false
        return false;
    }
    //other wise, the position is an empty space. allow movement, return true
    return true;
}





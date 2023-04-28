#include "PlayableMap.h"
//CONSTRUCTORS
PlayableMap :: PlayableMap()
{

}
PlayableMap :: PlayableMap(std::vector<GameObject*> &handle)
{
    std::string line;
    std::fstream file;
    file.open(LAYOUT_SPRITE_SHEET);
    if (!file)
    {
        std::cout << "[ERROR] Failed to open sprite sheet." << std::endl;
        exit(1);
    }
    int count = 0;
    while(getline(file,line))
    {
        for (int i = 0; i < line.length();i++)
        {
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
            else if (line[i] == '.')
            {
                // make a pill object at this pos   
                map_layout[count][i] = DEFAULT_EMPTY_CHAR;
                GameObject * pill_ptr = new Pill("Pills.txt", i+1,count+1, 3,SMALL_PILL,SMALL_PILL_PTS);
       
                handle.push_back(pill_ptr);

            }
            else if (line[i] == '@')
            {
                // make a super pill object at this pos
                map_layout[count][i] = DEFAULT_EMPTY_CHAR;
                GameObject * pill_ptr = new Pill("Pills.txt", i+1,count+1, 3,LARGE_PILL,LARGE_PILL_PTS);
       
                handle.push_back(pill_ptr);
            }
            else if (line[i] == '*')
            {
                //make cherry object at this pos
                map_layout[count][i] = DEFAULT_EMPTY_CHAR;
            }
            else
            {
                map_layout[count][i] = DEFAULT_UNKNOWN;
            }
        }
        count++;
    }
    file.close();
}


//DECONSTRUCTORS
PlayableMap :: ~PlayableMap()
{
}


//EXTERNAL MEMBER FUNCTIONS
std::string PlayableMap :: getCharAtPos(int x, int y)
{
    return map_layout[y][x];
}
bool PlayableMap :: IsMoveable(int x, int y, int object_type)
{
    if (map_layout[y][x] != DEFAULT_EMPTY_CHAR && !((y == 14) && (x == -1 || x == 28))) // make it so any x and y value can be passed and update all functions using this
    {
        if ( map_layout[y][x] == DEFAULT_HORIZ_DOOR && object_type != 1)
        {
            return true;
        }
        return false;
    }
    return true;
}
std::string PlayableMap :: mapToString()
{
    std::string out;
    for (int i =0; i<MAP_HEIGHT;i++)
    {
        for (int j =0; i<MAP_WIDTH;i++)
        {
            out+=map_layout[i][j];
        }
    }
    return out;
}




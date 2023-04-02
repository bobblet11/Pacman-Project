#include "PlayableMap.h"
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
                GameObject * pill_ptr = new Pill("Pills.txt", i+1,count+1,COLOR_WHITE,COLOR_BLACK, 1,SMALL_PILL,SMALL_PILL_PTS);
       
                handle.push_back(pill_ptr);

            }
            else if (line[i] == '@')
            {
                // make a super pill object at this pos
                map_layout[count][i] = DEFAULT_EMPTY_CHAR;
                GameObject * pill_ptr = new Pill("Pills.txt", i+1,count+1,COLOR_WHITE,COLOR_BLACK, 1,LARGE_PILL,LARGE_PILL_PTS);
       
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

PlayableMap :: ~PlayableMap()
{
}

std::string PlayableMap :: getCharAtPos(int x, int y)
{
    return map_layout[y][x];
}

bool PlayableMap :: IsMoveable(int x, int y)
{
    if (map_layout[y][x] == DEFAULT_WALL_CHAR)
    {
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




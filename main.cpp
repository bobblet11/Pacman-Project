#include "Screen.h"
#include <unistd.h>
#include <thread>
#include <chrono>
#include "Character.h"
#include "Ghosts.h"

//define object types
#define  CHARACTER 1
#define WALL 2
#define  PILL 3
#define GHOST_R 4
#define GHOST_Y 5
#define GHOST_P 6
#define GHOST_C 7

const int FRAMERATE = 60;

int main(int argc, char *argv[])
{
    bool running = true;

    std::vector<GameObject*> handle;
    
    PlayableMap map(handle);

    Screen screen(28,31,map);

    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_R, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_Y, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_C, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_P, map));
   
    handle.push_back(new Character("CharacterSprites.txt",screen.getWidth(), screen.getHeight(), map, 2,2, CHARACTER));


    cbreak();
    noecho();
    setlocale(LC_ALL,"");
    initscr();
    nodelay(stdscr,TRUE);

    if(has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();

    //colour init
    init_pair(CHARACTER, COLOR_YELLOW,COLOR_BLACK);
    init_pair(WALL, COLOR_BLUE, COLOR_BLACK);
    init_pair(PILL, COLOR_WHITE, COLOR_BLACK);
    init_pair(GHOST_R, COLOR_RED, COLOR_BLACK);
    init_pair(GHOST_Y, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GHOST_P, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(GHOST_C, COLOR_CYAN, COLOR_BLACK);

    int character_index = handle.size() -1;
    while(running)
    {
        auto start = std::chrono::steady_clock::now();

        handle.at(character_index)->handleCharacterMove(handle, character_index);
        handle.at(character_index)->updateAnimationState();

        for (int i = 0; i < handle.size(); i++)
        {
            if (handle.at(i)->object_type == GHOST_R || handle.at(i)->object_type == GHOST_Y || handle.at(i)->object_type == GHOST_P || handle.at(i)->object_type == GHOST_C )
            {
                handle.at(i)->handleState(handle.at(character_index));
            }
        }
        
        screen.render(handle);
        auto end = std::chrono::steady_clock::now();
        std::this_thread::sleep_for(std::chrono::milliseconds((1000/FRAMERATE) - std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()));
        if (handle.size() == 5)
        {
            for (int i = 0; i<handle.size(); i++)
            {
                delete handle[i];
            }
            handle.clear();
            break;
        }
    }

    //add win screen using ncurses here
    endwin();
    std::cout << "YOU WIN!" << std::endl;
}








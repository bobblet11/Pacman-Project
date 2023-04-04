#include "Screen.h"
#include <unistd.h>
#include <thread>
#include <chrono>
#include "Character.h"
#include "RedGhost.h"

//colour pairs
#define WALL_COLOUR 2

//define object types
#define  CHARACTER 1
#define WALL 2
#define  PILL 3
#define GHOST 4

const int FRAMERATE = 60;

    //since gameObjects have the neccesary functions that screen uses, i can pass a pointer thru to screen


    //initalise
        //make all game objects, variables, states and mem allocs
    //game loops
        //do a check for the current game state
        //if in game mode:
            //check for any input, on another thread?
            //perform a input check, see if the instruction is valid and doabel ie x, y check
            //do a collectable check, see if any pills need to be deleted and points need to be modified
            //do a ghost check, see if any ghosts are in way of character
            //update position and anim state of character
                //if game is ended beacuse of last pill or death
                    //commence ending procedure
            //if game is still continuing
            //do a ghost path findiing check
            //update all ghost positions and states

            //do a render process, update all objects (?that have had a change) into the frame
            //render the frame
            //wait frame rate

int main(int argc, char *argv[])
{
    bool running = true;
    std::vector<GameObject*> handle;
    
    PlayableMap map(handle);

    Screen screen(28,31,map);

    RedGhost* r_ghost_ptr;
    r_ghost_ptr = new RedGhost("GhostSprites.txt",4,4,GHOST);
    handle.push_back(r_ghost_ptr);


    Character* character_ptr;
    character_ptr = new Character("CharacterSprites.txt",screen.getWidth(), screen.getHeight(), map, 2,2, CHARACTER);
    handle.push_back(character_ptr);

        



        //terminal setup
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
	start_color();			/* Start color 			*/

    //colour init
    init_pair(CHARACTER, COLOR_YELLOW,COLOR_BLACK);
    init_pair(WALL, COLOR_BLUE, COLOR_BLACK);
    init_pair(PILL, COLOR_WHITE, COLOR_BLACK);
    init_pair(GHOST, COLOR_RED, COLOR_BLACK);
    

    int character_index = handle.size() -1;
    while(running)
    {

        handle.at(character_index)->handleCharacterMove(handle, character_index);
        handle.at(character_index)->updateAnimationState();
        handle.at(character_index-1)->handleState();
        if ( handle.size() == 1)
        {
            delete handle.at(character_index);
            handle.erase(handle.begin()+character_index);
            break;
        }
        screen.render(handle);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/FRAMERATE));



    }
    endwin();
    std::cout << "YOU WIN!" << std::endl;
}








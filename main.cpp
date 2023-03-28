#include "Screen.h"
#include <unistd.h>
#include <thread>
#include <chrono>
#include "Character.h"
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
    init_pair(10, COLOR_YELLOW, COLOR_BLACK );
    bool running = true;
    std::vector<GameObject*> handle;
    
    PlayableMap map(handle);

    Screen screen(28,31,map);

    Character* character_ptr;
    character_ptr = new Character("CharacterSprites.txt",screen.getWidth(), screen.getHeight(), map, 2,2,COLOR_YELLOW,COLOR_BLACK);
    handle.push_back(character_ptr);
   
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    
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

    while(running)
    {
        for (int i=0; i < handle.size(); i++)
        {
            handle.at(i)->handleCharacterMove();
            handle.at(i)->updateAnimationState();
        }
        
        screen.render(handle);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/FRAMERATE));
    }


    for (int i=0; i < handle.size(); i++)
    {
        delete[] handle.at(i);
    }
    endwin();

}








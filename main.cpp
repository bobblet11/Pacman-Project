//INCLUDES
#include "Screen.h"
#include <unistd.h>
#include <thread>
#include <chrono>
#include "Character.h"
#include "Ghosts.h"
#include "menu.h"

//DEFINES THE OBJECT TYPES AND THEIR ASSOCIATED COLOURS
#define  CHARACTER 1
#define WALL 2
#define  PILL 3
#define GHOST_R 4
#define GHOST_Y 5
#define GHOST_P 6
#define GHOST_C 7


//CONSTANTS
const int FRAMERATE = 60;
const int MENU = 0, INGAME = 1, WIN = 2, LOSE = 3;

void PlayGame(), highscores(), difficulty();
string Name();
int gameState = MENU;

int main(int argc, char *argv[])
{

    //INITIALISING VARIABLES AND OBJECTS
    int score = 0;
    bool running = true;
    std::vector<GameObject*> handle;
    PlayableMap map(handle);
    Screen screen(28,32,map);
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_R, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_Y, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_C, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_P, map));
    handle.push_back(new Character("CharacterSprites.txt",screen.getWidth(), screen.getHeight(), map, 2,2, CHARACTER));
    bool freightened = false;

    int character_index = handle.size() -1;
    
    menu obj;
    int x;
    std::string Game =   
                    "⠀⠀⠀⠀⣀⣤⣴⣶⣶⣶⣦⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           \n"
                    "⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⢿⣿⣿⣷⣄⠀⠀⠀⠀                                                 \n"
                    "⢀⣾⣿⣿⣿⣿⣿⣿⣿⣅⢀⣽⣿⣿⡿⠃⠀⠀⠀                                                 \n"
                    "⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                           \n"
                    "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⠁⠀⠀⣴⣶⡄⠀⣶⣶⡄⠀⣴⣶⡄ ⣴⣶⡄⠀⣶⣶⡄⠀⣴⣶⡄ ⣴⣶⡄⠀⣶⣶⡄⠀⣴⣶⡄ ⣴⣶⡄⠀⣶⣶⡄⠀⣴⣶⡄\n"
                    "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣀⠀⠙⠋⠁⠀⠉⠋⠁⠀⠙⠋⠀ ⠙⠋⠁⠀⠉⠋⠁⠀⠙⠋  ⠙⠋⠁⠀⠉⠋⠁⠀⠙⠋  ⠙⠋⠁⠀⠉⠋⠁⠀⠙⠋  \n"
                    "⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀                                             \n"
                    "⠀⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀                                             \n"
                    "   ⠙⠿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠀⠀⠀⠀⠀⠀                                                 \n"
                    "⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                 ";
    obj.menu_head(Game);
    obj.add("Play", 1, "Start a new game");
    obj.add("High Scores", 2, "See previous high scores");
    obj.add("Exit", 3, "Exit to the terminal CLI");

    //GAMELOOP
    while(running)
    {
        //MENU LOOP
        if (gameState == MENU)
        {
            x=obj.display();
            switch(x)
            {
                case 1:
                    PlayGame();
                    break;
                case 2:
                    highscores();
                    break;
                case 3:
                    system("clear");
                    directdistheplay("ThankYOU!!\nBrought to you by Ligma Ballz productions.\n");
                    usleep(3000000);
                    system("clear");
                    system("setterm -cursor on");
                    exit(0);
                default:
                    cout << x << endl;
                    break;
            }
        }
        else if (gameState == INGAME) //GAME LOOP
        {

            auto start = std::chrono::steady_clock::now();


            //CHARACTER MOVEMENT
            handle.at(character_index)->handleCharacterMove(handle, character_index, freightened);
            handle.at(character_index)->updateAnimationState();


            //GHOST MOVEMENT
            for (int i = 0; i < handle.size(); i++)
            {
                if (handle.at(i)->object_type == GHOST_R || handle.at(i)->object_type == GHOST_Y || handle.at(i)->object_type == GHOST_P || handle.at(i)->object_type == GHOST_C )
                {
                    //checks for lose scenario
                    handle.at(i)->handleState(handle.at(character_index), gameState, freightened);
                }
            }
            

            //SCORE UPDATING
            score = handle.at(character_index)->getPoints();
        

            //RENDERING
            screen.render(handle);
            mvprintw(1,2,"SCORE: %i", score);
            refresh();


            //FRAMERATE HANDLING
            auto end = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(std::chrono::milliseconds((1000/FRAMERATE) - std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()));
            

            //checks for win scenario
            if (handle.size() == 5)
            {
                for (int i = 0; i<handle.size(); i++)
                {
                    delete handle[i];
                }
                handle.clear();
                gameState = WIN;
                break;
            }
        }
        else
        {
            if (gameState == WIN)
            {
                //win page
                std::cout << "YOU WIN!" << std::endl;
                
            }
            else
            {
                //lose page
                std::cout << "YOU LOSE!" << std::endl;
            }
        }

    }
    endwin();

}


void PlayGame()
{
    system("clear");
    string name = Name();
    string statement = "Hello " + name + "\nWelcome to Ligma Ballz\n<<<Game Loading>>>\n";
    directdistheplay(statement);
    system("setterm -cursor off");
    cout << "\n\n";
    for (int i = 0; i <= 100; ++i)
    {
        if (i == 100) 
        {
            system("clear");
        }
        gotoxy((max_x / 2) + 3, (max_y / 2) - 52);
        string progress = "[" + string(i, '|') + string(100 - i, ' ') + "]";
        cout << progress << flush << " " << i << "%" << endl;
        usleep(50000);
    }
    cout << "\n";
    statement = "Game Locked and Loaded Bitch\n<<Press Enter to Start>>";
    directdistheplay(statement);
    cin.ignore();
    cin.ignore();
    system("clear");

   //INITIALISING THE NCURESES TERMINAL
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
        //CREATING COLOUR PAIRS FOR EACH OBJECT TYPE
    init_pair(CHARACTER, COLOR_YELLOW,COLOR_BLACK);
    init_pair(WALL, COLOR_BLUE, COLOR_BLACK);
    init_pair(PILL, COLOR_WHITE, COLOR_BLACK);
    init_pair(GHOST_R, COLOR_RED, COLOR_BLACK);
    init_pair(GHOST_Y, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GHOST_P, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(GHOST_C, COLOR_CYAN, COLOR_BLACK);

    gameState = INGAME;
}
void difficulty()
{
    //difficulty choosing option
    return;
}

void highscores()
{
    cout <<"We are still working on it.\nThanks for being with us." << endl;
    return;
}

string Name()
{
    string name;
    preprocess("Namebox.txt");
    gotoxy(max_x / 2, (max_y / 2) - 10);
    system("setterm -cursor on");
    cin >> name;
    system("setterm -cursor off");
    system("clear");
    return name;
}
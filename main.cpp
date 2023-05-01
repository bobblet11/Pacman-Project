//INCLUDES
#include "Screen.h"
#include <unistd.h>
#include <thread>
#include <chrono>
#include "Character.h"
#include "Ghosts.h"
#include "menu.h"
#include "middle.h"
#include "Highscores.h"

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

//FUNCTION DECLARATION
void PlayGame(), highscores(), difficulty();
string Name();
void init(vector<GameObject*> & handle, PlayableMap & map, Screen & screen, int & score, bool & freightened, int & character_index);
void initSCR();

//PLAYER NAME
string name;
string display_name;

int gameState = MENU;
bool replay = false;
int freightened_timer=0;
int main(int argc, char *argv[])
{

    //INITIALISING VARIABLES AND OBJECTS
    int score = 0;
    int timer = 0;
    bool running = true;
    vector<GameObject*> handle;
    PlayableMap map(handle);
    Screen screen(28,32,map);
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_R, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_Y, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_C, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_P, map));
    handle.push_back(new Character("CharacterSprites.txt",screen.getWidth(), screen.getHeight(), map, 14,24, CHARACTER));
    bool freightened = false;
    int character_index = handle.size() -1;
    
    menu obj;
    int x;
    string Game =   
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
    obj.add("New Game", 1, "Start a new game");
    obj.add("High Scores", 2, "See previous high scores");
    obj.add("Exit", 3, "Exit to the terminal CLI");

    //GAMELOOP
    while(running)
    {
        //MENU LOOP
        if (gameState == MENU)
        {
            system("setterm -cursor off");
            processAnimation();
            x=obj.display();
            switch(x)
            {
                case 1:
                    system("clear");
                    name = Name();
                    if (name.find(' ') != string::npos)
                    {
                        int pos = name.find(' ');
                        display_name = name.substr(0, pos);
                    }
                    PlayGame();
                    system("clear");
                    initSCR();
                    break;
                case 2:
                    highscores();
                    break;
                case 3:
                    system("clear");
                    for (int i = 5; i > 0; i--) 
                    {
                        gotoxy(0,0);
                        cout << "Back to Terminal CLI in: " << i << endl;
                        directdistheplay("Thank You\nBrought you by\nNabid Ahmed Shaan 3036087145\nBenjamin Jun-jie Glover 3035962764\nWONG Shom 3036066555\n");
                        usleep(1000000);
                    }
                    system("clear");
                    system("setterm -cursor on");
                    exit(0);
                case 4:
                    PlayGame();
                    system("clear");
                    initSCR();
                    break;
                default:
                    cout << x << endl;
                    break;
            }
        }
        else if (gameState == INGAME) //GAME LOOP
        {
            timer++;
            auto start = chrono::steady_clock::now();


            //CHARACTER MOVEMENT
            handle.at(character_index)->handleCharacterMove(handle, character_index, freightened, freightened_timer);
            handle.at(character_index)->updateAnimationState();


            //GHOST MOVEMENT
            for (int i = 0; i < handle.size(); i++)
            {
                if (handle.at(i)->object_type == GHOST_R || handle.at(i)->object_type == GHOST_Y || handle.at(i)->object_type == GHOST_P || handle.at(i)->object_type == GHOST_C )
                {
                    //checks for lose scenario
                    handle.at(i)->handleState(handle.at(character_index), gameState, freightened, freightened_timer);
                }
            }
            

            //SCORE UPDATING
            score = handle.at(character_index)->getPoints();
        

            //RENDERING
            screen.render(handle);
            mvprintw(1 + (getmax_x()/2-16),2 + (getmax_y()/2-30),"PLAYER: %s", display_name.c_str());
            mvprintw(1 + (getmax_x()/2-16),45 + (getmax_y()/2-30),"SCORE: %i", score);
            mvprintw(1 + (getmax_x()/2-16),(getmax_y()/2-30 + 26),"TIMER: %d", timer/60);
            refresh();


            //FRAMERATE HANDLING
            auto end = chrono::steady_clock::now();
            this_thread::sleep_for(chrono::milliseconds((1000/FRAMERATE) - chrono::duration_cast<chrono::milliseconds>(end-start).count()));
            

            //checks for win scenario
            if (handle.size() == 5)
            {
                score = handle.at(character_index)->getPoints();
                for (int i = 0; i<handle.size(); i++)
                {
                    delete handle[i];
                }
                handle.clear();
                gameState = WIN;
                
            }
        }
        else
        {
            clear();
            refresh();
            endwin();
            system("clear");
            if (gameState == WIN)
            {
                

               //win page
               for (int i = 5; i > 0; i--) 
                    {
                        preprocess("Win.txt");
                        usleep(800000);
                        system("clear");
                        usleep(500000);
                    }
            }
            else
            {
                //lose page
                for (int i = 5; i > 0; i--) 
                    {
                        preprocess("Loose.txt");
                        usleep(800000);
                        system("clear");
                        usleep(500000);
                    }
            }

            add_highscores(name, score, timer);
            for (int i = 5; i > 0; i--) 
            {
                gotoxy(0,0);
                cout << "Next Screen in: " << i << endl;
                processHighscore("HighScoreFinal.txt", "highscores.txt");
                usleep(800000);
            }
            system("clear");
            gameState = MENU;
            init(handle, map, screen, score, freightened, character_index);
            if (replay == false) {
                obj.add("Play Again", 4, "Play again under the same");
                replay = true;
            }
            timer = 0;
        }

    }


}


void PlayGame()
{
    system("clear");
    string statement = "Hello " + name + "\nWelcome to our version of PACMAN\n<<<Game Loading>>>\n";
    directdistheplay(statement);
    cout << "\n\n";
    for (int i = 0; i <= 100; ++i)
    {
        if (i == 100) 
        {
            system("clear");
        }
        gotoxy((getmax_x() / 2) + 3, (getmax_y() / 2) - 52);
        string progress = "[" + string(i, '|') + string(100 - i, ' ') + "]";
        cout << progress << flush << " " << i << "%" << endl;
        usleep(30000);
    }
    cout << "\n";
    statement = "READY TO START\n<<Press Enter to Start>>";
    directdistheplay(statement);
    cin.ignore();
}

void highscores()
{
    system("clear");
    processHighscore("HighScoreFinal.txt", "highscores.txt");
    cout << "\n\n\n\n\n\n\n";
    cout << ">>> Press Enter to go back to Main Menu";
    cin.ignore();
    return;
}

string Name()
{
    string name;
    preprocess("Namebox.txt");
    gotoxy(getmax_x() / 2, (getmax_y() / 2) - 10);
    system("setterm -cursor on");
    getline(cin, name);
    if (name.empty())
    {
        name = "Unknown Player";
    }
    system("setterm -cursor off");
    system("clear");
    return name;
}

void init(vector<GameObject*> & handle, PlayableMap & map, Screen & screen, int & score, bool & freightened, int & character_index)
{
    handle.clear();
    map.initPill(handle);
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_R, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_Y, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_C, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_P, map));
    handle.push_back(new Character("CharacterSprites.txt",screen.getWidth(), screen.getHeight(), map, 14,24, CHARACTER));
    score = 0;
    freightened = false;
    character_index = handle.size() -1;
}

void initSCR()
{
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
    keypad(stdscr, TRUE); 
    gameState = INGAME;
}
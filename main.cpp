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
const int FRAMERATE = 60; //framerate
const int MENU = 0, INGAME = 1, WIN = 2, LOSE = 3; //game states
const string HIGHSCORES = "Highscores.txt", HIGHSCORES_TITLE = "HighscoreTitle.txt"; //filenames for txts

//FUNCTION PROTOTYPES
void PlayGame(), highscores();
string Name();
void init(vector<GameObject*> & handle, PlayableMap & map, Screen & screen, int & score, bool & freightened, int & character_index);
void initSCR();

//PLAYER NAME
string name;
string display_name;

//GLOBAL VARIABLES
int gameState = MENU;

int main(int argc, char *argv[])
{

    //INITIALISING VARIABLES AND OBJECTS
    int score = 0;
    int timer = 0;
    bool running = true;
    bool freightened = false;
    bool replay = false;
    int freightened_timer=0;
    //initialise all the gameObjects 
    vector<GameObject*> handle;
    PlayableMap map(handle);
    Screen screen(28,32,map);
    //allocate gameobjects
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_R, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_Y, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_C, map));
    handle.push_back(new Ghosts("GhostSprites.txt",14,15,GHOST_P, map));
    handle.push_back(new Character("CharacterSprites.txt",screen.getWidth(), screen.getHeight(), map, 14,24, CHARACTER));

    int character_index = handle.size() -1;
    
    //initialise menu
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
    //Prints the Pacman head in the main menu
    obj.menu_head(Game);
    //Options in main menu
    obj.add("New Game", 1, "Start a new game");
    obj.add("High Scores", 2, "See previous high scores");
    obj.add("Exit", 3, "Exit to the terminal CLI");

    //initialise terminal
    system("setterm -cursor off");

    //start intro sequence
    intro();

    //clears input buffer
    int copy_of_input = dup(STDIN_FILENO);
    /* remove garbage from stdin */
    tcdrain(copy_of_input);
    tcflush(copy_of_input, TCIFLUSH);
    close(copy_of_input);


    //GAMELOOP
    while(running)
    {
        //MENU LOOP
        if (gameState == MENU)
        {
            x = obj.display();
            switch(x)
            {
                case 1:
                    system("clear");
                    //asks for name
                    name = Name();
                    //Only takes the first name for display if anyone inputs full name or a name with space
                    if (name.find(' ') != string::npos)
                    {
                        int pos = name.find(' ');
                        display_name = name.substr(0, pos);
                    }
                    else
                    {
                        display_name = name;
                    }
                    //Calls function to initialize game
                    PlayGame();
                    system("clear");
                    //Calls function to start game screen
                    initSCR();
                    break;
                case 2:
                    highscores();
                    break;
                case 3:
                    system("clear");
                    //Credit screen when exiting from game
                    //Also displayes a countdown for the user to wait
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
                //Case 4 adds after game has been played once to give the option of playing game under the same name
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
            //start a timer for counting how long the processes take
            auto start = chrono::steady_clock::now();
            //add a frame to timer for each frame. ie timer += 60 ever second
            timer++;

            //CHARACTER MOVEMENT
            //moves character and updates its animations -> increments its movecounts, animation_counts, inputs and directions
            handle.at(character_index)->handleCharacterMove(handle, character_index, freightened, freightened_timer);
            handle.at(character_index)->updateAnimationState();


            //GHOST MOVEMENT
            //for each ghost
            for (int i = 0; i < handle.size(); i++)
            {
                if (handle.at(i)->object_type == GHOST_R || handle.at(i)->object_type == GHOST_Y || handle.at(i)->object_type == GHOST_P || handle.at(i)->object_type == GHOST_C )
                {
                    //handle state does the ghosts behaviour, moves it, 
                    handle.at(i)->handleState(handle.at(character_index), gameState, freightened, freightened_timer);
                }
            }
            
            //SCORE UPDATING
            score = handle.at(character_index)->getPoints();
        
            //RENDERING
            //render the frame and all gameobjects
            screen.render(handle);

            //print the timer, score, and name
            mvprintw(1 + (getmax_x()/2-16),2 + (getmax_y()/2-30),"PLAYER: %s", display_name.c_str());
            mvprintw(1 + (getmax_x()/2-16),45 + (getmax_y()/2-30),"SCORE: %i", score);
            mvprintw(1 + (getmax_x()/2-16),(getmax_y()/2-30 + 26),"TIMER: %d", timer/60);

            //refresh to load all prints to screen
            refresh();


            //FRAMERATE HANDLING
            //end timer that counts time taken for processes
            auto end = chrono::steady_clock::now();
            //sleep for 1/60 of a second. subtracts the time taken to do calculations to maintain accurate 60fps.
            this_thread::sleep_for(chrono::milliseconds((1000/FRAMERATE) - chrono::duration_cast<chrono::milliseconds>(end-start).count()));
            

            //checks for win scenario
            //if there is only the 4 ghosts and 1 player
            if (handle.size() == 5)
            {
                //update the score one final time
                score = handle.at(character_index)->getPoints();
                //deallocate all gameObjects
                for (int i = 0; i<handle.size(); i++)
                {
                    delete handle[i];
                }
                //remove all pointers
                handle.clear();
                //change state so that this part of loop is not accessed anymore
                gameState = WIN;
                
            }
        }
        else //if in a win or lose situation
        {
            //clear and close the ncurses terminal
            clear();
            refresh();
            endwin();
            //clear normal terminal
            system("clear");

            if (gameState == WIN)
            {
                //animation the win title
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
                //animate the lose title
                //lose page
                for (int i = 5; i > 0; i--) 
                    {
                        preprocess("Lose.txt");
                        usleep(800000);
                        system("clear");
                        usleep(500000);
                    }
            }

            //update the highscore records
            add_highscores(name, score, timer);
            //render the highscores screen for 5*0.8 seconds
            for (int i = 5; i > 0; i--) 
            {
                gotoxy(0,0);
                //Displayes a countdown for the user to wait
                cout << "Main Menu in: " << i << endl;
                processHighscore("HighscoreTitle.txt", "highscores.txt");
                usleep(800000);
            }
            //clear screen
            system("clear");
            //reset to menu
            gameState = MENU;
            //reallocate all gameobjects and push to handle
            init(handle, map, screen, score, freightened, character_index);
            //if this is the first playthrough in this session, replay is false
            if (replay == false) {
                //adds the play again button to allow you to continue playing under same name
                obj.add("Play Again", 4, "Play again under the same name");
                replay = true;
            }
            //reset timer
            timer = 0;
            //now the menu part of loop will be run.
        }

    }


}

//Initializes game start
void PlayGame()
{
    system("clear");
    string statement = "Hello " + name + "\nWelcome to our version of PACMAN\n<<<Game Loading>>>\n";
    //Prints Welcome message
    directdistheplay(statement);
    cout << "\n\n";
    //loading bar animation
    for (int i = 0; i <= 100; ++i)
    {
        if (i == 100) 
        {
            system("clear");
        }
        //Loading bar position in the terminal screen
        gotoxy((getmax_x() / 2) + 3, (getmax_y() / 2) - 52);
        string progress = "[" + string(i, '|') + string(100 - i, ' ') + "]";
        cout << progress << flush << " " << i << "%" << endl;
        usleep(30000);
    }
    cout << "\n";
    statement = "READY TO START\n<<Press Enter to Start>>";
    //Prints that the game has loaded and ready to start
    directdistheplay(statement);
    cin.ignore();
}

//Shows highscores to the player
void highscores()
{
    system("clear");
    //Prints highscores in the terminal screen
    processHighscore(HIGHSCORES_TITLE, HIGHSCORES); 
    cout << "\n\n\n\n\n\n\n";
    //Info for user on how to get back to main menu
    cout << ">>> Press Enter to go back to Main Menu";
    cin.ignore();
    return;
}

//Requests user to input name
string Name()
{
    string name;
    //Prints a box to type name inside
    preprocess("Namebox.txt"); 
    //Puts cursor inside the box
    gotoxy(getmax_x() / 2, (getmax_y() / 2) - 10);
    //Turns on blinking cursor for visualization
    system("setterm -cursor on");
    getline(cin, name);
    //If no input was detected from user programme will assign player as Unknown Player
    if (name.empty())
    {
        name = "Unknown Player";
    }
    //Turns off blinking cursor again to avoid distractions
    system("setterm -cursor off");
    //Clears the terminal screen
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

//initialises the n curses screen. 
void initSCR()
{
     //INITIALISING THE NCURESES TERMINAL
     //set all ncurses terminal parameters
    setlocale(LC_ALL,"");//allows unicode
    initscr();//opens ncurses terminal
    noecho();
    cbreak();

    //checks if tereminal supports colour
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
    
    //switch the the game loop.
    gameState = INGAME;
}
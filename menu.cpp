//INCLUDES
#include <iostream>
#include "functions.h"
#include "menu.h"
#include "middle.h"

using namespace std;

void playG(), skins(), colors(), hs();
string Name();

int main()
{
    menu obj;
    int x;
    string Game =   "⠀⠀⠀⠀⣀⣤⣴⣶⣶⣶⣦⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                             \n"
                    "⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⢿⣿⣿⣷⣄⠀⠀⠀⠀                                                  \n"
                    "⢀⣾⣿⣿⣿⣿⣿⣿⣿⣅⢀⣽⣿⣿⡿⠃⠀⠀⠀                                                 \n"
                    "⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                            \n"
                    "⣿⣿⣿⣿⣿⣿⣿⣿⣿⠛⠁⠀⠀⣴⣶⡄⠀⣶⣶⡄⠀⣴⣶⡄ ⣴⣶⡄⠀⣶⣶⡄⠀⣴⣶⡄ ⣴⣶⡄⠀⣶⣶⡄⠀⣴⣶⡄ ⣴⣶⡄⠀⣶⣶⡄⠀⣴⣶⡄\n"
                    "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣀⠀⠙⠋⠁⠀⠉⠋⠁⠀⠙⠋⠀ ⠙⠋⠁⠀⠉⠋⠁⠀⠙⠋  ⠙⠋⠁⠀⠉⠋⠁⠀⠙⠋  ⠙⠋⠁⠀⠉⠋⠁⠀⠙⠋  \n"
                    "⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⣄⠀⠀⠀⠀⠀⠀⠀⠀                                             \n"
                    "⠀⠙⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀                                             \n"
                    "   ⠙⠿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠀⠀⠀⠀⠀⠀                                                 \n"
                    "⠀⠀⠀⠀⠀⠀⠉⠉⠉⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀                                                   ";
    obj.menu_head(Game);
    obj.add("Play", 1, "Start a new game");
    obj.add("Skins", 2, "Choose your favourite skin");
    obj.add("Colors", 3, "Choose your favourite color");
    obj.add("High Scores", 4, "See previous high scores");
    obj.add("Exit", 5, "Exit to the terminal CLI");
    
    while(true)
    {
        x=obj.display();
        switch(x)
        {
            case 1:
                playG();
                break;
            case 2:
                skins();
                break;
            case 3:
                colors();
                break;
            case 4:
                hs();
                break;
            case 5:
                system("clear");
                cout << "ThankYOU!!\nBrought to you by Ligma Ballz productions." << "\n";
                system("setterm -cursor on");
                exit(0);
            default:
                cout << x << endl;
                break;
        }
        getch();
    }
    return 0;
}

void playG()
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
    preprocess("PlayableMap.txt");
    cin.ignore();
    system("clear");
    system("setterm -cursor on");
    exit(0);
}
void skins()
{
    cout <<"We are still working on it.\nThanks for being with us." << endl;
    return;
}
void colors()
{
    menu obj;
    int x;
    obj.menu_head("Colors");
    obj.add("Red", 1);
    obj.add("Green", 2);
    obj.add("Blue", 3);
    obj.add("Yellow", 4);
    obj.add("Exit", 5, "Return to the main menu");
    x=obj.display();
    switch(x)
    {
        case 1:
            hs();
            break;
        case 2:
            hs();
            break;
        case 3:
            hs();
            break;
        case 4:
            hs();
            break;
        case 5:
            return;
            break;
        default:
            cout << x << endl;
            break;
    }
    return;
}
void hs()
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
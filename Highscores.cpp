#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int add_highscores(string name, int score)
{
    ofstream file("highscores.txt", ios::app);
    if (file.is_open()) 
    {
        file << name + ": " << score << endl;
        file.close();
    } 
    else 
    {
        cout << "Unable to open file" << endl;
    }
    return 0;
}

//Need to add sorting
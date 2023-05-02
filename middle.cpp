#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <cmath>
#include <sstream>
#include "functions.h"
#include "middle.h"
#include <sstream>

using namespace std;

//SCREEN SIZE CO-ORDINATES
int max_x = getmax_x();
int max_y = getmax_y();

//Displays everything in the middle of the terminal window
int distheplay(string s, int pp) 
{
    int s_width = s.length();
    int x = (max_y - s_width) / 2;
    int y = (max_x / 2) - pp;
    cout << "\033[" << y << ";" << x << "H";
    cout << s << endl;
    return 0;
}

//Processes texts from text files for printing contents of the file in the middle of the terminal window 
int preprocess(string filename) 
{
    int line_count = 0;
    int smthn;

    //Opens a file and counts the lines inside a file
    ifstream file(filename);
    if (file.is_open()) 
    {
        string line;
        while (getline(file, line)) 
        { 
            line_count++;
        }
        smthn = floor(static_cast<double>(line_count) / 2);
        file.close();
    } 
    else 
    {
        cout << "Unable to open file" << endl;
    }

    //Opens the file to print the contents in the middle of the terminal line by line
    ifstream samefile(filename);
    if (samefile.is_open())
    {
        string line;
        while (getline(samefile, line)) 
        {
            distheplay(line, smthn);
            smthn--;
        }
        samefile.close();
    }
    return 0;
}

//Prints passed strings directly in the middle of the terminal window
int directdistheplay(string my_string) 
{
    stringstream ss(my_string);
    string line;
    int line_count = 0;
    int smthn;
    //Loop to count how many lines are in the string
    while (getline(ss, line, '\n')) 
    {
        line_count++;
    }
    smthn = floor(static_cast<double>(line_count) / 2);
    ss.clear();
    ss.seekg(0);
    //Loop to print the strings in the middle of the terminal line by line
    while (getline(ss, line, '\n')) 
    {
        distheplay(line, smthn);
        smthn--;
    } 
    return 0;
}

//Processes and shows highscores in the middle of the terminal window after win or lose from highscores file
//Process conducts: Adding the contents of two files to display together
void processHighscore(string highscore_title, string highscores)
{
    string final_string, line;
    int count = 0;
    ifstream title;
    title.open(highscore_title);
    if (!title.fail())
    {
        while (getline(title,line))
        {
            final_string += line + "\n";
            count++;
        }
    }
    title.close();
    
    ifstream scores;
    scores.open(highscores);

    if (!scores.fail())
    {
        for (int i=0; i < 10; i++)
        {
            getline(scores,line);
            final_string += line + "\n";
            count++;
        }
    }
    scores.close();

    directdistheplay(final_string);
}

//Processes intro animation and shows when the programme has started
void processAnimation(string filename, int time) 
{
    system("clear");
    string final_line = "";
    ifstream file(filename);
    if (file.is_open()) 
    {
        string line;
        while (getline(file, line)) 
        {
            if (line.find("END") != string::npos) 
            {
                directdistheplay(final_line);
                usleep(time);
                final_line = "";
            }
            else
            {
                final_line += line + '\n';
            }
        }
        file.close();
    } 
    else 
    {
        cout << "Unable to open file" << endl;
    }
}

//Conducts the intro animation in the terminal window using multiple text files
void intro()
{
    processAnimation("PACMAN-1.txt", 500000);
    for (int i = 2; i > 0; i--) 
    { 
        preprocess("PACMAN.txt"); 
        usleep(800000); 
        system("clear"); 
        usleep(500000); 
    }
    for (int i = 3; i > 0; i--) 
    { 
        processAnimation("PACMAN-2.txt", 120000); 
    }
    processAnimation("PACMAN-3.txt", 40000);
}
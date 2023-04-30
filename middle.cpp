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

int distheplay(string s, int pp) 
{
    int s_width = s.length();
    int x = (max_y - s_width) / 2;
    int y = (max_x / 2) - pp;
    cout << "\033[" << y << ";" << x << "H";
    cout << s << endl;
    return 0;
}

int preprocess(string filename) 
{
    int line_count = 0;
    int smthn;
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

int directdistheplay(string my_string) 
{
    stringstream ss(my_string);
    string line;
    int line_count = 0;
    int smthn;
    while (getline(ss, line, '\n')) 
    {
        line_count++;
    }
    smthn = floor(static_cast<double>(line_count) / 2);
    ss.clear();
    ss.seekg(0);
    while (getline(ss, line, '\n')) 
    {
        distheplay(line, smthn);
        smthn--;
    } 
    return 0;
}

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

    distheplay(final_string, count/2);



}
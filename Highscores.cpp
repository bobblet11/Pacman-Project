#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "middle.h"
using namespace std;

//structure to store the data of each unique person
struct person
{
    string name;
    int score;

    person(int score_, string name_)
    {
        score = score_;
        name = name_;
    };
};
//compare the scores of Person struct when sorting through STL containers
bool operator<(const person &a, const person &b)
{
    return a.score < b.score;
}

//sorts and stores highscore in highscores.txt file
void add_highscores(string name, int score, int timer)
{
    //handles the time bonus/penalty
    const int time_multiplier = 11; // anything past 70secs causes negative points to be added
    int final_score = score + (1000 - time_multiplier * (timer / 60));
    if (final_score < 0) // if player takes around way more than 90 seconds to complete game, they get 0, not negative score
    {
        final_score = 0;
    }

    //updates the timer and printst the highscores
    for (int i = 5; i > 0; i--) 
    {
        gotoxy(0,0);
        cout << "Highscores in: " << i << endl;
        directdistheplay("POINT SCORE: " + to_string(score) + "\nTIME " + (((1000 - time_multiplier * (timer / 60)) < 0) ? "PENALTY: " : "BONUS: ") + to_string((1000 - time_multiplier * (timer / 60))) + "\nTOTAL SCORE: " + to_string(final_score));
        usleep(800000);
    }
    system("clear");

    //will add in the current player's highscore under their name
    int temp_score;
    string temp_name;
    string line;

    vector<person> scores;

    vector<person>::iterator ptr = scores.begin();
    scores.push_back(person(final_score, name));

    //opens and loads all the highscores into the vector as Persons objects
    ifstream infile;
    infile.open("Highscores.txt");

    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            ptr = scores.begin();
            //creates person object from the line in the highscores records textfile
            temp_score = stoi(line.substr(line.find_last_of(':') + 1));
            temp_name = line.substr(0, line.find_last_of(':'));
            person p1(temp_score, temp_name);

            //checks if there any duplicates of the name in the textfile
            int count = 0;
            for (int i = 0; i < scores.size(); i++)
            {
                //if there is already a record, if the score is greater, replace it
                //>ie reads the txt file and gets the largest score under a unique name
                if ((*ptr).name == temp_name)
                {
                    if ((*ptr).score <= temp_score)
                    {
                        (*ptr) = p1;
                    }
                    break;
                }
                else
                {
                    count++;
                }
                ptr++;
            }


            if (count == scores.size())
            {
                scores.push_back(p1);
            }
        }
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
    infile.close();

    ofstream outfile;
    outfile.open("Highscores.txt");

    //sorts the scores by numerical order
    sort(scores.begin(), scores.end());
    reverse(scores.begin(), scores.end());

    //writes unique, sorted scores to the txt file -> overwrites
    if (outfile.is_open())
    {
        ptr = scores.begin();
        for (int i = 0; i < scores.size(); i++)
        {
            outfile << (*ptr).name << ":" << (*ptr).score << "\n";
            ptr++;
        }
    }
    else
    {
        cout << "Unable to open file" << endl;
    }
    outfile.close();
}
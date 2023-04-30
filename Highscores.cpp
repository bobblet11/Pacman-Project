#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "middle.h"
using namespace std;

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

bool operator<(const person &a, const person &b)
{
    return a.score < b.score;
}

void add_highscores(string name, int score, int timer)
{
    const int time_multiplier = 11; // anything past 70secs causes negative points to be added
    int final_score = score + (1000 - time_multiplier * (timer / 60));
    if (final_score < 0) // if player takes 10 minutes or something, they get 0, not negative score
    {
        final_score = 0;
    }

    directdistheplay("POINT SCORE: " + to_string(score) + "\nTIME " + (((1000 - time_multiplier * (timer / 60)) < 0) ? "PENALTY: " : "BONUS: ") + to_string((1000 - time_multiplier * (timer / 60))) + "\n TOTAL SCORE: " + to_string(final_score));
    usleep(800000 * 5);
    system("clear");

    int temp_score;
    string temp_name;
    string line;
    vector<person> scores;
    vector<person>::iterator ptr = scores.begin();
    scores.push_back(person(final_score, name));

    ifstream infile;
    infile.open("highscores.txt");

    if (infile.is_open())
    {
        while (getline(infile, line))
        {
            ptr = scores.begin();
            temp_score = stoi(line.substr(line.find_last_of(':') + 1));
            temp_name = line.substr(0, line.find_last_of(':'));
            person p1(temp_score, temp_name);
            int count = 0;
            for (int i = 0; i < scores.size(); i++)
            {
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
    outfile.open("highscores.txt");

    sort(scores.begin(), scores.end());
    reverse(scores.begin(), scores.end());

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

// Need to add sorting
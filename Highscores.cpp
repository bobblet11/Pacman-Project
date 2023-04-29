#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

void add_highscores(string name, int score)
{
    int temp;
    string line;

    map<int, string> scores; 

    scores[score] = name + ':' + to_string(score);

    ifstream infile;
    infile.open("highscores.txt");

    if (infile.is_open()) 
    {
        while (getline(infile, line))
        {
            temp = stoi(line.substr(line.find_last_of(':')));
            scores[temp] = line;
        }
    } 
    else 
    {
        cout << "Unable to open file" << endl;
    }
    infile.close();

    map<int,string>::iterator ptr = scores.begin();

    ofstream outfile;
    outfile.open("highscores.txt");
    if (outfile.is_open()) 
    {
        for (int i =0; i < scores.size(); i++)
        {
            outfile << (*ptr).second;
            ptr++;
        }
    } 
    else 
    {
        cout << "Unable to open file" << endl;
    }
    outfile.close();
}



//Need to add sorting
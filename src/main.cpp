// **************************************************************************
//  File       [main.cpp]
//  Author     [Shu-Yu Lin]
//  Synopsis   [The main program of 2020 data structure PA1]
// **************************************************************************
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include <new>
#include <ctime>
#include <algorithm>

using namespace std;
//warning message
void help_message()
{
    cout << "usage: ./mps <input file name> <output file name>" << endl;
}
void pagerank(double d, double DIFF)
{
    vector<double> PR(501, 1 / 501);
    double diff = 0;

    return;
}

int main()
{
    //////////// read the input file /////////////
    for (int i = 0; i < 500; i++)
    {
        fstream fin("inputs/page" + to_string(i));
        fstream fout;
        fout.open("outputs/test" + to_string(i) + ".out", ios::out);
        string pages;
        vector<string> words;
        while (fin >> pages)
        {
            if (pages == "---------------------")
            {
                while (fin >> pages)
                {
                    //fout << pages << endl;
                    bool exist = false;
                    for (int i = 0; i < words.size(); i++)
                    {
                        if (pages == words[i])
                            exist = true;
                    }
                    if (exist == false)
                        words.push_back(pages);
                }
            }
            else
                continue;
        }
        for (int i = 0; i < words.size(); i++)
            cout << words[i] << endl;
        fin.close();
        fout.close();
    }
    return 0;
}
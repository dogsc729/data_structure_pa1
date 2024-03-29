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
#include <iomanip>

using namespace std;
//warning message
void help_message()
{
    cout << "usage: ./mps <input file name> <output file name>" << endl;
}

int main()
{
    vector<string> words;
    //////////// read the input file /////////////
    for (int i = 0; i < 500; i++)
    {
        fstream fin("inputs/page" + to_string(i));
        string pages;
        while (fin >> pages)
        {
            if (pages == "---------------------")
            {
                while (fin >> pages)
                {
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
        fin.close();
    }
    sort(words.begin(), words.end());
    /*for (int i = 0; i < words.size(); i++)
        cout << words[i] << endl;
    cout << words.size();*/
    fstream fout;
    fout.open("outputs/reverseindex.txt", ios::out);
    vector<vector<int>> wordsList(words.size());
    for (int i = 0; i < 500; i++)
    {
        fstream fin("inputs/page" + to_string(i));
        string pages;
        while (fin >> pages)
        {
            if (pages == "---------------------")
            {
                while (fin >> pages)
                {
                    for (int j = 0; j < words.size(); j++)
                    {
                        if (words[j] == pages)
                        {
                            bool exist = false;
                            for (int k = 0; k < wordsList[j].size(); k++)
                            {
                                if (wordsList[j][k] == i)
                                    exist = true;
                            }
                            if (exist == false)
                                wordsList[j].push_back(i);
                        }
                    }
                }
            }
            else
                continue;
        }
        fin.close();
    }
    for (int i = 0; i < wordsList.size(); i++)
    {
        fout << setiosflags(ios::left) << setw(19) << words[i] << "   ";
        for (int j = 0; j < wordsList[i].size(); j++)
            fout << "page" << wordsList[i][j] << " ";
        fout << endl;
    }
    /*for (int i = 0; i < words.size(); i++)
        cout << words[i] << endl;*/
    return 0;
}
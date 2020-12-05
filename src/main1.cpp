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
    vector<int> outbranching(500, 0);
    //////////// read the input file /////////////
    for (int i = 0; i < 500; i++)
    {
        fstream fin("inputs/page" + to_string(i));
        fstream fout;
        fout.open("outputs/test" + to_string(i) + ".out", ios::out);
        string pages;
        while (fin >> pages)
        {
            if (pages == "---------------------")
                break;
            int number = std::stoi(pages.substr(4));
            outbranching[number]++;
        }
        fin.close();
        fout.close();
    }
    for (int i = 0; i < 500; i++)
        cout << "page" << i << " " << outbranching[i] << endl;
    return 0;
}
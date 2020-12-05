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
#include <map>

using namespace std;
//warning message
void help_message()
{
    cout << "usage: ./mps <input file name> <output file name>" << endl;
}
struct comp
{
    template <typename T>

    // Comparator function
    bool operator()(const T &l,
                    const T &r) const
    {
        if (l.first != r.first)
        {
            return l.first < r.first;
        }
        return l.second < r.second;
    }
};

// Function to sort the map according
// to value in a (key-value) pairs
void sort(map<int, int> &PR)
{

    // Declare set of pairs and insert
    // pairs according to the comparator
    // function comp()
    set<pair<int, int>, comp> S(PR.begin(),
                                PR.end());
    // Print the sorted value
    for (auto &it : S)
    {
        cout << it.first << ' '
             << it.second << endl;
    }
}
void pagerank(vector<int> &outbranching, vector<vector<int>> &citations, double d, double DIFF)
{
    map<int,double> PR(501, double(1) / 501);
    double diff = 0;
    for (int i = 0; i < 501; i++)
    {
        double PRbefore = PR[i];
        double PRdivCR = 0;
        for (int j = 0; j < citations[i].size(); j++)
        {
            PRdivCR = PRdivCR + PR[citations[i][j]] / outbranching[citations[i][j]];
        }
        PR[i] = double((1 - d)) / 501 + d * (PRdivCR);
        diff = diff + abs(PRbefore - PR[i]);
    }
    while (diff >= DIFF)
    {
        diff = 0;
        for (int i = 0; i < 501; i++)
        {
            double PRbefore = PR[i];
            double PRdivCR = 0;
            for (int j = 0; j < citations[i].size(); j++)
            {
                PRdivCR = PRdivCR + PR[citations[i][j]] / outbranching[citations[i][j]];
            }
            PR[i] = double((1 - d)) / 501 + d * (PRdivCR);
            diff = diff + abs(PRbefore - PR[i]);
        }
    }
    for (int i = 0; i < 501; i++)
        cout << PR[i] << endl;
    return;
}

int main()
{
    vector<int> outbranching(501, 0);
    vector<vector<int>> citations(501);
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
            citations[number].push_back(i);
        }
        fin.close();
        fout.close();
    }
    /*for (int i = 0; i < 501; i++)
        cout << "page" << i << " " << outbranching[i] << endl;*/
    /*for (int i = 0; i < 501; i++)
    {
        cout << "page" << i << " ";
        for (int j = 0; j < citations[i].size(); j++)
        {
            cout << citations[i][j] << " ";
        }
        cout << endl;
    }*/
    pagerank(outbranching, citations, 0.25, 0.1);
    return 0;
}
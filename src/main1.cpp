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
#include <iomanip>
//fuck"
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
        if (l.second != r.second)
        {
            return l.second > r.second;
        }
        return l.first > r.first;
    }
};

// Function to sort the map according
// to value in a (key-value) pairs
void sort(map<int, double> &PR, vector<int> &outbranching, double d, double DIFF)
{
    fstream fout;
    fout.open("outputs/pr_" + to_string(int(d * 100)) + "_" + to_string(DIFF).substr(2, 3) + ".txt", ios::out);
    // Declare set of pairs and insert
    // pairs according to the comparator
    // function comp()
    set<pair<int, double>, comp> S(PR.begin(),
                                   PR.end());
    // Print the sorted value
    for (auto &it : S)
    {
        fout << "page" << setiosflags(ios::left) << setw(3) << it.first << ' ' << setw(3) << outbranching[it.first] << " " << it.second << endl;
    }
}
void pagerank(vector<int> &outbranching, vector<vector<int>> &citations, double d, double DIFF)
{
    map<int, double> PR;
    for (int i = 0; i < 501; i++)
    {
        PR[i] = double(1) / 501;
    }
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
    /*for (int i = 0; i < 501; i++)
        cout << PR[i] << endl;*/
    sort(PR, outbranching, d, DIFF);
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
        string pages;
        while (fin >> pages)
        {
            if (pages == "---------------------")
                break;
            int number = std::stoi(pages.substr(4));
            outbranching[i]++;
            citations[number].push_back(i);
        }
        fin.close();
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
    pagerank(outbranching, citations, 0.85, 0.001);
    return 0;
}
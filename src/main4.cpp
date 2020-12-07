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
#include <iterator>

using namespace std;
//warning message
void help_message()
{
    cout << "usage: ./mps <input file name> <output file name>" << endl;
}

template <class Container>
void split1(const std::string &str, Container &cont)
{
    std::istringstream iss(str);
    std::copy(std::istream_iterator<std::string>(iss),
              std::istream_iterator<std::string>(),
              std::back_inserter(cont));
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
void sort(map<int, double> &PR)
{

    // Declare set of pairs and insert
    // pairs according to the comparator
    // function comp()
    set<pair<int, double>, comp> S(PR.begin(),
                                   PR.end());
    // Print the sorted value
    /*for (auto &it : S)
    {
        cout << "page" << setiosflags(ios::left) << setw(3) << it.first << ' ' << setw(3) << outbranching[it.first] << " " << it.second << endl;
    }*/
}
void sort_topten(map<int, double> &list)
{

    // Declare set of pairs and insert
    // pairs according to the comparator
    // function comp()
    set<pair<int, double>, comp> S(list.begin(),
                                   list.end());
    // Print the sorted value
    int count = 10;
    for (auto &it : S)
    {
        if (count == 0)
            break;
        cout << "page" << setiosflags(ios::left) << setw(3) << it.first << " ";
        count--;
    }
}
map<int, double> pagerank(vector<int> &outbranching, vector<vector<int>> &citations, double d, double DIFF)
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
    sort(PR);
    return PR;
}

int main(int argc, char *argv[])
{
    vector<string> words; //存所有字
    vector<int> outbranching(501, 0);
    vector<vector<int>> citations(501);
    vector<vector<string>> wordlistofeachpage(500);
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
            {
                while (fin >> pages)
                {
                    wordlistofeachpage[i].push_back(pages);
                    fout << pages << endl;
                    bool exist = false;
                    for (int i = 0; i < words.size(); i++)
                    {
                        if (pages == words[i])
                            exist = true;
                    }
                    if (exist == false)
                        words.push_back(pages);
                }
                break;
            }
            //break;
            int number = std::stoi(pages.substr(4));
            outbranching[i]++;
            citations[number].push_back(i);
        }
        fin.close();
        fout.close();
    }
    sort(words.begin(), words.end());
    vector<vector<int>> wordsList(words.size()); //對應的word裡面有哪些page有包含
    for (int i = 0; i < 500; i++)
    {
        fstream fin("inputs/page" + to_string(i));
        fstream fout;
        fout.open("outputs/test" + to_string(i) + ".out", ios::out);
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
        fout.close();
    }
    map<int, double> PR = pagerank(outbranching, citations, 0.25, 0.1);

    fstream fin("inputs/list.txt");
    string word;
    int count = 0;
    while (getline(fin, word))
    {
        vector<string> wordseq;
        split1(word, wordseq);
        count = wordseq.size();
        /*cout << count << endl
             << word << endl;*/
        if (count == 1)
        {
            map<int, double> singlelist;
            bool exist = false;
            for (int i = 0; i < words.size(); i++)
            {
                if (wordseq[0] == words[i])
                    exist = true;
            }
            if (exist == false)
                cout << "none" << endl;
            else
            {
                for (int i = 0; i < words.size(); i++)
                {
                    if (wordseq[0] == words[i])
                    {
                        for (int j = 0; j < wordsList[i].size(); j++)
                        {
                            singlelist.insert({wordsList[i][j], PR[wordsList[i][j]]});
                        }
                    }
                }
                sort_topten(singlelist);
                cout << endl;
            }
        }
        else
        {
            bool cases = true;
            //count larger than one, AND case
            for (int i = 0; i < wordseq.size(); i++)
            {
                bool exist = false;
                for (int j = 0; j < words.size(); j++)
                {
                    if (wordseq[i] == words[j])
                        exist = true;
                }
                //if one of the words is not exist in the wordlist
                if (exist == false)
                {
                    cases = false;
                    cout << "AND none" << endl;
                    break;
                }
            }
            //所有字都存在wordlist
            if (cases == true)
            {
                //cout << "fuck" << endl;
                vector<int> searchlist; //存候選人
                //from page0 to page499
                for (int i = 0; i < 500; i++)
                { //for each word in wordsequence
                    bool exist = false;
                    for (int j = 0; j < wordseq.size(); j++)
                    { //for every word in that page
                        for (int k = 0; k < wordlistofeachpage[i].size(); k++)
                        {
                            if (wordseq[j] == wordlistofeachpage[i][k])
                            { //if we find that word,find the next word!
                                exist = true;
                                break;
                            }
                            else
                                exist = false;
                        }
                        if (exist == false) //if we cant find that word in the intire page
                            break;
                    }
                    if (exist == true) //if we find all the word in one page
                        searchlist.push_back(i);
                }
                if (searchlist.size() > 0)
                {
                    cout << "AND ";
                    for (int i = 0; i < 10; i++)
                    {
                        cout << searchlist[i] << " ";
                    }
                    cout << endl;
                }
            }
            //OR case
            map<int, double> ranklist;
            for (int i = 0; i < wordseq.size(); i++)
            {
                for (int j = 0; j < words.size(); j++)
                {
                    if (wordseq[i] == words[j])
                    {
                        for (int k = 0; k < wordsList[j].size(); k++)
                        {
                            ranklist.insert({wordsList[j][k], PR[wordsList[j][k]]});
                        }
                    }
                }
            }
            cout << "OR ";
            sort_topten(ranklist);
            cout << endl;
        }
    }
    return 0;
}
/*for (int i = 0; i < wordlistofeachpage.size(); i++)
    {
        for (int j = 0; j < wordlistofeachpage[i].size(); j++)
        {
            cout << wordlistofeachpage[i][j];
        }
    */
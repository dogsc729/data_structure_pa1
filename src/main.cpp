// **************************************************************************
//  File       [main.cpp]
//  Author     [Shu-Yu Lin]
//  Synopsis   [The main program of 2020 data structure PA1]
// **************************************************************************
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//warning message
void help_message()
{
    cout << "usage: ./mps <input file name> <output file name>" << endl;
}

int main(int argc, char *argv[]){
    if(argc != 2){
        help_message();
    }
    return 0;
}
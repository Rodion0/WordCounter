//--------------------------------------------------------------------
//				CS315-001  Assignment 2
//--------------------------------------------------------------------
// Author: Justin Hamilton
// Date: 3/16/21
// Description: Given a text, return a word frequency count
// Assistance: We'll See
//--------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <iterator>
#include <map>
#include <string>
using namespace std;

string santizeWords(string input)
{
    string newInput;
    for (int i = 0; i < input.size(); i++)
    {
        if (isalpha(input[i]))
        {
            newInput += input[i];
        }
        else
        {
            continue;
        }
    }
    return newInput;
}

int main(int argc, char const *argv[])
{
    ifstream file("data.txt");
    string word;

    map<string, int> words;

    while (file >> word)
    {
        string goodWord;
        goodWord = santizeWords(word);
        words[goodWord]++;
    }
    file.close();

    map<string, int>::iterator itr;
    for (itr = words.begin(); itr != words.end(); itr++)
    {
        cout << itr->first << " " << itr->second << '\n';
    }
    cout << endl;
    return 0;
}

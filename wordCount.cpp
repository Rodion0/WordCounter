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
    }
    return newInput;
}

multimap<int, string> invert(map<string, int> m)
{
    multimap<int, string> inversions;
    map<string, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++)
    {
        inversions.insert(make_pair(it->second, it->first));
    }
    return inversions;
}

int main(int argc, char const *argv[])
{
    ifstream file("data.txt");
    string word;

    map<string, int> words;
    multimap<int, string> occurances;

    while (file >> word)
    {
        string goodWord = santizeWords(word);
        words[goodWord]++;
    }
    file.close();

    map<string, int>::iterator itr;
    for (itr = words.begin(); itr != words.end(); itr++)
    {
        cout << itr->first << " " << itr->second << '\n';
    }
    cout << endl;

    // Make way to sort based on values
    occurances = invert(words);
    multimap<int, string>::iterator itr2;
    for (itr2 = occurances.end(); itr2 != occurances.begin(); itr2--)
    {
        cout << itr2->second << " " << itr2->first << '\n';
    }
    cout << endl;
}

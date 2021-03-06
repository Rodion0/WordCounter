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

//Will be used in final implmentation
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

// The Various Sort Functions will take the place of this
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
        if (goodWord.length() != 0)
        {
            words[goodWord]++;
        }
    }

    file.close();

    map<string, int>::iterator itr;
    cout << "Word List: " << endl;
    for (itr = words.begin(); itr != words.end(); itr++)
    {
        cout << itr->first << " " << itr->second << endl;
    }
    cout << endl;

    // Make way to sort based on values
    occurances = invert(words);
    multimap<int, string>::iterator itr2;
    cout << "Occurance List: " << endl;
    for (itr2 = occurances.end(); itr2 != occurances.begin(); itr2--)
    {
        if (itr2->second.length() != 0)
        {
            cout << itr2->second << " " << itr2->first << endl;
        }
    }
}

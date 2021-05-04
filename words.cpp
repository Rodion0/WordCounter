//--------------------------------------------------------------------
//				CS315-001  Assignment 2
//--------------------------------------------------------------------
// Author: Justin Hamilton
// Date: 5/4/21
// Description: Given a text, return a word frequency count
// Assistance: Tau Beta Pi tutoring, Notes
//--------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

const int BUCKET_SIZE = 10;

//Node Class
class node
{
public:
    friend class hashtable;
    node();
    node(string _key, int _value);
    string getKey();
    int getValue();

private:
    string key;
    int value;
    node *next;
};

//--------------------------------------------------------------------------------------
//                                      getKey()
//--------------------------------------------------------------------------------------
// Returns: key of node
//--------------------------------------------------------------------------------------
string node::getKey()
{
    return key;
}

//--------------------------------------------------------------------------------------
//                                      getRoot()
//--------------------------------------------------------------------------------------
// Returns: value of node
//--------------------------------------------------------------------------------------
int node::getValue()
{
    return value;
}

//--------------------------------------------------------------------------------------
//                                      node()
//--------------------------------------------------------------------------------------
// Given: key, value
// Sets respective trait to given value
//--------------------------------------------------------------------------------------
node::node(string _key, int _value)
{
    key = _key;
    value = _value;
    next = NULL;
}

//--------------------------------------------------------------------------------------
//                                      node()
//--------------------------------------------------------------------------------------
// Default Constructor
//--------------------------------------------------------------------------------------
node::node()
{
    key = "";
    value = 0;
    next = NULL;
}

//HashTable class
class hashtable
{
public:
    hashtable();
    // Insert Method based on key, Seperate Chaining using basic Linked List
    void insert(string key, int value);
    // Hashing function
    int hashFunction(string input);
    //Insert into vector to be used for sorting
    vector<pair<string, int>> insertIntoVector(vector<node *> table);
    // Merge Sort based on Key
    void sortKeys(vector<pair<string, int>> &table, int lowIndex, int highIndex);
    //Helper Function for sortValue
    void mergeKeys(vector<pair<string, int>> &table, int lowIndex, int mid_point, int highIndex);
    //Sort Based on Value
    void sortValue(vector<pair<string, int>> &table, int lowIndex, int highIndex);
    //Helper Function for sortValue
    void mergeValue(vector<pair<string, int>> &table, int lowIndex, int mid_point, int highIndex);
    //Print based on Value&
    void printByValue();
    // Print based on Key
    void printByKey();

private:
    vector<node *> buckets;
};

//--------------------------------------------------------------------------------------
//                                      hashtable()
//--------------------------------------------------------------------------------------
// Default Constructor
// Fills up buckets with empty nodes
//--------------------------------------------------------------------------------------
hashtable::hashtable()
{
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        buckets.push_back(new node());
    }
}

//--------------------------------------------------------------------------------------
//                                      hashFunction()
//--------------------------------------------------------------------------------------
// Given: string
// Calculates hash value of given string
//--------------------------------------------------------------------------------------
int hashtable::hashFunction(string s)
{
    int hash_index = 0;
    if (s.length() > 0)
    {
        for (int i = 0; i < int(s.length()); i++)
        {
            hash_index += int(char(s[i]));
        }
        if (hash_index % s.length() == 0)
        {
            hash_index = (hash_index - s.length() + 1) % BUCKET_SIZE;
        }
        else
        {
            hash_index = (hash_index - s.length()) % BUCKET_SIZE;
        }
    }
    return hash_index;
}

//--------------------------------------------------------------------------------------
//                                      insert()
//--------------------------------------------------------------------------------------
// Given: some string, some int
// Inserts a node with given string and int into hashtable
//--------------------------------------------------------------------------------------
void hashtable::insert(string key, int value)
{
    //Calcuate Key with Hash Function
    int hash_key = hashFunction(key);
    node *element = buckets[hash_key];
    node *traveler = new node(key, value);
    //Case for When Nothing Is at Hash Index
    if (element->key.empty())
    {
        buckets[hash_key] = traveler;
    }
    //Case for when Something is Hash Index
    else
    {
        node *temp = element;
        //Get to end of list
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = traveler;
    }
}

//--------------------------------------------------------------------------------------
//                                      mergeKeys()
//--------------------------------------------------------------------------------------
// Given: vector of pairs of strings and int, some int, some int, some int
// Merges the elements in the vector based on keys
//--------------------------------------------------------------------------------------
void hashtable::mergeKeys(vector<pair<string, int>> &table, int lowIndex, int mid_point, int highIndex)
{
    int low = 0;
    int high = 0;
    int both = lowIndex;
    vector<pair<string, int>> smaller(mid_point - lowIndex + 1);
    vector<pair<string, int>> larger(highIndex - mid_point);

    //Insert into respective vector based on midpoint
    for (int i = 0; i < (mid_point - lowIndex + 1); i++)
    {
        smaller[i] = table[lowIndex + i];
    }
    for (int j = 0; j < (highIndex - mid_point); j++)
    {
        larger[j] = table[mid_point + 1 + j];
    }

    //While walking concurrently through each vector, compare elements from both lists
    while (low < (mid_point - lowIndex + 1) && high < (highIndex - mid_point))
    {
        //Insert correcting ordering into table
        if (smaller[low].first.compare(larger[high].first) <= 0)
        {

            table[both] = smaller[low];
            low++;
        }
        else
        {
            table[both] = larger[high];
            high++;
        }
        both++;
    }

    //Put anything that is left in the vectors back into table
    for (int i = low; i < smaller.size(); i++)
    {
        table[both] = smaller[i];
        both++;
    }

    for (int i = high; i < larger.size(); i++)
    {
        table[both] = larger[i];
        both++;
    }
}

//--------------------------------------------------------------------------------------
//                                      sortKeys()
//--------------------------------------------------------------------------------------
// Given: vector of pair of strings and ints, some int, some int
// Sorts table based on keys using merge sort
//--------------------------------------------------------------------------------------
void hashtable::sortKeys(vector<pair<string, int>> &table, int lowIndex, int highIndex)
{
    if (lowIndex < highIndex)
    {
        int midpoint = (lowIndex + highIndex) / 2;
        sortKeys(table, lowIndex, midpoint);
        sortKeys(table, midpoint + 1, highIndex);
        mergeKeys(table, lowIndex, midpoint, highIndex);
    }
}

//--------------------------------------------------------------------------------------
//                                      mergeValue()
//--------------------------------------------------------------------------------------
// Given: vector of pairs of strings and int, some int, some int, some int
// Merges the elements in the vector based on values
//--------------------------------------------------------------------------------------
void hashtable::mergeValue(vector<pair<string, int>> &table, int lowIndex, int mid_point, int highIndex)
{
    int low = 0;
    int high = 0;
    int both = lowIndex;
    vector<pair<string, int>> smaller(mid_point - lowIndex + 1);
    vector<pair<string, int>> larger(highIndex - mid_point);

    //Insert into respective vector based on midpoint
    for (int i = 0; i < (mid_point - lowIndex + 1); i++)
    {
        smaller[i] = table[lowIndex + i];
    }
    for (int j = 0; j < (highIndex - mid_point); j++)
    {
        larger[j] = table[mid_point + 1 + j];
    }
    //While walking concurrently through each vector, compare elements from both lists
    while (low < (mid_point - lowIndex + 1) && high < (highIndex - mid_point))
    {
        if (smaller[low].second <= larger[high].second)
        {

            table[both] = smaller[low];
            low++;
        }
        else
        {
            table[both] = larger[high];
            high++;
        }
        both++;
    }
    //Put anything that is left in the vectors back into table
    for (int i = low; i < smaller.size(); i++)
    {
        table[both] = smaller[i];
        both++;
    }

    for (int i = high; i < larger.size(); i++)
    {
        table[both] = larger[i];
        both++;
    }
}

//--------------------------------------------------------------------------------------
//                                      sortValue()
//--------------------------------------------------------------------------------------
// Given: vector of pair of strings and ints, some int, some int
// Sorts table based on values using merge sort
//--------------------------------------------------------------------------------------
void hashtable::sortValue(vector<pair<string, int>> &table, int lowIndex, int highIndex)
{
    if (lowIndex < highIndex)
    {
        int midpoint = (lowIndex + highIndex) / 2;
        sortValue(table, lowIndex, midpoint);
        sortValue(table, midpoint + 1, highIndex);
        mergeValue(table, lowIndex, midpoint, highIndex);
    }
}

//--------------------------------------------------------------------------------------
//                                      insertIntoVector()
//--------------------------------------------------------------------------------------
// Given: vector of nodes
// Returns: vector of pairs of strings and ints
// Inserts all nodes into vector of pairs to be used for sorting
//--------------------------------------------------------------------------------------
vector<pair<string, int>> hashtable::insertIntoVector(vector<node *> table)
{
    vector<pair<string, int>> data;
    //Travel the Hashmap
    for (int i = 0; i < int(table.size()); i++)
    {
        if (table[i]->key.length() > 0)
        {
            node *traveler = table[i];
            //Put all couples into new vector of pairs
            if (table[i]->next == NULL)
            {

                data.push_back(make_pair(table[i]->key, table[i]->value));
            }
            else
            {
                while (traveler != NULL)
                {
                    data.push_back(make_pair(traveler->key, traveler->value));
                    traveler = traveler->next;
                }
            }
        }
    }

    //Set duplicates to null values
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = i + 1; j < data.size(); j++)
        {
            if (data[i].second > 0)
            {
                if (data[i].first == data[j].first)
                {
                    data[i].second++;
                    data[j] = make_pair("", 0);
                }
            }
        }
    }

    //Erase duplicates
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].second == 0)
        {
            data.erase(data.begin() + i);
            i--;
        }
    }

    //Return vector
    return data;
}

//--------------------------------------------------------------------------------------
//                                      printByKey()
//--------------------------------------------------------------------------------------
// Prints data in order based on key
//--------------------------------------------------------------------------------------
void hashtable::printByKey()
{
    //Insert all entries of hash map into vector of pairs
    vector<pair<string, int>> key_values = insertIntoVector(buckets);
    //Run sortKey
    sortKeys(key_values, 0, key_values.size() - 1);
    //Iterate through new vector of pairs and output
    for (int i = 0; i < int(key_values.size()); i++)
    {
        cout << key_values[i].first << " "
             << key_values[i].second << endl;
    }
}

//--------------------------------------------------------------------------------------
//                                      printByValue()
//--------------------------------------------------------------------------------------
// Prints data in reverse order(largest  to smallest) based on value
//--------------------------------------------------------------------------------------
void hashtable::printByValue()
{
    ///Insert all entries of hash map into vector of pairs
    vector<pair<string, int>> key_values = insertIntoVector(buckets);
    //Run sortKey
    sortValue(key_values, 0, key_values.size() - 1);
    //Iterate through new vector of pairs and output
    for (int i = int(key_values.size()); i > 0; i--)
    {
        if (key_values[i].second > 0)
        {
            cout << key_values[i].second << " "
                 << key_values[i].first << endl;
        }
    }
}

//--------------------------------------------------------------------------------------
//                                      sanitizeWords()
//--------------------------------------------------------------------------------------
// Given: some string
// Returns: string
// Gets rid of any punction or non-alphabetic characters from word
//--------------------------------------------------------------------------------------
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

//--------------------------------------------------------------------------------------
//                                      main()
//--------------------------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    string word;
    //New Table
    hashtable table;
    while (cin)
    {
        string input;
        //Take in input
        getline(cin, input);
        stringstream ss(input);
        while (ss >> word)
        {
            //Isolate only word
            string goodWord = santizeWords(word);
            if (goodWord.length() != 0)
            {
                //Insert word into table
                table.insert(goodWord, 1);
            }
        }
    }

    //Printing what is in table
    table.printByKey();
    cout << endl;
    table.printByValue();
}
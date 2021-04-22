//--------------------------------------------------------------------
//				CS315-001  Assignment 2
//--------------------------------------------------------------------
// Author: Justin Hamilton
// Date: 3/16/21
// Description: Given a text, return a word frequency count
// Assistance: Class Notes
//--------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//This is the HashTable that I will develop seperately because I don't wanna break everything

//TODO: Finish INsert and Hash Functions, Test,Integrate,Profit
class node
{
public:
    friend class hashtable;
    node();
    node(string key, int value);

private:
    string key;
    int value;
    node *next;
};

node::node(string key, int value)
{
    key = key;
    value = value;
    next = NULL;
}

class hashtable
{
public:
    hashtable(/* args */);
    // Insert Method based on key, Seperate Chaining using basic Linked List
    void insert(string key, int value);
    // Hashing function
    int hashFunction(string input);
    // Merge Sort based on Key
    void sortKeys(vector<pair<string, int>> table, int lowIndex, int highIndex);
    //Helper Function for sortValue
    void mergeKeys(vector<pair<string, int>> table);
    //Sort Based on Value
    void sortValue(vector<pair<string, int>> table, int lowIndex, int highIndex);
    //Helper Function for sortValue
    void mergeValue(vector<pair<string, int>> table);
    //Print based on Value(May just need to start at end and rhen just ouput second)
    void printByValue();
    // Print based on Key
    void printByKey();
    vector<pair<string, int>> insertIntoVector(vector<node *> table);

private:
    vector<node *> buckets;
};

hashtable::hashtable(/* args */)
{
}

void hashtable::insert(string key, int value)
{
    //Calcuate Key with Hash FUnction
    int hash_key = hashFunction(key);
    //Figure out where Key points to in table
    node *element = buckets[hash_key];
    node *traveler = new node(key, value);

    //Case for When Nothing Is at Hash Index

    //Case for when Something is Hash Index
    //Get to end of list
    //Insert
    //Gotta resize the list because we're over Bucket Size
}

void hashtable::mergeKeys(vector<pair<string, int>> table)
{
    //Make Temporary Vectors to hold smaller and larger
    int midpoint = table.size() / 2;
    vector<pair<string, int>> smaller;
    vector<pair<string, int>> larger;
    // Put correct poritons into each based on midpoint
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].first <= table[midpoint].first)
        {
            smaller.push_back(table[i]);
        }
        else
        {
            larger.push_back(table[i]);
        }
    }
    table.clear();
    //Concatenate both arrays into table
    table.insert(table.begin(), smaller.begin(), smaller.end());
    table.insert(table.end(), larger.begin(), larger.end());
}

//Use mergeSort to sort all keys(recursive)
void hashtable::sortKeys(vector<pair<string, int>> table, int lowIndex, int highIndex)
{
    if (table.size() < 1)
    {
        return;
    }
    int mid_point = (lowIndex + highIndex) / 2;
    sortKeys(table, lowIndex, mid_point);
    sortKeys(table, mid_point + 1, highIndex);
    mergeKeys(table);
}
//Helper Function for sortValue
void hashtable::mergeValue(vector<pair<string, int>> table)
{
    //Make Temporary Vectors to hold smaller and larger
    int midpoint = table.size() / 2;
    vector<pair<string, int>> smaller;
    vector<pair<string, int>> larger;
    // Put correct poritons into each based on midpoint
    for (int i = 0; i < table.size(); i++)
    {
        if (table[i].second <= table[midpoint].second)
        {
            smaller.push_back(table[i]);
        }
        else
        {
            larger.push_back(table[i]);
        }
    }
    table.clear();
    //Concatenate both arrays into table
    table.insert(table.begin(), smaller.begin(), smaller.end());
    table.insert(table.end(), larger.begin(), larger.end());
}

//Sort Based on Value
void hashtable::sortValue(vector<pair<string, int>> table, int lowIndex, int highIndex)
{
    if (table.size() < 1)
    {
        return;
    }
    int mid_point = (lowIndex + highIndex) / 2;
    sortValue(table, lowIndex, mid_point);
    sortValue(table, mid_point + 1, highIndex);
    mergeValue(table);
}

//Insert into Vector of Pairs from HashMap
vector<pair<string, int>> hashtable::insertIntoVector(vector<node *> table)
{
    vector<pair<string, int>> data;
    //Travel the Hashmap
    for (int i = 0; i < table.size(); i++)
    {
        node *traveler = table[i];
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
    //Put all couples into new vector of pairs
    //Return vector
    return data;
}

// Print based on Key
void hashtable::printByKey()
{
    //Insert all entries of hash map into vector of pairs
    vector<pair<string, int>> key_values = insertIntoVector(buckets);
    //Run sortKey
    sortKeys(key_values, 0, key_values.size() - 1);
    //Iterate through new vector of pairs and output
    for (int i = 0; i < key_values.size(); i++)
    {
        cout << key_values[i].first << "\t" << key_values[i].second << endl;
    }
}

//Print based on Value
void hashtable::printByValue()
{
    ///Insert all entries of hash map into vector of pairs
    vector<pair<string, int>> key_values = insertIntoVector(buckets);
    //Run sortKey
    sortValue(key_values, 0, key_values.size() - 1);
    //Iterate through new vector of pairs and output
    for (int i = 0; i < key_values.size(); i++)
    {
        cout << key_values[i].second << "\t" << key_values[i].first << endl;
    }
}

//Driver Code to Test
int main(int argc, char const *argv[])
{
    hashtable table1;
    table1.insert("a", 1);
    table1.insert("b", 2);
    table1.insert("c", 3);
    table1.insert("d", 4);
    table1.insert("e", 5);

    table1.printByKey();
    table1.printByValue();

    return 0;
}

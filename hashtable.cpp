//--------------------------------------------------------------------
//				CS315-001  Assignment 2
//--------------------------------------------------------------------
// Author: Justin Hamilton
// Date: 3/16/21
// Description: Given a text, return a word frequency count
// Assistance: We'll See
//--------------------------------------------------------------------
#include <iostream>
#include <string>
using namespace std;
//This is the HashTable that I will develop seperately because I don't wanna break everything

class node
{

public:
    friend class hashtable;
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
    // Sort based on Key
    void sortByKey(/* args */);
    //Print based on Value(May just need to start at end and rhen just ouput second)
    void printByValue();
    // Print based on Key
    void printByKey();

private:
    vector<node *> table;
};

hashtable::hashtable(/* args */)
{
}

// 3 Possible Cases
// Found Somethnig at HashValue and need to Traverse Bucket
// Nothing at HashValue and new hashnode needs to be created
// Put something in
void hashtable::insert(string key, int value)
{
    //Calcuate Key with Hash FUnction
    int hash_key = hashFunction(key);
    //Figure out where Key points to in table
    node *input = table[hash_key];
    node *traveler;

    while (input != NULL && input->next != NULL)
    {
        //If there is an input at hashvalue then travel through its bucket
    }
    //If Input at hashvalue is empty then check to see if traveler has anything and if so then put it at the end of that
    // Else Just put it at beginning
}

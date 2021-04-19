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
    void sortKey(/* args */);
    //Helper Function for sortValue
    void mergeKey(/* agrs */);
    //Sort Based on Value
    void sortValue(/*args */);
    //Helper Function for sortValue
    void mergeValue(/* args */);
    //Print based on Value(May just need to start at end and rhen just ouput second)
    void printByValue();
    // Print based on Key
    void printByKey();

private:
    vector<node> *table;
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
    node *input = &table[hash_key];
    node *traveler;

    while (input != NULL && input->next != NULL)
    {
        //If there is an input at hashvalue then travel through its bucket
    }
    //If Input at hashvalue is empty then check to see if traveler has anything and if so then put it at the end of that
    // Else Just put it at beginning
}

void mergeBuckets(vector<node> table)
{
    //Make Temporary Vectors to hold smaller and larger
    // Put correct poritons into each based on midpoint
    // Walk through each vector concurrently
    // Compare each element and if right is smaller then put into array else put the other in the array
}

//Use mergeSort to sort all keys(recursive)
void sortBuckets(vector<node> table, int lowIndex, int highIndex)
{
    if (table.size() < 1)
    {
        return;
    }
    int mid_point = (lowIndex + highIndex) / 2;
    sortBuckets(table, lowIndex, mid_point);
    sortBuckets(table, mid_point + 1, highIndex);
    mergeBuckets(table);
}
//Helper Function for sortValue
void mergeValue(/* args */)
{
}

//Sort Based on Value
void sortValue(vector<node> table, int lowIndex, int highIndex)
{
    if (table.size() < 1)
    {
        return;
    }
    int mid_point = (lowIndex + highIndex) / 2;
    sortBuckets(table, lowIndex, mid_point);
    sortBuckets(table, mid_point + 1, highIndex);
    mergeBuckets(table);
}

// Print based on Key
void printByKey()
{
}

//Print based on Value(May need to start at end and just ouput second)
void printByValue()
{
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

    table1.sortBuckets(table1->, table1);

    return 0;
}

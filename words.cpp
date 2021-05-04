//--------------------------------------------------------------------
//				CS315-001  Assignment 2
//--------------------------------------------------------------------
// Author: Justin Hamilton
// Date: 5/4/21
// Description: Given a text, return a word frequency count
// Assistance: We'll See
//--------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
//This is the HashTable that I will develop seperately because I don't wanna break everything

const int BUCKET_SIZE = 10;

class node
{
public:
    friend class hashtable;
    node();
    node(string k, int v);
    string getKey();
    int getValue();

private:
    string key;
    int value;
    node *next;
};

string node::getKey()
{
    return key;
}

int node::getValue()
{
    return value;
}

node::node(string k, int v)
{
    key = k;
    value = v;
    next = NULL;
}

node::node()
{
    key = "";
    value = 0;
    next = NULL;
}

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
    bool contains(string key);
    node *getEntryAtBucket(string key);

private:
    vector<node *> buckets;
};

hashtable::hashtable()
{
    for (int i = 0; i < BUCKET_SIZE; i++)
    {
        buckets.push_back(new node());
    }
}

int hashtable::hashFunction(string s)
{
    int hash_index = 0;
    if (s.length() > 0)
    {
        for (int i = 0; i < int(s.length()); i++)
        {
            hash_index += int(char(s[i]));
        }
        //cout << "Hash Index inside of Hash Loop: " << hash_index << endl;
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

void hashtable::insert(string key, int value)
{
    //Calcuate Key with Hash FUnction
    int hash_key = hashFunction(key);
    //Figure out where Key points to in table
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
            if (temp->key == traveler->key)
            {
                traveler->value = temp->value + 1;
                temp = traveler;
                break;
            }
            temp = temp->next;
        }
    }
}

void hashtable::mergeKeys(vector<pair<string, int>> &table, int lowIndex, int mid_point, int highIndex)
{
    int low = 0;
    int high = 0;
    int both = lowIndex;
    vector<pair<string, int>> smaller(mid_point - lowIndex + 1);
    vector<pair<string, int>> larger(highIndex - mid_point);

    for (int i = 0; i < (mid_point - lowIndex + 1); i++)
    {
        smaller[i] = table[lowIndex + i];
    }
    for (int j = 0; j < (highIndex - mid_point); j++)
    {
        larger[j] = table[mid_point + 1 + j];
    }

    while (low < (mid_point - lowIndex + 1) && high < (highIndex - mid_point))
    {
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

//Use mergeSort to sort all keys(recursive)
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

//Helper Function for sortValue
void hashtable::mergeValue(vector<pair<string, int>> &table, int lowIndex, int mid_point, int highIndex)
{
    int low = 0;
    int high = 0;
    int both = lowIndex;
    vector<pair<string, int>> smaller(mid_point - lowIndex + 1);
    vector<pair<string, int>> larger(highIndex - mid_point);

    for (int i = 0; i < (mid_point - lowIndex + 1); i++)
    {
        smaller[i] = table[lowIndex + i];
    }
    for (int j = 0; j < (highIndex - mid_point); j++)
    {
        larger[j] = table[mid_point + 1 + j];
    }

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

//Sort Based on Value
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

//Insert into Vector of Pairs from HashMap
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
    for (int i = 0; i < int(key_values.size()); i++)
    {
        cout << "First Value: " << key_values[i].first << "\t"
             << "Second Value: " << key_values[i].second << endl;
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
    for (int i = 0; i < int(key_values.size()); i++)
    {
        cout << "First Value: " << key_values[i].second << "\t"
             << "Second Value: " << key_values[i].first << endl;
    }
}
/* bool hashtable::contains(string key)
{
    int hash_key = hashFunction(key);
    node *element = buckets[hash_key];

    node *temp = element;
    while (temp->next != NULL)
    {
        if (temp->getKey() == key)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

node *hashtable::getEntryAtBucket(string key)
{
    int hash_key = hashFunction(key);
    node *element = buckets[hash_key];

    node *temp = element;
    while (temp->next != NULL)
    {
        if (temp->getKey() == key)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
} */

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

int main(int argc, char const *argv[])
{
    ifstream file("data.txt");
    string word;

    hashtable table;

    while (file >> word)
    {
        string goodWord = santizeWords(word);
        if (goodWord.length() != 0)
        {
            table.insert(goodWord, 1);
        }
    }

    file.close();

    table.printByKey();
    cout << endl;
    table.printByValue();
}
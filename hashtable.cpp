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

//TODO: Figuire out seg fualts in sort, integrate, profit
const int BUCKET_SIZE = 10;

class node
{
public:
    friend class hashtable;
    node();
    node(string k, int v);

private:
    string key;
    int value;
    node *next;
};

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
    void mergeKeys(vector<pair<string, int>> &table, int lowIndex, int highIndex);
    //Sort Based on Value
    void sortValue(vector<pair<string, int>> &table, int lowIndex, int highIndex);
    //Helper Function for sortValue
    void mergeValue(vector<pair<string, int>> &table);
    //Print based on Value&
    void printByValue();
    // Print based on Key
    void printByKey();

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
    //cout << "I've made the hash_key: " << hash_key << endl;
    //Figure out where Key points to in table
    node *element = buckets[hash_key];
    node *traveler = new node(key, value);
    //cout << traveler->key << " " << traveler->value << endl;

    //cout << "Right before actual insert" << endl;
    //Case for When Nothing Is at Hash Index
    if (element->key.empty())
    {
        //cout << "There isnt anything here" << endl;
        buckets[hash_key] = traveler;
    }
    //Case for when Something is Hash Index
    else
    {
        //cout << "Ope" << endl;
        node *temp = element;
        //Get to end of list
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        //Insert
        temp->next = traveler;
    }
}

void hashtable::mergeKeys(vector<pair<string, int>> &table, int lowIndex, int highIndex)
{
    cout << "This is lowIndex: " << lowIndex << endl;
    cout << "This is highIndex: " << highIndex << endl;
    int midpoint = (lowIndex + highIndex) / 2;
    cout << "this is the midpoint " << midpoint << endl;
    int low = 0;
    int high = 0;
    int both = 0;
    vector<pair<string, int>> smaller;
    vector<pair<string, int>> larger;

    cout << "No seg fault yet" << endl;
    for (int i = 0; i <= midpoint; i++)
    {
        cout << "Heres table[i]: " << table[i].first << table[i].second << endl;
        smaller.push_back(table[i]);
    }
    for (int i = midpoint + 1; i <= highIndex; i++)
    {
        cout << "Heres table[i]: " << table[i].first << table[i].second << endl;
        larger.push_back(table[i]);
    }

    for (auto i : smaller)
    {
        cout << "Here's smaller " << i.first << " " << i.second << endl;
    }
    for (auto i : larger)
    {
        cout << "Here's larger " << i.first << " " << i.second << endl;
    }

    cout << "Just got done merging everything" << endl;
    while (low <= midpoint && high <= highIndex)
    {
        cout << "I have entered the loop" << endl;
        if (smaller[low].first <= larger[high].first)
        {
            cout << "I have entered the low loop" << endl;
            table[both] = smaller[low];
            low++;
        }
        else
        {
            cout << "I have entered the high loop" << endl;
            table[both] = larger[high];
            high++;
        }
        both++;
    }
    cout << "Just got done putting things inside other things" << endl;

    cout << "This is low: " << low << endl;
    cout << "This is high: " << high << endl;
    for (int i = low; i <= midpoint; i++)
    {
        cout << i << endl;
        table[both] = smaller[i];
        both++;
    }

    for (int i = high; i <= highIndex; i++)
    {
        table[both] = larger[i];
        both++;
    }
    cout << "Dude why" << endl;
}

//Use mergeSort to sort all keys(recursive)
void hashtable::sortKeys(vector<pair<string, int>> &table, int lowIndex, int highIndex)
{
    if (lowIndex < highIndex)
    {
        cout << highIndex << " " << lowIndex << endl;
        int midpoint = (lowIndex + highIndex) / 2;
        cout << "This is the midpoint from sort function: " << midpoint << endl;
        sortKeys(table, lowIndex, midpoint);
        sortKeys(table, midpoint + 1, highIndex);
        mergeKeys(table, lowIndex, highIndex);
    }
}

//Helper Function for sortValue
void hashtable::mergeValue(vector<pair<string, int>> &table)
{
    //Make Temporary Vectors to hold smaller and larger
    int midpoint = table.size() / 2;
    vector<pair<string, int>> smaller;
    vector<pair<string, int>> larger;
    // Put correct poritons into each based on midpoint
    for (int i = 0; i <= midpoint; i++)
    {
        smaller.push_back(table[i]);
    }
    for (int i = midpoint + 1; i < table.size(); i++)
    {
        larger.push_back(table[i]);
    }
    int iter1 = 0, iter2 = 0, iter3 = 0;
    //Concatenate both arrays into table
    while (iter1 < smaller.size() && iter2 < larger.size())
    {
        if (smaller[iter1].second <= larger[iter2].second)
        {
            table[iter3] = smaller[iter1];
            iter1++;
        }
        else
        {
            table[iter3] = larger[iter2];
            iter2++;
        }
        iter3++;
    }
}

//Sort Based on Value
void hashtable::sortValue(vector<pair<string, int>> &table, int lowIndex, int highIndex)
{
    if (lowIndex >= highIndex)
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
    for (int i = 0; i < int(table.size()); i++)
    {
        if (table[i]->key.length() > 0)
        {
            node *traveler = table[i];
            //cout << table[i]->key << " " << table[i]->value << endl;
            //Put all couples into new vector of pairs
            if (table[i]->next == NULL)
            {
                //cout << " I am in main loop" << endl;
                data.push_back(make_pair(table[i]->key, table[i]->value));
            }
            else
            {
                //cout << "I gotta travel" << endl;
                while (traveler != NULL)
                {
                    //cout << traveler->key << " " << traveler->value << " ";
                    data.push_back(make_pair(traveler->key, traveler->value));
                    traveler = traveler->next;
                }
            }
        }
    }

    for (auto i : data)
    {
        cout << i.first << " " << i.second << endl;
    }
    //Return vector
    return data;
}

// Print based on Key
void hashtable::printByKey()
{
    //Insert all entries of hash map into vector of pairs
    vector<pair<string, int>> key_values = insertIntoVector(buckets);
    cout << "I've inserted all the key/value pairs into a vector" << endl;
    //Run sortKey
    cout << "Heres the size: " << key_values.size() - 1 << endl;
    sortKeys(key_values, 0, key_values.size() - 1);
    cout << "I've sorted all the pairs" << endl;
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
    cout << "My Guy please" << endl;
    for (int i = 0; i < int(key_values.size()); i++)
    {
        cout << "First Value: " << key_values[i].second << "\t"
             << "Second Value: " << key_values[i].first << endl;
    }
}

//Driver Code to Test
int main(int argc, char const *argv[])
{
    hashtable table1;
    cout << "I have made table 1" << endl;

    table1.insert("b", 1);
    table1.insert("c", 2);
    table1.insert("a", 3);
    table1.insert("f", 4);
    table1.insert("e", 5);
    table1.insert("o", 6);
    table1.insert("i", 7);
    table1.insert("l", 8);
    table1.insert("k", 9);
    table1.insert("j", 10);
    cout << "I have inserted everything" << endl;

    table1.printByKey();
    cout << "Finished printing the Keys" << endl
         << endl;
    //table1.printByValue();
    cout << "I've printed everthing" << endl;

    return 0;
}

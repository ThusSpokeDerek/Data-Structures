//
//  main.cpp
//
//  COSC 160 Fall 2016
//  Assignment 3
//
//  Due on: DEC 09, 2016
//  Author: Derek Acosta
//
//  Created by Derek Acosta on 12/4/16.
//  Copyright © 2016 Derek Acosta. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <ctype.h>
#include <cmath>

using std::cout;
using std::endl;
using std::string;

int total_num_of_collisions = 0;

struct node
{
    string text;
    unsigned long long data;
    node *next;
    node(string, unsigned long long, node*);
};

class HashTable
{
private:
    
    int capacity;
    node **table;
    
public:
    
    // Array length is set to 13 by default.
    HashTable( int tableSize = 13 );
    ~HashTable();

    //member function push results in a node<T> object being added
    //to the beginning of the linked list requires dynamic allocation of memory
    void insert(string val );
    
    void deleteAll();
    
    bool find(string val);
    
    unsigned long long hash_string(string val);
    
    // Returns an array location for a given item key.
    int hash( unsigned long long val );
};

node::node(string text, unsigned long long data, node *next)
{
    this->text = text;
    this->data = data;
    this->next = NULL;
}

HashTable::HashTable(int tableSize)
{
    capacity = tableSize;
    if(capacity <= 0) capacity = 13;
    
    table = new node*[capacity];
    for (int i = 0; i < capacity; i++)
        table[i] = NULL;
    
}//END of constructor

HashTable::~HashTable(){
    deleteAll();
}//END of destructor

void HashTable::insert(string val)
{
    unsigned long long convert_int = hash_string(val);
    unsigned long long index = hash(convert_int);
    
    
    if(table[index] == NULL)
        table[index] = new node(val, convert_int, NULL);
    else
    {
        total_num_of_collisions++;
        node *newNode = table[index];
        while(newNode->next != NULL)
            newNode = newNode->next;
        newNode->next = new node(val, convert_int, NULL);
    }
}

bool HashTable::find(string val)
{
    unsigned long long convert_int = hash_string(val);
    unsigned long long index = hash(convert_int);

    node *ptr = table[index];
    
    while(ptr != NULL)
    {
        if(convert_int == ptr->data)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Returns an array location for a given item key.
int HashTable::hash( unsigned long long val )
{
    return val % capacity;
}

unsigned long long HashTable::hash_string(string val)
{
    unsigned long long int convert_int = 0;
    for(long i = val.size()-1; i >= 0; i--)
    {
        convert_int += val[i]*pow(19, i);//found 19 reducing collision significantly compared to 37
    }
    return convert_int;
}

void HashTable::deleteAll()
{
    long long int i = 0;
    while(table[i] != NULL)
    {
        node *ptr = table[i];
        while(ptr != NULL)
        {
            node *temp = table[i];
            ptr = ptr->next;
            temp->next = NULL;
            delete temp;
            temp = NULL;
        }
        i++;
    }
    delete table;
}

#endif /* HashTable_h */

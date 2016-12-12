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

#include "HashTable.h"

using namespace std;

const double TABLESIZE = 200029;

//Prototype
void load(string argv1, string argv2, HashTable &HashTable);

int main(int argc, const char* argv[])
{
    try
    {
        if(argc < 3)
        {
            string error = "Please pass both a dictionary file and a textfile to spell check as arguments into the command line\n";
            throw error;
        }
        
        HashTable *dictTable = new HashTable(TABLESIZE);
        load(argv[1], argv[2], *dictTable);
    }
    catch(string a)
    {
        cout << a;
    }
    catch(...)
    {
        cout << "This should not happen\n";
    }
    
    return 0;
}

void load(string argv1, string argv2, HashTable &HashTable)
{
    try
    {
        string file_name1 = argv1;
        ifstream file(file_name1.c_str());
        
        string file_name2 = argv2;
        ifstream file2(file_name2.c_str());
        ofstream outfile("Using_separate_chaining.txt", fstream::out);
        
        if(!file && !file2 && !outfile)
        {
            cout << "Check to ensure the file" << endl;
        }
        else
        {
            string dict_word;
            double total_num_dict_words;
            while(getline(file, dict_word))
            {
                string mod_dict = dict_word.substr(0, dict_word.find("/", 0));
                mod_dict = mod_dict.substr(0, mod_dict.find("'", 0));
                mod_dict = mod_dict.substr(0, mod_dict.find("\"", 0));
                mod_dict = mod_dict.substr(0, mod_dict.find("-", 0));
                mod_dict = mod_dict.substr(0, mod_dict.find(".", 0));
                mod_dict = mod_dict.substr(0, mod_dict.find(",", 0));
                mod_dict = mod_dict.substr(0, mod_dict.find(":", 0));
                mod_dict = mod_dict.substr(0, mod_dict.find("!", 0));
                mod_dict = mod_dict.substr(0, mod_dict.find("(", 0));
                mod_dict = mod_dict.substr(0, mod_dict.find(")", 0));


                transform(mod_dict.begin(), mod_dict.end(),
                          mod_dict.begin(), (int (*)(int))tolower);//make shape_choice lowercase
                
                HashTable.insert(mod_dict);
                total_num_dict_words++;
            }
            string doc_line, doc_word;
            long long int line_num, total_word_count, total_misspelled;
            while(getline(file2, doc_line))
            {
                line_num++;
                istringstream line(doc_line);
                while(line >> doc_word)
                {
                    total_word_count++;
                    string mod_doc = doc_word.substr(0, doc_word.find("/", 0));
                    mod_doc = mod_doc.substr(0, mod_doc.find("'", 0));
                    mod_doc = mod_doc.substr(0, mod_doc.find("\"", 0));
                    mod_doc = mod_doc.substr(0, mod_doc.find("-", 0));
                    mod_doc = mod_doc.substr(0, mod_doc.find(".", 0));
                    mod_doc = mod_doc.substr(0, mod_doc.find(",", 0));
                    mod_doc = mod_doc.substr(0, mod_doc.find(":", 0));
                    mod_doc = mod_doc.substr(0, mod_doc.find("!", 0));
                    mod_doc = mod_doc.substr(0, mod_doc.find("(", 0));
                    mod_doc = mod_doc.substr(0, mod_doc.find(")", 0));
                    
                    transform(mod_doc.begin(), mod_doc.end(),
                              mod_doc.begin(), (int (*)(int))tolower);//make shape_choice lowercase
                    
                    if(HashTable.find(mod_doc) == false)
                    {
                        total_misspelled++;
                        cout << "(" << total_misspelled << ") " << mod_doc << " is not found!" << " : on line " << line_num << endl;
                        outfile << "(" << total_misspelled << ") " << mod_doc << " is not found!" << " : on line " << line_num << endl;
                    }
                }
            }
            cout << endl << "Total words checked: " << total_word_count << endl;
            cout << "Total number of misspelled words: " << total_misspelled << endl;
            cout << "Total number of collisions in creating hash table: " << total_num_of_collisions << endl;
            cout << "Total number of unsuccessful probes (word not found in hash table): "
                << total_misspelled << endl;
            cout << "Total number of successful probes (word found in dictionary, note count each access/probe): "
                << total_word_count - total_misspelled << endl;
            cout << "Load factor (lamda) of the table: " << double(total_num_dict_words/TABLESIZE) <<  endl;
            cout << "Size of hash table: " << TABLESIZE << endl;
            
            outfile << endl << "Total words checked: " << total_word_count << endl;
            outfile << "Total number of misspelled words: " << total_misspelled << endl;
            outfile << "Total number of collisions in creating hash table: " << total_num_of_collisions << endl;
            outfile << "Total number of unsuccessful probes (word not found in hash table): "
            << total_misspelled << endl;
            outfile << "Total number of successful probes (word found in dictionary, note count each access/probe): "
            << total_word_count - total_misspelled << endl;
            outfile << "Load factor (lamda) of the table: " << double(total_num_dict_words/TABLESIZE) <<  endl;
            outfile << "Size of hash table: " << TABLESIZE << endl;
            
            file.close();
            file2.close();
            outfile.close();
        }
    }
    catch(string e)//didnt enter file in command file give warning.
    {
        throw e;
    }
}//END loadData

//
//  main.cpp
//
//  COSC 160 Fall 2016
//  Assignment 3
//
//  Due on: NOV 17, 2016
//  Author: Derek Acosta
//
//  Created by Derek Acosta on 11/13/16.
//  Copyright © 2016 Derek Acosta. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <string.h>
#include <sstream>
#include "BT.h"
#include <ctype.h>

using namespace std;

//Prototype
void load(string argv);

int main(int argc, const char* argv[])
{
    try
    {
        load(argv[1]);
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

void load(string argv)
{
    try
    {
        if(!argv[1]){
            string error = "Please enter the file name on the command line\n";
            throw error;
        }
        
        string file_name = argv;
        
        ifstream command_file(file_name.c_str());
        
        if(!command_file)
        {
            cout << "Check to ensure the file" << endl;
        }
        else
        {
            string all;
            char command, colon;
            string data;
            
            BTree<int> iTree(7);//instantiation change order as needed; I find order 7 works perfectly
            BTree<string> sTree(7);//to ensure it can handle all data types
            
            while(getline(command_file, all))
            {
                istringstream line(all);
                line >> command >> colon >> data;
                
                if(command == 'L')
                {
                    string path = argv;
                    while(path.back() != '/') path.pop_back();
                    ifstream data_file(path + data);
                    
                    if(!data_file)
                    {
                        string error = "Please provide a list a file\n";
                        throw error;
                    }
                    else
                    {
                        string values;
                        while(data_file >> values)
                        {
                            if(isdigit(values[0]) || isdigit(values[1]))
                            {
                                stringstream ss(values);
                                int node;
                                ss >> node;
                                iTree.insert(node);
                            }
                            else
                            {
                                sTree.insert(values);
                            }
                        }
                        data_file.close();
                    }
                }
                else if(command == 'A')//adds the key to BTree
                {
                    if(isdigit(data[0]))
                        iTree.insert(stoi(data));
                    else
                        sTree.insert(data);
                    cout << "Object " << data << " was added\n";
                }
                else if(command == 'D')//removes key from BTree
                {
                    if(isdigit(data[0]))
                        iTree.Delete(stoi(data));
                    else
                        sTree.Delete(data);
                }
                else if(command == 'S')//find/search for key in	BTree
                {
                    if(isdigit(data[0]))
                    {
                        if(iTree.search(stoi(data)))
                            cout << "True: " << "Object " << data << " was found\n\n";
                        else
                            cout << "False: Object " << data << " was not found\n\n";
                    }
                    else
                    {
                        if(sTree.search(data))
                            cout << "True: " << "Object " << data << " was found\n\n";
                        else
                            cout << "False: Object " << data << " was not found\n\n";
                    }
                }
                else if(command == 'P')//prints	BTree in level order
                {
                    iTree.print();
                    sTree.print();
                    cout << endl << endl;
                }
                else if(command == 'T')//Terminate program
                {
                    cout << "Program has terminated\n\n";
                    return;
                }
                
            }
        }
    }
    catch(string e)//didnt enter file in command file give warning.
    {
        throw e;
    }
}//END loadData

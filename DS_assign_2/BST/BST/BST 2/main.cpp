//
//  main.cpp
//
//  COSC 160 Fall 2016
//  Assignment 2
//
//  Due on: OCT 21, 2016
//  Author: Derek Acosta
//
//  Created by Derek Acosta on 10/18/16.
//  Copyright © 2016 Derek Acosta. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include "BST.h"
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
        
        ifstream file(file_name.c_str());
        
        if(!file)
        {
            cout << "Check to ensure the file" << endl;
        }
        else
        {
            BinaryTree<string> sTree;
            BinaryTree<int> iTree;
            string input;
            while(file >> input)
            {
                if(isdigit(input[0]))
                {
                    stringstream ss(input);
                    int node;
                    ss >> node;
                    iTree.insert(node);
                }
                else
                {
                    sTree.insert(input);
                }
            }
            iTree.printInorderTraversal();
            sTree.printInorderTraversal();
            file.close();
        }
    }
    catch(string e)//didnt enter file in command file give warning.
    {
        throw e;
    }
}//END loadData

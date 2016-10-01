//
//  main.cpp
//
//  COSC 160 Fall 2016
//  Assignment 2
//
//  Due on: SEPT 27, 2016
//  Author: Derek Acosta
//
//  Created by Derek Acosta on 9/17/16.
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
#include "LL.h"
#include "Stack.h"

using namespace std;

//Prototype
void upload(string argv, Stack &Stack );

int main(int argc, const char * argv[])
{
    try
    {
        Stack *polyStack = new Stack();
        upload(argv[1], *polyStack);
        polyStack->Display();
        
    }//END try block
    catch(...)
    {
        cout << "This should happen\n";
    }
    
    return 0;
}

void upload(string argv, Stack &Stack)
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
            string polynominal, base, exponent;
            /****************************************************************************
             *                    Loop through file                                     *
             ****************************************************************************/
            while(getline(file,polynominal))
            {
                istringstream line(polynominal);
                
                if(polynominal == "+")
                {
                    Element *poly1 = Stack.getTop();
                    Element *poly2 = Stack.getTop()->previous;
                    Polynomial *poly = new Polynomial();
                    *poly = *poly1->data + *poly2->data;
                    Stack.Pop();
                    Stack.Pop();
                    Stack.Push(poly);
                }
                else if(polynominal == "-")
                {
                    Element *poly1 = Stack.getTop();
                    Element *poly2 = Stack.getTop()->previous;
                    Polynomial *poly = new Polynomial();
                    *poly = *poly1->data - *poly2->data;
                    Stack.Pop();
                    Stack.Pop();
                    Stack.Push(poly);
                }
                else if(polynominal == "*")
                {
                    Element *poly1 = Stack.getTop();
                    Element *poly2 = Stack.getTop()->previous;
                    Polynomial *poly = new Polynomial();
                    *poly = *poly1->data * *poly2->data;
                    Stack.Pop();
                    Stack.Pop();
                    Stack.Push(poly);
                }
                else
                {
                    Polynomial* poly = new Polynomial();
                    while(line >> base >> exponent)
                    {
                        stringstream ss(base);
                        stringstream ss2(exponent);
                        
                        int base2,exponent2;
                        ss >> base2;
                        ss2 >> exponent2;
                        
                        Node *newterm = new Node(base2, exponent2, NULL);
                        if(newterm->base !=0)
                        {
                            poly->sort(newterm);
                        }
                    }
                    
                    Stack.Push(poly);
                }
            }

            file.close();
        }
        
    }
    catch(string e)//didnt enter file in command file give warning.
    {
        cout << e;
    }


    cout << "Exiting function loadData\n";
}//END loadData

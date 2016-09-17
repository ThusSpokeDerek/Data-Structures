//
//  main.cpp
//
//  COSC 160 Fall 2016
//  Assignment 1
//
//  Due on: SEPT 27, 2016
//  Author: Derek Acosta
//
//  Created by Derek Acosta on 9/17/16.
//  Copyright © 2016 Derek Acosta. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <string.h>
//#include "LL.h"

using namespace std;

int main(int argc, const char * argv[])
{
    try
    {
        if(argv[1] == NULL){
            string error = "Please enter the file name on the command line\n";
            throw error;
        }
        
        string file_name = argv[1];
        
        ifstream file(file_name.c_str());
        
        if(!file)
        {
            cout << "Check to ensure the file" << endl;
        }
        else
        {
            //a will store first operand, b second operand, c operator, d will be used for demarcating a and b
            string a,b,c,d;
            
            /****************************************************************************
             *                    Loop through file                                     *
             ****************************************************************************/
            while(file >> a >> b >> c)
            {
            }
            file.close();
        }
        
        
    }//END try block
    catch(string e)//didnt enter file in command file give warning.
    {
        cout << e;
    }
    catch(...)
    {
        cout << "This should happen\n";
    }
    
    return 0;
    
}

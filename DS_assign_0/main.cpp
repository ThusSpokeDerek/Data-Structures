//
//  main.cpp
//
//  COSC 160 Fall 2016
//  Assignment 0
//
//  Due on: SEPT 7, 2016
//  Author: Derek Acosta
//
//  Created by Derek Acosta on 8/31/16.
//  Copyright © 2016 Derek Acosta. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <string.h>

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
                //printing out general format
                if(a.size() > b.size())
                {
                    cout << setw(a.size()) << a << endl;
                    cout << setw(a.size()) << b << endl;
                    cout << c << endl;
                    for(int i = 0; i < a.size(); i++){
                        cout << "-";
                    }
                    cout << endl;
                }
                else
                {
                    cout << setw(b.size()) << a << endl;
                    cout << setw(b.size()) << b << endl;
                    cout << c << endl;
                    for(int i = 0; i < b.size(); i++){
                        cout << "-";
                    }
                    cout << endl;
                }
                
                if(a == b && c =="-")
                {
                    cout << 0 << endl;
                    break;
                }
                
                vector<char> operand1, operate, operand2, solution;
                vector<int> ninesComp;
                if(a[0] == '+')//treat as unsigned int
                {
                    a.erase(a.begin());
                }
                else if(a[0] == '-' && (b[0] != '-') && c == "+")//required for adding a positive operand(b) to a negative operand(a). When computed will be treated as subtraction.
                {
                    c = "-";
                    d = "+";
                    a.erase(a.begin());
                }
                else if(a[0] == '-' && (b[0] != '-') && c == "-")//required for subtracting a positive operand(b) to a negative operand(a). When computed will be treated as addition.
                {
                    c = "+";
                    d = "-";
                    a.erase(a.begin());
                }
                
                if(b[0] == '+')//treat as unsigned int
                {
                    b.erase(b.begin());
                }
                else if(b[0] == '-' && (a[0] != '-') && c == "+")//required for adding a positive operand(a) to a negative operand(b). When computed will be treated as subtraction.
                {
                    c = "-";
                    b.erase(b.begin());
                }
                else if(b[0] == '-' && (a[0] != '-') && c == "-")//required for subtracting a positive operand(a) to a negative operand(b). When computed will be treated as addition.
                {
                    c = "+";
                    b.erase(b.begin());
                }
                
                if(a[0] == '-' && (b[0] == '-') && c == "+")//required for adding two negative operands. Treated as positive and will add negative sign post calculation.
                {
                    d = "demarker";
                    a.erase(a.begin());
                    b.erase(b.begin());
                }
                else if(a[0] == '-' && (b[0] == '-') && c == "-") //treat as case 1 in that it will subtract and later add in a negative sign
                {
                    d = "+";
                    a.erase(a.begin());
                    b.erase(b.begin());
                }
                
                for(int i = 0; i < a.size(); i++)//pushing string elements into vector by based on string sign. Will simplify issues of carrying over later
                {
                    if(a.size() >= b.size())
                    {
                        operand1.push_back(a[i]);
                    }
                    else
                    {
                        operand2.push_back(a[i]);
                    }
                }
                for(int i = 0; i < b.size(); i++)//pushing string elements into vector by based on string sign. Will simplify issues of carrying over later
                {
                    if(a.size() >= b.size())
                    {
                        operand2.push_back(b[i]);
                    }
                    else
                    {
                        operand1.push_back(b[i]);
                    }
                }
                
                /****************************************************************************
                 *                    computations                                          *
                 ****************************************************************************/
                if(c == "+")//adds the two vectors
                {
                    int carryOver= 0;//initialized carrying number to zero
                    int operand2Conversion = 0;
                    for(int i = operand1.size()-1; i >= 0; --i)//operand1 will either be string a or b based on whose size is larger
                    {
                        int operand1Conversion = operand1.back() - '0';//used to char to int for analysis
                        if(operand2.size() != 0)
                        {
                            operand2Conversion = operand2.back() - '0';
                            if(operand2Conversion < 0 || operand2Conversion >= 10)//for issues involving ascii when converting
                            {
                                operand2Conversion = 0;
                            }
                        }
                        else//if 0 all other values being store passed the carryOver should necessarily be the same as string
                        {
                            operand2Conversion = 0;
                        }
                        int store = operand1Conversion + operand2Conversion + carryOver;//does the adding
                        if(store >=10)//determines carrying value
                        {
                            solution.push_back(to_string(store)[1]);//pushes to new vector
                            carryOver = store/10;
                            if(i == 0)//if operand is approaching last element get the first digit of the int and append to new vector
                            {
                                solution.push_back(to_string(store)[0]);
                            }
                        }
                        else//adds value with no carrying number
                        {
                            solution.push_back(to_string(store)[0]);
                            carryOver = 0;
                        }
                        operand1.pop_back();//removes last element from vector so all I have to do is check the 'back' every time for next element to process
                        if(operand2Conversion > 0 && operand2Conversion < 10){operand2.pop_back();}//had some difficulties
                    }
                    
                    if(d == "-")//post alter
                    {
                        cout << "-";
                    }
                    else if(d == "demarker")//post alter
                    {
                        cout << "-";
                    }
                    
                    for(int i = solution.size()-1; i >= 0; --i)//print solution
                    {
                        cout << solution[i];
                    }
                    cout << endl;
                }
                else if(c == "-")//subtract two vectors
                {
                    int carryOver= 0;
                    
                    for(int i = operand1.size()-1; i >= 0; i--)
                    {
                        int operand1Conversion = 9 - (operand1[i] - '0');//nines complement
                        int operand2Conversion = 0;
                        if(operand2.size() != 0)
                        {
                            operand2Conversion = operand2.back() - '0';//char to int
                            if(operand2Conversion < 0 || operand2Conversion >= 10)//for issues involving ascii when converting
                            {
                                operand2Conversion = 0;
                            }
                        }
                        else
                        {
                            operand2Conversion = 0;
                        }
                        int store = operand1Conversion + operand2Conversion + carryOver;//does the adding
                        if(store >=10)//determines carrying value
                        {
                            solution.push_back(to_string(store)[1]);//pushes to new vector
                            carryOver = store/10;
                            if(i == 0)
                            {
                                solution.push_back(to_string(store)[0]);
                            }
                        }
                        else
                        {
                            solution.push_back(to_string(store)[0]);//pushes to new vector
                            carryOver = 0;
                        }
                        operand1.pop_back();//removes last element from vector so all I have to do is check the 'back' every time for next element to process
                        if(operand2Conversion > 0 && operand2Conversion < 10){operand2.pop_back();}
                    }
                    
                    if(a.size() <= b.size() && d.empty())//checking if value requires a negative
                    {
                        cout << "-";
                    }
                    else if(a.size() >= b.size() && d == "+")//checking if value requires a negative
                    {
                        cout << "-";
                    }
                    
                    for(int i = solution.size()-1; i >= 0; --i)//prints solution
                    {
                        int mod = 9 - (solution[i] - '0');//nines complement of the prior resultant
                        cout << mod;
                    }
                    cout << endl;
                }
                else//for insurance
                {
                    cout << "This wasn't part of the assignment";
                }
                solution.clear();
                cout << endl;
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

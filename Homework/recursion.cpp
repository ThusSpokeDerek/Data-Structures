/*
 *  recursion.cpp
 *
 *  COSC 160 Fall 2016
 *  Recursion
 *
 *  Due on: SEPT 11, 2016
 *  Author: Derek Acosta
 *
 */

#include <iostream>
#include <math.h>
#include <cstdlib>
#include <cstring>
#include <iterator>
#include <algorithm>

using namespace std;

//for recursion
int gcd(int a, int b);
int Mul(int a, int b);
int find(int a, int b, int K, int S[]);

//for non-recursion version
int gcd_non(int a, int b);
int Mul_non(int a, int b);
int find_non(int a, int b, int K, int S[]);


template<class T, size_t N>
size_t size(T (&)[N]) { return N; }

int main(int argc, char const *argv[])
{
    try
    {
        int S[] = {3,4,3,36,4,7,234,234,56,3,2};
        cout << gcd(120,6) << endl;
        cout << gcd_non(6, 120) << endl;
        cout << Mul(5,3) << endl;
        cout << Mul_non(5,3) << endl;
        cout << find(0,size(S)-1,7,S) << endl;
        cout << find_non(0,size(S)-1,7,S) << endl;
    }
    catch(...)
    {
        cout << "This shouldn't happen";
    }
    return 0;
}

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                     Question 1. Recursive definition/relational        **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

gcd(a,b) = {    if(a == 0) b //base case throw b
                if(b == 0) a //base case throw a
                f(b,a%b) //otherwise do this
            }

Mul(a,b) = {    if(b == 0) 0 //base case throw 0
                a + Mul(a, b-1) // otherwise do this
            }
find(a,b,K,S) = {     if(b ==0) false //base case throw false; meaning has reached end of sequence and not found anything
                      if(K == S[a] || K == S[b] true //base case has found element in sequence now return true
                      find(a+1, b-1, K, S) //otherwise do this
                 }

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                     Question 2. Done recursively                       **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

int gcd(int a, int b)//recursively
{
    if(a == 0) return b;
    if(b == 0) return a;
    if(a == b) return b;
    else return gcd(b, a%b);
}

int Mul(int a, int b)//recursively
{
    if(b == 0) return 0;
    else return (a + Mul(a, b-1));
}

int find(int a, int b, int K, int S[])//recursively
{
    if(b == 0) return false;
    if(K == S[a] || K == S[b]) return true;
    find(a+1, b-1, K, S);
}//seems to work on other IDEs but hungs here

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                     Question 3. Done non-recursively                   **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

int gcd_non(int a, int b)//non-recursively
{
    if(a == 0) return b;
    if(b == 0) return a;
    
    while( a % b != 0 )
    {
        a = a + b;
        b = a - b;
        a = a - b;
        b = b % a;
    }
    return b;
}

int find_non(int a, int b, int K, int S[])//non-recursively
{
    const int b2 = b;
    while(a != b2 || b != 0)
    {
        if(a == b2 || b <= 0) return false;
        if(K == S[a] || K == S[b]) return true;
        else
        {
            a+=1; b-=1;
        }
    }
    return false;
}

int Mul_non(int a, int b)//non-recursively
{
    if(a == 0) return 0;
    if(b == 0) return 0;
    
    int a2 = 0;
    while(b != 0)
    {
        a2 += a;
        b -= 1;
    }
    return a2;
}






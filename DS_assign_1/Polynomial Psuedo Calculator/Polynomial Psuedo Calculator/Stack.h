//
//  Stack.h
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

#ifndef Stack_h
#define Stack_h

#include "LL.h"

using std::cout;
using std::endl;

struct Element
{
    Polynomial *data;
    Element *next;
    Element *previous;
    Element(Polynomial*, Element*, Element*);
};

class Stack: public Polynomial
{
private:
    Element* top;
    
public:
    
    Stack();
    ~Stack(); //destructor, must ensure memory is deallocated
    
    //member function push results in a Element<T> object being added
    //to the beginning of the linked list requires dynamic allocation of memory
    void Push(Polynomial*);
    
    //member function pop removes the first list object and deallocates memory
    void Pop();
    
    //member function top return reference to first object
    Polynomial Top();
    
    //member function isEmpty returns true or false if the linked list is full or empty
    bool IsEmpty();
    
    //member function Display will print out resultant
    void Display();
    
    void Clear();
    
    Element *getTop(){return top;};
    
    void setTop(Element *top){this->top = top;};

};

Element::Element(Polynomial *data, Element *previous, Element *next){
    this->data = data;
    this->previous = previous;
    this->next = next;
}

Stack::Stack(){
    top  = NULL;
}//END of constructor

Stack::~Stack(){
    Clear();
    clear();
}//END of destructor

void Stack::Push(Polynomial *val){
    
    if(top == NULL)
    {
        top = new Element(val, NULL, NULL);
    }
    else
    {
        top->next = new Element(val, top, NULL);
        top = top->next;
    }
}

void Stack::Pop(){
    
    if(top == NULL)
    {
        cout << "The stack is empty";
    }
    else if(this->top->previous == NULL)
    {
        delete this->top;
        top = NULL;
    }
    else
    {
        delete top;
        top = top->previous;
        top->next = NULL;
    }
}

Polynomial Stack::Top() {
        return *top->data;
}

void Stack::Clear(){
    while(top != NULL)
    {
        this->Pop();
    }
} //END LL::clear()


bool Stack::IsEmpty(){
    bool empty = false;
    if(top == NULL)
    {
        empty = true;
    }
    return empty;
}

void Stack::Display(){
    
    Element *display = top;
    while(display != NULL)
    {
        Node *display2 = display->data->getHead();
        while(display2 != NULL)
        {
            cout << display2->base << "x^" << display2->exponent << " ";
            display2 = display2->next;
        }
        cout << endl;
        display = display->previous;
    }
    cout << endl;
}

#endif /* Stack_h */

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

#include <algorithm>
#include "LL.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;
using std::ostream;
using std::istream;
using std::cin;
using std::istringstream;
using std::ostringstream;
using std::setw;
using std::setfill;

struct Element
{
    Polynomial *data;
    Element *next;
    Element *previous;
    Element(Polynomial*, Element*, Element*);
};

class Stack
{
private:
    Element* head;
    Element* top;
    
public:
    
    Stack();
//    ~Stack(); //destructor, must ensure memory is deallocated
    
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
    Element *getHead(){return head;};
    
    void setTop(Element *top){this->top = top;};
    void setHead(Element *head){this->head = head;};

};

Element::Element(Polynomial *data, Element *previous, Element *next){
    this->data = data;
    this->previous = previous;
    this->next = next;
}

Stack::Stack(){
    cout << "Inside default constructor for class Stack<T>\n";
    head = NULL;
    top  = NULL;
}//END of constructor

//Stack::~Stack(){
//    cout << "Stack<T>::~Stack() Entered destructor for class Stack<T>\n";
//    cout << "calling member function clear() to deallocate memory for all objects on the list\n";
//    Clear();
//    cout << endl;
//    
//}//END of destructor

void Stack::Push(Polynomial *val){
    
    if(head == NULL)
    {
        head = new Element(val, NULL, NULL);
        top  = head;
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
    
    while(top != head)
    {
        this->Pop();
    }
    top = head = NULL;
    delete top;
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
            cout << display2->base << "x" << display2->exponent << " ";
            display2 = display2->next;
        }
        cout << endl;
        display = display->previous;
    }
    cout << endl;
}

#endif /* Stack_h */

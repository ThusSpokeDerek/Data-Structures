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

#ifndef ll_h
#define ll_h

#include <algorithm>

template <typename T>
class Node
{
public:
    T info;
    Node<T> *next;
    
    Node(T = T(), Node<T>* = NULL);
};


/****************************************************************************
 *                                                                          *
 *                   class LL_iterator declaration                          *
 *                                                                          *
 ****************************************************************************/

// new for P4
template <typename T>
class LL_iterator
{
    
private:
    Node<T> *current;
    //pointer to point to the current
    //node in the linked list
    
public:
    
    LL_iterator();
    //default constructor
    //Postcondition: current = NULL;
    
    LL_iterator(Node<T> *ptr);
    //constructor with parameter
    //Postcondition: current = ptr;
    
    T& operator*();
    //overloaded dereferencing operator *
    //Postcondition: Returns the info contained in the node
    
    LL_iterator operator++();
    //overloaded pre-increment operator
    //Postcondition: The iterator is advanced to the next node in the linked list
    
    bool operator==(const LL_iterator &rhsObj) const;
    //overloaded equality operator
    //Postcondition: Returns true if this iterator is equal to the
    //               iterator specified on the right hand side
    //               otherwise returns false
    
    bool operator!=(const LL_iterator &rhsObj) const;
    //overloaded equality operator
    //Postcondition: Returns true if this iterator is NOT equal to the
    //               iterator specified on the right hand side
    //               otherwise returns false
    
    
}; //END class LL_iterator

template <typename T>
LL_iterator<T>::LL_iterator(){
    current = NULL;
}

template <typename T>
LL_iterator<T>::LL_iterator(Node<T> *ptr){
    current = ptr;
}

template <typename T>
T& LL_iterator<T>::operator*(){
    return current->info;
}

template <typename T>
LL_iterator<T> LL_iterator<T>::operator++(){
    return current->next;
}

template <typename T>
bool LL_iterator<T>::operator==(const LL_iterator &rhsObj) const{
   
    return this->current == rhsObj.current;
    
}

template <typename T>
bool LL_iterator<T>::operator!=(const LL_iterator &rhsObj) const{
  
    return this->current != rhsObj.current;
    
}


template <typename T>
class LL
{
    //friend function, overloaded stream insertion operator mainly for testing
    //NOTE: The template parameter has a different identifier, this is on purpose
    template<typename F>
    friend ostream& operator <<(ostream &os, const LL<F> &rhsObj);

private:
    unsigned long count;
    Node<T>* head;
    
    //copyList is a private function called by
    //both copy constructor and overloaded = operator (must ensure deep copy)
    void copyList(const LL<T> &listToCopy);

public:
    
    LL();
    ~LL(); //destructor, must ensure memory is deallocated
    
    //copy constructor
    LL(const LL<T> &otherLL);
    
    //overloaded = operator
    LL<T> operator=(const LL<T> &rhsObj);
    
    //member function push_back results in a Node<T> object being added
    //to the end of the linked list requires dynamic allocation of memory
    void push_back(T);
    
    //member function insert results in a Node<T> object being inserted by
    //ascending order (smallest to largest) by incident number
    void insert(T);
    
    //member function pop_back removes the last list object and deallocates memory
    void pop_back();
    
    //member function clear removes all objects from the list and deallocates memory
    void clear();
    
    //member function size returns number of objects on the linked list
    unsigned long size() const;
    
    //member function at, same as at function of vector class
    T& at(int ndx) const;
    
    LL_iterator<T> begin() const {return LL_iterator<T>(head);};
    LL_iterator<T> end() const {return LL_iterator<T>(NULL);};
};

template<typename T>
Node<T>::Node(T t, Node<T> *n){
    info = t;
    next = n;
}

template<typename F>
ostream& operator<<(ostream &os, const LL<F> &rhsObj){

    Node<F> *current = rhsObj.head;
    
    while ( current != NULL )
    {
        os << current->info << endl;
        current = current->next;

    }
    return os;
}

template<typename T>
void LL<T>::copyList(const LL<T> &listToCopy){
    
    if(listToCopy.head == NULL){
        this->head = NULL;
    }
    else{
        this->head = new Node<T>(listToCopy.head->info, NULL);
        Node<T> *ptr = this->head;
        Node<T> *ptr2 = listToCopy.head->next;
        
        while(ptr2 != NULL){
            ptr->next = new Node<T>(ptr2->info, NULL);
            ptr2 = ptr2->next;
            ptr = ptr->next;
        }
    }
}

template<typename T>
LL<T>::LL(){
    cout << "Inside default constructor for class LL<T>\n";
    count = 0;
    head = NULL;
}//END of constructor

template<typename T>
LL<T>::~LL(){
    cout << "LL<T>::~LL() Entered destructor for class LL<T>\n";
    cout << "calling member function clear() to deallocate memory for all objects on the list\n";
    cout << "\tLL<T>::clear() preparing to remove " << size() << " Nodes from the linked list\n";
    clear();
    cout << "LL<T>::clear() new count is: " << size() << endl;
    

}//END of destructor

template<typename T>
LL<T>::LL(const LL<T> &otherLL){
    copyList(otherLL);
}


template<typename T>
LL<T> LL<T>::operator=(const LL<T> &rhsObj)
{
    if(this != rhsObj){
        
        if(rhsObj.head != NULL){
            
            clear();
        }
    
    copyList(rhsObj);

    }
    
    return rhsObj;
}//END

template<typename T>
void LL<T>::push_back(T val){
    
        Node<T> *add_obj;
        Node<T> *tail = head;
        add_obj = new Node<T>(val, NULL);
        
        
        //if list is empty, make this node the first node on the list
        if (head == NULL)
        {
            head = add_obj;
            //tail = add_obj;
        }
        else
        {
            //update the next pointer of the last node on the lists to point to the new node
            //tail->next = NULL;
            while (tail->next != NULL) {
                tail = tail->next;
                
            }
            
            //now tail points to the next to last node, move it to the new last node
            tail->next = add_obj;
            add_obj->next = NULL;
    
        }
        count++;

}

template<typename T>
void LL<T>::insert(T val){
    
    if(head == NULL){
        head = new Node<T>(val, NULL);
       
    }
    else if(head->info >= val){
        Node<T> *add_obj = head;
        head = new Node<T>(val, add_obj);
        //head = add_obj;
    }
    
    Node<T> *trail_current = head;
    Node<T> *current = head->next;
    while(current != NULL && current->info < val){
        trail_current = current;
        current = current->next;
    }
    //Node<T> *add_obj = NULL;
    trail_current->next = new Node<T>(val, current);
    //trail_current->next = add_obj;
    //add_obj->next = current;

}


template<typename T>
void LL<T>::pop_back(){
    
    Node<T> *tail;
    if (head == NULL)
    {
        cout << "  List is empty, nothing to do" << endl;
    }
    
    else if (head == tail)
    {
        //only one item on the list
        delete head;
        head = NULL;
        tail = NULL;
        
        cout << "  Deleted single Node that was on the list" << endl;
        
        count--;
    }
    else
    {
        //cout << "  Traversing the list to find last node to delete." << endl;
        
        //traverse the list, find next to last node, delete last node
        Node<T> *current = head;
        
        while (current->next != tail)
        {
            current = current->next;
        }
        
        delete tail;
        tail = current;
        tail->next = NULL;
        
        count--;
    }
}


template<typename T>
void LL<T>::clear(){
    
    //Node<T> *tail;
    int numDeleted = 0;
    if (head == NULL)
    {
        cout << "  List is empty, nothing to do" << endl;
    }
    
    else if (head == NULL)
    {
        //only one item on the list
        delete head;
        head = NULL;
      //  tail = NULL;
        
        cout << "  Deleted single Node that was on the list" << endl;
        
        count--;
        numDeleted++;
    }
    else
    {
        //cout << "  Traversing the list to find last node to delete." << endl;
        
        //traverse the list, find next to last node, delete last node
        Node<T> *current = head;
        
        while (current != NULL)
        {
            current = current->next;
            delete head;
            head = current;
            count--;
            numDeleted++;
        }
        
    }
    
    
} //END LL::clear()


template<typename T>
unsigned long LL<T>::size() const{
    int count;
    Node<T> *ptr = head;
    /* traverse the list */
    while (ptr != NULL) {
        /* Update the counter */
        count++;
        /* move along to the next node */
        ptr = ptr->next;
    }
    count--;
    return count;
}

template<typename T>
T& LL<T>::at(int ndx) const{
   
    Node<T> *current = head;
    
    try
    {
        if ( ndx < 0 || ndx >= count )
        {
            throw string("ERROR: out of bounds in LL::at()");
        }
        
        for ( int i = 0; (i < ndx) && (current != NULL); i++ )
        {
            current = current->next;
        }
        
    }
    catch (string a)
    {
       // throw a;
    }
    
    return current->info;
}

/****************************************************************************
 *                                                                          *
 *          class Node (template specialization version)                    *
 *                                                                          *
 *            The class definition and member function                      *
 *            implementation code for a specialized version                 *
 *            of the Node class is provided to students                     *
 *            in COSC 052 Spring 2016 to use in part                        *
 *            or in total for class projects.                               *
 *            Students may use this code as their                           *
 *            own, without any attribution.                                 *
 *            The specialization if to handle Nodes that                    *
 *            store pointers to RR_6180 objects.                            *
 *                                                                          *
 ****************************************************************************/

/****************************************************************************
 ^^                                                                        ^^
 ^^            SPECIALIZED    class Node declaration                       ^^
 ^^                                                                        ^^
 ****************************************************************************/

// new for P4 (template specialization)
template <>
class Node<RR_6180*>
{
public:
    RR_6180 *info;
    Node<RR_6180*> *next;
    
    //specialized to dynamically allocate memory, we will
    //discuss in class why this would be prudent to do
    //(afterall, a pointer was passed in, so why allocate memory again?)
    Node(RR_6180*, Node<RR_6180*> *n = NULL);
    
    //specialization to deallocate memory
    ~Node();
    
}; //END declaration for template specialization of class Node



/****************************************************************************
 ^^^^                                                                    ^^^^
 ^^^^                      BEGIN                                         ^^^^
 ^^^^                                                                    ^^^^
 ^^^^       SPECIALIZED    class Node implementation                     ^^^^
 ^^^^                                                                    ^^^^
 ****************************************************************************/

// new for P4 (template specialization)
Node<RR_6180*>::Node(RR_6180 *ptr6180, Node<RR_6180*> *n)
{
    //cout << "inside specialized version of constructor Node() " << endl;
    
    RR_6180 *addMe = NULL;
    
    RR_57 *ptr57 = NULL;
    RR_55A *ptr55a = NULL;
    RR_54 *ptr54 = NULL;
    
    try
    {
        
        if ( ptr6180->get_report_code() == "57")
        {
            ptr57 = static_cast<RR_57*>(ptr6180);
            //cout << "allocating memory for RR_57 object" << endl;
            addMe = new RR_57(*ptr57);
        }
        
        else if ( ptr6180->get_report_code() == "55a" ||
                 ptr6180->get_report_code() == "55A" )
        {
            ptr55a = static_cast<RR_55A*>(ptr6180);
            //cout << "allocating memory for RR_57A object" << endl;
            addMe = new RR_55A(*ptr55a);
        }
        
        else if ( ptr6180->get_report_code() == "54")
        {
            ptr54 = static_cast<RR_54*>(ptr6180);
            //cout << "allocating memory for RR_54 object" << endl;
            addMe = new RR_54(*ptr54);
        }
        else
        {
            cout << "something went wrong inside specialized Node constructor with parameters\n";
            cout << "there was no match to the category_code, should be 57, 55a, or 54\n";
            cout << "see Milestone 4, last bullet about the RRLog convert constructor\n";
        }
        
        
        info = addMe;
        
        next = n;
    }
    catch (std::bad_alloc baErr)
    {
        throw;
    }
    catch   (...)
    {
        throw string("unknown error in constructor of specialized Node class");
    }
}



// new for P4 (template specialization)
Node<RR_6180*>::~Node()
{
    
    //cout << "inside specialized version of destructor ~Node() " << endl;
    delete info;
    
}

/****************************************************************************
 ^^^^                                                                    ^^^^
 ^^^^                       END                                          ^^^^
 ^^^^                                                                    ^^^^
 ^^^^       SPECIALIZED    class Node implementation                     ^^^^
 ^^^^                                                                    ^^^^
 ****************************************************************************/



#endif /* ll_h */

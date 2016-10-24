//
//  LL.h
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

#ifndef LL_h
#define LL_h


using std::cout;
using std::endl;


struct Node
{
    int base, exponent;
    Node *next;
    Node(int, int, Node *);
};

class Polynomial
{
    private:
        Node *head;
    
    public:
        Polynomial();//constructor
        ~Polynomial();//destructor
    
        //Member functions
        void sort(Node *);
        void clear();
        void display();
    
        //Overloaded operators
        Polynomial operator = (Polynomial);
        Polynomial operator + (Polynomial);
        Polynomial operator - (Polynomial);
        Polynomial operator * (Polynomial);

    
        Node *getHead(){return head;};
};

Node::Node(int base, int exponent, Node *next)
{
    this->base = base;
    this->exponent = exponent;
    this->next = next;
}

Polynomial::Polynomial()
{
    this->head = NULL;
}

Polynomial::~Polynomial()
{
//    clear();//goes out of scope
}

void Polynomial::sort(Node *newterm)
{
    if(head == NULL)
    {
        head = newterm;
    }
    else
    {
        Node *add_node = head;
        Node *current = head;
        
        while(current != NULL)
        {
            if(current->exponent < newterm->exponent)
            {
                if(current == head)
                {
                    newterm->next = head;
                    head = newterm;
                    current = NULL;
                }
                else
                {
                    add_node->next = newterm;
                    newterm->next = current;
                    current = NULL;
                }
            }
            else if(current->exponent > newterm->exponent)
            {
                if(current->next == NULL)
                {
                    current->next = newterm;
                    current = NULL;
                }
                else
                {
                    add_node = current;
                    current = current->next;
                }
            }
            else
            {
                current->base = current->base + newterm->base;
                delete newterm;
                newterm = NULL;
                if(current->base == 0)
                {
                    if(current->next == NULL)
                    {
                        if(current == head)
                        {
                            delete head;
                            current = head = NULL;
                        }
                        else
                        {
                            add_node->next = NULL;
                            delete current;
                            current = NULL;
                        }
                    }
                    else
                    {
                        
                        if(current == head)
                        {
                            head = head->next;
                            current->next = NULL;
                            delete current;
                            current = NULL;
                        }
                        else
                        {
                            add_node->next = current->next;
                            current->next = NULL;
                            delete current;
                            current = NULL;
                        }
                    }
                }
                else
                {
                    current = NULL;
                }
            }
        }
        
    }
}

void Polynomial::clear()
{
    if(head != NULL)
    {
        while(head != NULL)
        {
            Node *temp = head;
            head = head->next;
            temp->next = NULL;
            delete temp;
            temp = NULL;
        }
        head = NULL;
    }
    else
    {
        head = NULL;
    }
}

void Polynomial::display()
{
    Node *current = head;
    while(current != NULL)
    {
        cout << current->base << "x^" << current->exponent << " ";
        current = current->next;
    }
    cout << endl;
}

Polynomial Polynomial::operator=(Polynomial poly)
{
    if(this->head == NULL)
    {
        Node *poly_node = poly.head;
        while(poly_node != NULL)
        {
            Node *new_poly = new Node(poly_node->base, poly_node->exponent, NULL);
            this->sort(new_poly);
            poly_node = poly_node->next;
        }
    }
    else
    {
        this->clear();
        Node *poly_node = poly.head;
        while(poly_node != NULL)
        {
            Node *new_poly = new Node(poly_node->base, poly_node->exponent, NULL);
            this->sort(new_poly);
            poly_node = poly_node->next;
        }
    }
    return *this;
}

Polynomial Polynomial::operator+(Polynomial poly)
{
    Polynomial *sum = new Polynomial();
    Node *poly2 = this->head;
    Node *poly_node = poly.head;
    while(poly2 != NULL)
    {
        Node *new_poly = new Node(poly2->base, poly2->exponent, NULL);
        sum->sort(new_poly);
        poly2 = poly2->next;
    }
    while(poly_node != NULL)
    {
        Node *new_poly = new Node(poly_node->base, poly_node->exponent, NULL);
        sum->sort(new_poly);
        poly_node = poly_node->next;
    }
    
    return *sum;
}

Polynomial Polynomial::operator-(Polynomial poly)
{
    Polynomial *diff = new Polynomial();
    Node *poly2 = this->head;
    Node *poly_node = poly.head;
    while(poly2 != NULL)
    {
        Node *new_poly = new Node(poly2->base, poly2->exponent, NULL);
        diff->sort(new_poly);
        poly2 = poly2->next;
    }
    while(poly_node != NULL)
    {
        Node *new_poly = new Node(-poly_node->base, poly_node->exponent, NULL);
        diff->sort(new_poly);
        poly_node = poly_node->next;
    }
    
    return *diff;
}

Polynomial Polynomial::operator*(Polynomial poly)
{
    Polynomial *product = new Polynomial();
    Node *poly2 = this->head;
    Node *poly_node = poly.head;
    while(poly2 != NULL)
    {
        while(poly_node != NULL)
        {
            Node *new_poly = new Node(poly_node->base * poly2->base, poly_node->exponent + poly2->exponent, NULL);
            product->sort(new_poly);
            poly_node = poly_node->next;
        }
        poly2 = poly2->next;
        poly_node = poly.head;
    }
    return *product;
}


#endif /* LL_h */

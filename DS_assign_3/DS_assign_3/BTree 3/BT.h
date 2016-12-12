//
//  BST.h
//
//  COSC 160 Fall 2016
//  Assignment 3
//
//  Due on: NOV 17, 2016
//  Author: Derek Acosta
//
//  Created by Derek Acosta on 11/12/16.
//  Copyright © 2016 Derek Acosta. All rights reserved.
//

#ifndef BT_h
#define BT_h

#include <algorithm>
#include <ctype.h>
#include <string.h>

using std::cout;
using std::endl;
using std::max;
using std::string;
using std::strcmp;
using std::sort;

template<typename T>
class BTNode
{
public:
    // data members
    T *keys;
    BTNode<T> *_parent;//simplist way to do this; should not justify penalization for caliber of assignment
    virtual void insert(BTNode<T> *, T) = 0;
    virtual void print(BTNode<T> *) = 0;
    virtual void split(BTNode<T> *, BTNode<T> *) = 0;
    virtual void merge(BTNode<T> *, BTNode<T> *) = 0;
    virtual bool search(BTNode<T> *, T) = 0;
    virtual int height(BTNode<T> *, int) = 0;
    virtual void Delete(BTNode<T> *, T) = 0;
    virtual void DeleteAll(BTNode<T> *, int) = 0;
    int size, capacity;
};

template<typename T>
class leafNode: public BTNode<T>
{
public:
    void insert(BTNode<T> *, T);//insertion into node
    void print(BTNode<T> *);//print node
    void split(BTNode<T> *, BTNode<T> *);//split contents of node to allow for correct order
    void merge(BTNode<T> *, BTNode<T> *);//merge nodes when deleted
    bool search(BTNode<T> *, T);//search for nodes
    int height(BTNode<T> *, int);//find height of tree for deallocating all nodes
    void Delete(BTNode<T> *, T);//delete one key
    void DeleteAll(BTNode<T> *, int);//delete all keys
    leafNode(T*, BTNode<T> *,int, int);
};

template<typename T>
class internalNode: public BTNode<T>
{
public:
    void insert(BTNode<T> *, T);//insertion into node
    void print(BTNode<T> *);//print node
    void split(BTNode<T> *, BTNode<T> *);//split contents of node to allow for correct order
    void merge(BTNode<T> *, BTNode<T> *);//merge nodes when deleted
    bool search(BTNode<T> *, T);//search for nodes
    int height(BTNode<T> *, int);//find height of tree for deallocating all nodes
    void Delete(BTNode<T> *, T);//delete one key
    void DeleteAll(BTNode<T> *, int);//delete all keys
    BTNode<T> **_branches;
    internalNode(T*, BTNode<T> *,int, int, BTNode<T> **);
};



template<typename T>
leafNode<T>::leafNode(T *t, BTNode<T> *parent, int size, int capacity)
{
    this->keys = t;
    this->_parent = NULL;
    this->size = size;
    this->capacity = capacity;
}

template<typename T>
internalNode<T>::internalNode(T *t, BTNode<T> *parent, int size, int capacity, BTNode<T> **branches)
{
    this->keys = t;
    this->_parent = NULL;
    this->size = size;
    this->capacity = capacity;
    this->_branches = branches;
}

template<typename T>
void leafNode<T>::insert(BTNode<T> *node, T t)
{
    if(node->size < node->capacity)
    {
        node->keys[node->size] = t;
        node->size++;
        sort(node->keys, node->keys+node->size);
    }
    else
    {
        sort(node->keys, node->keys+node->size);
        BTNode<T> *newNode = new leafNode<T>(new T[node->capacity], NULL, 0, node->capacity);
        this->split(node, newNode);
    }
}

template<typename T>
void internalNode<T>::insert(BTNode<T> *node,T t)
{
    int index = 0;
    bool position = false;
    
    while(index < node->size && position == false)
    {
        if(t < node->keys[index])
        {
            position = true;
        }
        else
        {
            index++;
        }
    }
    
    if(((internalNode<T>*)node)->_branches[index] == ((internalNode<T>*)node))
    {
        ((internalNode<T>*)node)->insert(((internalNode<T>*)node)->_branches[index], t);
    }
    else
    {
        sort(node->keys, node->keys+node->size);
        BTNode<T> *newNode = ((internalNode<T>*)node)->_branches[index];
        newNode->insert(newNode, t);
        newNode = NULL;
    }
    
}

template<typename T>
void leafNode<T>::print(BTNode<T> *node)
{
    for(int i=0; i < node->size; i++)
    {
        cout << node->keys[i] << "  ";
    }
}

template<typename T>
void internalNode<T>::print(BTNode<T> *node)
{
    for(int i=0; i <= node->size; i++)
    {
        if(((internalNode<T>*)node)->_branches[i] == (internalNode<T>*)node)
        {
            ((internalNode<T>*)node)->print(((internalNode<T>*)node)->_branches[i]);
        }
        else
        {
            BTNode<T> *newNode = ((internalNode<T>*)node)->_branches[i];
            newNode->print(newNode);
        }
        if(i < node->size)
            cout << node->keys[i] << "  ";
    }
    
}

template<typename T>
void leafNode<T>::split(BTNode<T> *splitNode, BTNode<T> *newNode)
{
    int med = splitNode->size/2 +1;
    int i =0;
    while(med < splitNode->size)
    {
        newNode->keys[i] = splitNode->keys[med];
        med++;
        i++;
    }
    splitNode->size /= 2;
    newNode->size = splitNode->size;
    this->capacity = splitNode->capacity;
    
    if(splitNode->_parent == NULL)
    {
        BTNode<T> *newParent = new internalNode<T>(new T[this->capacity], NULL, 0, this->capacity, new BTNode<T> *[this->capacity+1]);
        splitNode->_parent = newParent;
        newNode->_parent = newParent;
        ((internalNode<T>*)newParent)->_branches[0] = splitNode;
        ((internalNode<T>*)newParent)->_branches[1] = newNode;
        splitNode->_parent->keys[splitNode->_parent->size] = splitNode->keys[splitNode->size];
        splitNode->_parent->size++;
    }
    else
    {
        newNode->_parent = splitNode->_parent;
        splitNode->_parent->keys[splitNode->_parent->size] = splitNode->keys[splitNode->size];
        int i = splitNode->_parent->size;
        while(((internalNode<T>*)splitNode->_parent)->_branches[i] != splitNode)
        {
            ((internalNode<T>*)splitNode->_parent)->_branches[i+1] = ((internalNode<T>*)splitNode->_parent)->_branches[i];
            i--;
        }
        ((internalNode<T>*)splitNode->_parent)->_branches[i+1] = newNode;
        splitNode->_parent->size++;
        if(splitNode->_parent->size == splitNode->_parent->capacity)
        {
            BTNode<T> *newParent = new internalNode<T>(new T[this->capacity], NULL, 0, this->capacity, new BTNode<T> *[this->capacity+1]);
            splitNode->_parent->split(splitNode->_parent, newParent);
        }
    }
    
    
}

template<typename T>
void internalNode<T>::split(BTNode<T> *splitNode, BTNode<T> *newNode)
{
    int med = splitNode->size/2 +1;
    int i =0;
    while(med <= splitNode->size)
    {
        ((internalNode<T>*)newNode)->_branches[i] = ((internalNode<T>*)splitNode)->_branches[med];
        ((internalNode<T>*)newNode)->_branches[i]->_parent = newNode;
        if(med < splitNode->size)
        {
            newNode->keys[i] = splitNode->keys[med];
        }
        
        med++;
        i++;
    }
    splitNode->size /= 2;
    newNode->size = splitNode->size;
    this->capacity = splitNode->capacity;
    
    if(splitNode->_parent == NULL)
    {
        BTNode<T> *newParent = new internalNode<T>(new T[this->capacity], NULL, 0, this->capacity, new BTNode<T> *[this->capacity+1]);
        splitNode->_parent = newParent;
        newNode->_parent = newParent;
        ((internalNode<T>*)newParent)->_branches[0] = splitNode;
        ((internalNode<T>*)newParent)->_branches[1] = newNode;
        splitNode->_parent->keys[splitNode->_parent->size] = splitNode->keys[splitNode->size];
        splitNode->_parent->size++;
    }
    else
    {
        newNode->_parent = splitNode->_parent;
        splitNode->_parent->keys[splitNode->_parent->size] = splitNode->keys[splitNode->size];
        int i = splitNode->_parent->size;
        while(((internalNode<T>*)splitNode->_parent)->_branches[i] != splitNode)
        {
            ((internalNode<T>*)splitNode->_parent)->_branches[i+1] = ((internalNode<T>*)splitNode->_parent)->_branches[i];
            i--;
        }
        ((internalNode<T>*)splitNode->_parent)->_branches[i+1] = newNode;
        splitNode->_parent->size++;
        if(splitNode->_parent->size == splitNode->_parent->capacity)
        {
            BTNode<T> *newParent = new internalNode<T>(new T[this->capacity], NULL, 0, this->capacity, new BTNode<T> *[this->capacity+1]);
            splitNode->_parent->split(splitNode->_parent, newParent);
        }
    }
}

template<typename T>
bool internalNode<T>::search(BTNode<T> *node,T t)
{
    for(int i = 0; i < node->size; i++)
    {
        if(node->keys[i] == t)
        {
            return true;
        }
    }
    
    int index = 0;
    bool position = false;
    
    while(index < node->size && position == false)
    {
        if(t < node->keys[index])
        {
            position = true;
        }
        else
        {
            index++;
        }
    }
    
    if(((internalNode<T>*)node)->_branches[index] == (internalNode<T>*)node)
    {
        return ((internalNode<T>*)node)->search(((internalNode<T>*)node)->_branches[index], t);
    }
    else
    {
        sort(node->keys, node->keys+node->size);
        BTNode<T> *newNode = ((internalNode<T>*)node)->_branches[index];
        return newNode->search(newNode, t);
    }
}

template<typename T>
bool leafNode<T>::search(BTNode<T> *node,T t)
{
    for(int i = 0; i < node->size; i++)
    {
        if(node->keys[i] == t)
        {
            return true;
        }
    }
    return false;
}

template<typename T>
void leafNode<T>::Delete(BTNode<T> *node,T t)
{
    bool found = false;
    for(int i =0; i< node->size; i++)
    {
        if(node->keys[i] == t)
        {
            found = true;
            for(int j = i; j < node->size; j++)
            {
                node->keys[j] = node->keys[j+1];
            }
            node->size--;
            break;
        }
    }
    if(found == true)
    {
        cout << "Object " << t << " was found and deleted\n";
    }
    else
    {
        cout << "Object " << t << " not found\n";
    }
    
    if(node->size < node->capacity/2)
    {
        if(node->_parent != NULL)
        {
            int index = 0;
            while(((internalNode<T>*)node->_parent)->_branches[index] != node)
            {
                index++;
            }
            if(index == 0)
            {
                node->merge(node,((internalNode<T>*)node->_parent)->_branches[index+1]);
            }
            else if(index == node->_parent->size)
            {
                node->merge(((internalNode<T>*)node->_parent)->_branches[index-1], node);
            }
            else
            {
                if(((internalNode<T>*)node->_parent)->_branches[index-1]->size < ((internalNode<T>*)node->_parent)->_branches[index+1]->size)
                {
                    node->merge(((internalNode<T>*)node->_parent)->_branches[index-1], node);
                }
                else if(((internalNode<T>*)node->_parent)->_branches[index-1]->size >= ((internalNode<T>*)node->_parent)->_branches[index+1]->size)
                {
                    node->merge(node, ((internalNode<T>*)node->_parent)->_branches[index+1]);
                }
            }
        }
    }
}

template<typename T>
void internalNode<T>::Delete(BTNode<T> *node, T t)
{
    bool found = false;
    int var = 0;
    for(int i = 0; i < node->size; i++)
    {
        if(node->keys[i] == t)
        {
            var = i;
            found = true;
            for(int j = i; j < node->size; j++)
            {
                node->keys[j] = node->keys[j+1];
            }
            break;
        }
    }
    if(found == false)
    {
        int index = 0;
        bool position = false;
        
        while(index < node->size && position == false)
        {
            if(t < node->keys[index])
            {
                position = true;
            }
            else
            {
                index++;
            }
            
        }
        
        if(((internalNode<T>*)node)->_branches[index] == (internalNode<T>*)node)
        {
            return ((internalNode<T>*)node)->Delete(((internalNode<T>*)node)->_branches[index], t);
        }
        else
        {
            sort(node->keys, node->keys+node->size);
            BTNode<T> *newNode = ((internalNode<T>*)node)->_branches[index];
            return newNode->Delete(newNode, t);
        }
    }
    else
    {
        if(((internalNode<T>*)node)->_branches[var+1] == ((internalNode<T>*)node))
        {
            node->keys[var] = ((internalNode<T>*)node)->_branches[var+1]->keys[0];
            node->Delete(((internalNode<T>*)node)->_branches[var+1], ((internalNode<T>*)node)->_branches[var+1]->keys[0]);
        }
        else
        {
            BTNode<T> *newNode = ((internalNode<T>*)node)->_branches[var+1];
            node->Delete(newNode, ((internalNode<T>*)node)->_branches[var+1]->keys[0]);
        }
        
    }
}


template<typename T>
void leafNode<T>::merge(BTNode<T> *mergeNode, BTNode<T> *newNode)
{
    if(newNode->size != 0)
    {
        for(int i = 0; i < newNode->size;i++)
        {
            mergeNode->keys[mergeNode->size] = newNode->keys[i];
            mergeNode->size++;
        }
    }
    int index = 0;
    while(((internalNode<T>*)mergeNode->_parent)->_branches[index] != newNode)
    {
        index++;
    }
    delete ((internalNode<T>*)mergeNode->_parent)->_branches[index];
    ((internalNode<T>*)mergeNode->_parent)->_branches[index] = NULL;
    int var = mergeNode->_parent->size;
    while(((internalNode<T>*)mergeNode->_parent)->_branches[var] != mergeNode)
    {
        ((internalNode<T>*)mergeNode->_parent)->_branches[var] = ((internalNode<T>*)mergeNode->_parent)->_branches[var+1];
        delete ((internalNode<T>*)mergeNode->_parent)->_branches[var+1];
        ((internalNode<T>*)mergeNode->_parent)->_branches[var+1] = NULL;
        var--;//something is wrong here, but im not quite sure what it is
    }
    mergeNode->_parent->size--;
    
    if(mergeNode->_parent->size < mergeNode->_parent->capacity/2)
    {
        if(mergeNode->_parent != NULL)
        {
            int index = 0;
            while(((internalNode<T>*)mergeNode->_parent)->_branches[index] != ((internalNode<T>*)mergeNode))
            {
                index++;
            }
            if(index == 0)
            {
                ((internalNode<T>*)mergeNode)->merge(mergeNode,((internalNode<T>*)mergeNode->_parent)->_branches[index+1]);
            }
            else if(index == mergeNode->_parent->size)
            {
                ((internalNode<T>*)mergeNode)->merge(((internalNode<T>*)mergeNode->_parent)->_branches[index-1], ((internalNode<T>*)mergeNode));
            }
            else
            {
                if(((internalNode<T>*)mergeNode->_parent)->_branches[index-1]->size < ((internalNode<T>*)mergeNode->_parent)->_branches[index+1]->size)
                {
                    ((internalNode<T>*)mergeNode)->merge(((internalNode<T>*)mergeNode->_parent)->_branches[index-1], ((internalNode<T>*)mergeNode));
                }
                else if(((internalNode<T>*)mergeNode->_parent)->_branches[index-1]->size >= ((internalNode<T>*)mergeNode->_parent)->_branches[index+1]->size)
                {
                    ((internalNode<T>*)mergeNode)->merge(((internalNode<T>*)mergeNode), ((internalNode<T>*)mergeNode->_parent)->_branches[index+1]);
                }
            }
            
        }
    }
}

template<typename T>
void internalNode<T>::merge(BTNode<T> *mergeNode, BTNode<T> *newNode)
{
    if(newNode->size != 0)
    {
        for(int i = 0; i < newNode->size;i++)
        {
            mergeNode->keys[mergeNode->size] = newNode->keys[i];
            ((internalNode<T>*)mergeNode)->_branches[mergeNode->size] = ((internalNode<T>*)newNode)->_branches[i];
            delete ((internalNode<T>*)newNode)->_branches[i];
            ((internalNode<T>*)newNode)->_branches[i] = NULL;
            mergeNode->size++;
        }
    }
    int index = 0;
    while(((internalNode<T>*)mergeNode->_parent)->_branches[index] != newNode)
    {
        index++;
    }
    delete ((internalNode<T>*)mergeNode->_parent)->_branches[index];
    ((internalNode<T>*)mergeNode->_parent)->_branches[index] = NULL;
    int var = mergeNode->_parent->size;
    while(((internalNode<T>*)mergeNode->_parent)->_branches[var] != mergeNode)
    {
        ((internalNode<T>*)mergeNode->_parent)->_branches[index] = ((internalNode<T>*)mergeNode->_parent)->_branches[var+1];
        delete ((internalNode<T>*)mergeNode->_parent)->_branches[var+1];
        ((internalNode<T>*)mergeNode->_parent)->_branches[var+1] = NULL;
        var--;
    }
    mergeNode->_parent->size--;
    
    if(mergeNode->_parent->size < mergeNode->_parent->capacity/2)
    {
        if(mergeNode->_parent != NULL)
        {
            int index = 0;
            while(((internalNode<T>*)mergeNode->_parent)->_branches[index] != ((internalNode<T>*)mergeNode))
            {
                index++;
            }
            if(index == 0)
            {
                ((internalNode<T>*)mergeNode)->merge(mergeNode,((internalNode<T>*)mergeNode->_parent)->_branches[index+1]);
            }
            else if(index == mergeNode->_parent->size)
            {
                ((internalNode<T>*)mergeNode)->merge(((internalNode<T>*)mergeNode->_parent)->_branches[index-1], ((internalNode<T>*)mergeNode));
            }
            else
            {
                if(((internalNode<T>*)mergeNode->_parent)->_branches[index-1]->size < ((internalNode<T>*)mergeNode->_parent)->_branches[index+1]->size)
                {
                    ((internalNode<T>*)mergeNode)->merge(((internalNode<T>*)mergeNode->_parent)->_branches[index-1], ((internalNode<T>*)mergeNode));
                }
                else if(((internalNode<T>*)mergeNode->_parent)->_branches[index-1]->size >= ((internalNode<T>*)mergeNode->_parent)->_branches[index+1]->size)
                {
                    ((internalNode<T>*)mergeNode)->merge(((internalNode<T>*)mergeNode), ((internalNode<T>*)mergeNode->_parent)->_branches[index+1]);
                }
            }
            
        }
        
    }
}

template<typename T>
void leafNode<T>::DeleteAll(BTNode<T> *node, int height)
{
    //requires nothing
}

template<typename T>
void internalNode<T>::DeleteAll(BTNode<T> *node, int height)
{
    for(int i=height-1; i != 0; i--)
    {
        for(int j=node->size; j < -1; j--)
        {
            
            if(((internalNode<T>*)node)->_branches[j] == (internalNode<T>*)node)
            {
                ((internalNode<T>*)node)->DeleteAll(((internalNode<T>*)node)->_branches[j], height);
            }
            else
            {
                delete ((internalNode<T>*)node)->_branches[j];
                ((internalNode<T>*)node)->_branches[j] = NULL;
            }
        }
        delete node;
        node = NULL;
    }
}

template<typename T>
int leafNode<T>::height(BTNode<T> *node, int Theight)
{
    return Theight;
}

template<typename T>
int internalNode<T>::height(BTNode<T> *node, int Theight)
{
    Theight++;
    if(((internalNode<T>*)node)->_branches[0] == (internalNode<T>*)node)
    {
        return ((internalNode<T>*)node)->height(((internalNode<T>*)node)->_branches[0], Theight);
    }
    else
    {
        sort(node->keys, node->keys+node->size);
        BTNode<T> *newNode = ((internalNode<T>*)node)->_branches[0];
        return newNode->height(newNode, Theight);
    }
}

template<typename TreeType>
class BTree
{
private:
    BTNode<TreeType> *_root;
    int capacity;
    
public:
    
    BTree(int);
    ~BTree(); //destructor, must ensure memory is deaBTreeocated
    
//all member functions act as wrappers for BTNode functions
    
    //member function will print BTree in level	order
    void print();
    
    //member function find will return true if node is on tree
    bool search(const TreeType&);
    
    //member function deleteAll results in all BTNode<T> objects being removed from the tree
    void DeleteAll();
    
    //member function Delete results in a BTNode<T> object being remove from the tree
    void Delete(const TreeType&);
    
    //member function insert results in a BTNode<T> object being inserted onto the tree
    void insert(const TreeType&);
    
    //height function
    int height();
};

template<typename TreeType>
BTree<TreeType>::BTree(int Order)
{
    this->capacity = Order;
    if(this->capacity < 3)
        this->capacity = 3;
    else if(this->capacity%2 == 0)
    {
        this->capacity--;
    }
    this->_root = new leafNode<TreeType>(new TreeType[this->capacity], NULL, 0, this->capacity);
}//END of constructor

template<typename TreeType>
BTree<TreeType>::~BTree(){
    this->DeleteAll();
    cout << "Memory is successfully delocated: Tree is empty\n\n";
}//END of destructor

template<typename TreeType>
void BTree<TreeType>::print()
{
    if(_root == NULL)
    {
        cout << "There is nothing to print\n";
    }
    else
    {
        if(_root->_parent != NULL)
            _root = _root->_parent;
        _root->print(_root);
    }
    
}

template<typename TreeType>
bool BTree<TreeType>::search(const TreeType& val)
{
    return _root->search(_root, val);
}


template<typename TreeType>
void BTree<TreeType>::DeleteAll()
{
    if(_root->_parent != NULL)
    {
        _root = _root->_parent;
    }
    int height = _root->height(_root, 0);
    if(height == 0)
    {
        _root = NULL;
    }
    else
    {
        _root->DeleteAll(_root, height);
        _root = NULL;
    }
}

template<typename TreeType>
void BTree<TreeType>::Delete(const TreeType& val)
{
    if(_root->_parent != NULL)
    {
        this->_root = this->_root->_parent;
    }
    _root->Delete(_root, val);
    
    if(_root->size == 0)
    {
        this->_root = ((internalNode<TreeType>*)_root)->_branches[0];
        this->_root->_parent = NULL;
    }
}


template<typename TreeType>
void BTree<TreeType>::insert(const TreeType& val)
{
    if(_root->_parent != NULL)
    {
        this->_root = this->_root->_parent;
    }
    
    if(_root->search(_root, val))
       cout << "Warning " << val << " is a duplicate value, ignoring\n";
    _root->insert(_root, val);
}

template<typename TreeType>
int BTree<TreeType>::height()
{
    if(_root->_parent != NULL)
    {
        _root = _root->_parent;
    }
    return _root->height(_root, 0);
}




#endif /* BT_h */

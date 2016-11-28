//
//  BST.h
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

#ifndef BST_h
#define BST_h
#include <algorithm>
#include <ctype.h>
#include <string.h>

using std::cout;
using std::endl;
using std::max;
using std::string;
using std::strcmp;

template<typename T>
class BNode
{
public:
    // data members
    T _node;
    BNode<T> *_left;
    BNode<T> *_right;
    BNode<T> *_parent;
    BNode(T = T(), BNode<T>* = NULL, BNode<T>* = NULL, BNode<T>* = NULL); //constructor
    ~BNode(); //destructor
    BNode(const BNode<T> &otherBNode); //copy constructor
    BNode<T> operator=(const BNode<T> &rhsObj); // overloaded operator =
    BNode<T> operator<(const BNode<T> &rhsObj); // overloaded operator <
};

template<typename T>
BNode<T>::BNode(T t, BNode<T> *left, BNode<T> *right, BNode<T> *parent)
{
    this->_node = t;
    this->_left = left;
    this->_right = right;
    this->_parent = parent;
}

template<typename T>
BNode<T>::~BNode()
{
    
}

template<typename TreeType>
class BinaryTree
{
private:
    size_t _nodeCount;
    BNode<TreeType> *_root;
    
public:
    
    BinaryTree();
    ~BinaryTree(); //destructor, must ensure memory is deaBinaryTreeocated
    
    //member function will print the order of the tree from Left, Node, Right
    void printInorderTraversal();
    void Inorder(BNode<TreeType> *&);

    //member function will print the order of the tree from Node, Left, Right
    void printPostorderTraversal();
    void Postorder(BNode<TreeType> *&);

    //member function will print the order of the tree from Left, Right, Node
    void printPreorderTraversal();
    void Preorder(BNode<TreeType> *&);

    //member function find will return true if node is on tree
    bool find(const TreeType&);
    bool finder(BNode<TreeType> *&, const TreeType&);
    BNode<TreeType> *index(BNode<TreeType> *&, const TreeType&);

    //member function deleteAll results in all BNode<T> objects being removed from the tree
    void deleteAll();
    void deleterall(BNode<TreeType> *&);
    
    //member function height results in a retrieving the height of the tree from the longest path
    int height(const TreeType&  = 0);
    int heighter(BNode<TreeType> *&);

    //member function Delete results in a BNode<T> object being remove from the tree
    void Delete(TreeType);
    void Deleter(BNode<TreeType> *&, const TreeType&);

    //member function insert results in a BNode<T> object being inserted onto the tree
    void insert(const TreeType&);
    void insertion(BNode<TreeType> *&, const TreeType&);
};

template<typename TreeType>
BinaryTree<TreeType>::BinaryTree(){
    _nodeCount = 0;
    _root = NULL;
}//END of constructor

template<typename TreeType>
BinaryTree<TreeType>::~BinaryTree(){
    deleteAll();
    cout << "Memory is successfully delocated: Tree is empty\n";
}//END of destructor

template<typename TreeType>
void BinaryTree<TreeType>::printInorderTraversal()
{
    Inorder(_root);
    cout << endl;
}

template<typename TreeType>
void BinaryTree<TreeType>::Inorder(BNode<TreeType> *&current)
{
    if(current == NULL)
        return;
    Inorder(current->_left);
    cout << current->_node << " ";
    Inorder(current->_right);
}

template<typename TreeType>
void BinaryTree<TreeType>::printPostorderTraversal()
{
    Postorder(_root);
    cout << endl;
}

template<typename TreeType>
void BinaryTree<TreeType>::Postorder(BNode<TreeType> *&current)
{
    if(current == NULL)
        return;
    Postorder(current->_left);
    Postorder(current->_right);
    cout<<current->_node << " ";
}

template<typename TreeType>
void BinaryTree<TreeType>::printPreorderTraversal()
{
    Preorder(_root);
    cout << endl;
}

template<typename TreeType>
void BinaryTree<TreeType>::Preorder(BNode<TreeType> *&current)
{
    if(current == NULL)
        return;
    cout << current->_node << " ";
    Preorder(current->_left);
    Preorder(current->_right);
}

template<typename TreeType>
bool BinaryTree<TreeType>::find(const TreeType& val)
{
    return finder(_root, val);
}

template<typename TreeType>
bool BinaryTree<TreeType>::finder(BNode<TreeType> *&current, const TreeType& val)
{
    if(current == NULL)
    {
        return false;
    }
    else
    {
        if(current->_node == val)
            return true;
        else if(val < current->_node)
            return finder(current->_left, val);
        else
            return finder(current->_right, val);
    }
}

template<typename TreeType>
void BinaryTree<TreeType>::deleteAll()
{
    deleterall(_root);
}

template<typename TreeType>
void BinaryTree<TreeType>::deleterall(BNode<TreeType> *&current)
{
    try
    {
        if(current == NULL)
            return;
        deleterall(current->_left);
        deleterall(current->_right);
        delete current;
        current = NULL;

    }
    catch(...)
    {
        throw;
    }
}

template<typename TreeType>
int BinaryTree<TreeType>::height(const TreeType& val)
{
    try
    {
        if(!val)
            return heighter(_root);
        else
        {
            if(find(val))
            {
                BNode<TreeType> *temp = index(_root, val);
                return heighter(temp);
            }
            else
            {
                string a =  "Element not in the tree\n";
                throw a;
            }
        }
    }
    catch(string a)
    {
        throw a;
    }
    
}

template<typename TreeType>
BNode<TreeType> *BinaryTree<TreeType>::index(BNode<TreeType> *&current, const TreeType& val)
{
    if(current == NULL)
    {
        return index(current, val);
    }
    else
    {
        if(current->_node == val)
            return current;
        else if(val < current->_node)
            return index(current->_left, val);
        else
            return index(current->_right, val);
    }
}

template<typename TreeType>
int BinaryTree<TreeType>::heighter(BNode<TreeType> *&current)
{
    if(current == NULL) return -1;
    return 1 + max(heighter(current->_left), heighter(current->_right));
}

template<typename TreeType>
void BinaryTree<TreeType>::Delete(TreeType val)
{
    if(this->find(val))
        Deleter(_root, val);
    else
        cout << "ERROR: node not found, cannot be deleted\n";
}

template<typename TreeType>
void BinaryTree<TreeType>::Deleter(BNode<TreeType> *&current, const TreeType &val)
{
    if(current == NULL)
    {
        cout << "ERROR: Tree is empty\n";
    }
    else
    {
        if(val == current->_node)
        {
            if(current->_left == NULL && current->_right == NULL)//case1: node has no children;leaf node
            {
                if(current == _root)
                {
                    delete current;
                    current = NULL;
                    cout << "Node was deleted\n";
                }
                else if(current->_parent->_left == current)
                {
                    current->_parent->_left = NULL;
                    delete current;
                    current = NULL;
                    cout << "Node was deleted\n";
                }
                else if(current->_parent->_right == current)
                {
                    current->_parent->_right = NULL;
                    delete current;
                    current = NULL;
                    cout << "Node was deleted\n";
                }
                
            }
            else if(current->_left == NULL && current->_right != NULL)
            {
                if(_root == current)
                {
                    current = current->_right;
                    current->_parent->_right = NULL;
                    delete current->_parent;
                    current->_parent = NULL;
                    cout << "Node was deleted\n";
                }
                else if(current->_parent->_right == current)
                {
                    current->_parent->_right = current->_right;
                    current->_right = NULL;
                    delete current->_right;
                    current->_right = NULL;
                    cout << "Node was deleted\n";
                }
            }
            else if(current->_right == NULL && current->_left != NULL)
            {
                if(_root == current)
                {
                    current = current->_left;
                    current->_parent->_left = NULL;
                    delete current->_parent;
                    current->_parent = NULL;
                    cout << "Node was deleted\n";
                }
                else if(current->_parent->_left == current)
                {
                    current->_parent->_left = current->_left;
                    current->_left = NULL;
                    delete current->_right;
                    current->_left = NULL;
                    cout << "Node was deleted\n";
                }
            }
            else
            {
                BNode<TreeType> *successor = current->_left;
                while(successor->_right != NULL)
                    successor = successor->_right;
                current->_node = successor->_node;
                if(successor->_right == NULL && successor->_right == NULL)
                    Deleter(successor, successor->_node);
                delete current;
                cout << "Node was deleted\n";
            }
        }
        else if(val < current->_node)
            return Deleter(current->_left, val);
        else
            return Deleter(current->_right, val);
    }
}

template<typename TreeType>
void BinaryTree<TreeType>::insert(const TreeType& val)
{
    if(find(val))
        cout << "This value has duplicates: " << val << endl;
    insertion(_root, val);
}

template<typename TreeType>
void BinaryTree<TreeType>::insertion(BNode<TreeType> *&current, const TreeType &val)
{
    if(_root == NULL)
        current = new BNode<TreeType>(val, NULL, NULL, NULL);
    else if(val < current->_node)
    {
        if(current->_left == NULL)
            current->_left = new BNode<TreeType>(val, NULL, NULL, current);
        insertion(current->_left, val);
    }
    else if(val > current->_node)
    {
        if(current->_right == NULL)
            current->_right = new BNode<TreeType>(val, NULL, NULL, current);
        insertion(current->_right, val);
    }
}


#endif /* BST_h */

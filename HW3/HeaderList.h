#pragma once

#include <iostream>

using namespace std;

template<class T>
class ChainNode;

template<class T>
class HeaderList;

template <class T>
ostream& operator<< (ostream& os, const HeaderList<T>& chain);

template<class T>
class ChainNode
{
friend class HeaderList<T>;
friend ostream& operator<<<T> (ostream& os, const HeaderList<T>& chain);
private:
    T data;
    ChainNode<T>* link;
};

template<class T>
class HeaderList
{
    using Node = ChainNode<T>;
public:
    HeaderList();
    ~HeaderList();
    void InsertFront(const T& e);
    void InsertBack(const T& e);
    void DeleteFront();
    void DeleteBack();
    int Size();
    void DeleteOdd();
    HeaderList Split(Node* node);
    void Merge(HeaderList<T>& c);
private:
    Node* first;
friend ostream& operator<<<T> (ostream& os, const HeaderList<T>& chain);
};

template <class T>
ostream& operator<< (ostream& os, const HeaderList<T>& list)
{
    ChainNode<T>* head = list.first;
    for (ChainNode<T>* temp = head->link; temp != head; temp = temp->link)
        os << temp->data << ' ';
    return os << '\n';
}

template<class T>
HeaderList<T>::HeaderList()
{
    first = new Node;
    first->link = first;
}

template<class T>
HeaderList<T>::~HeaderList()
{
    Node* temp = first->link;
    while (temp != first)
    {
        Node* deleteNode = temp;
        temp = temp->link;
        delete deleteNode;
    }
}

template<class T>
void HeaderList<T>::InsertFront(const T& e)
{
    Node* temp = new Node;
    temp->data = e;
    temp->link = first->link;
    first->link = temp;
}

template<class T>
void HeaderList<T>::InsertBack(const T& e)
{
    Node* temp = first;
    while (temp->link != first)
        temp = temp->link;
    temp->link = new Node;
    temp->link->data = e;
    temp->link->link = first;
}

template<class T>
void HeaderList<T>::DeleteFront()
{
    if (first->link == first)
        throw "Can't delete an empty list. ";
    Node* temp = first->link;
    first->link = first->link->link;
    delete temp;
}

template<class T>
void HeaderList<T>::DeleteBack()
{
    if (first->link == first)
        throw "Can't delete an element from an empty list";
    Node* temp = first;
    while (temp->link->link != first)
        temp = temp->link;
    delete temp->link;
    temp->link = first;
}

template<class T>
int HeaderList<T>::Size()
{
    Node* temp = first;
    int i = 0;
    while (temp->link != first)
    {
        temp = temp->link;
        i++;
    }
    return i;
}

template<class T>
void HeaderList<T>::DeleteOdd()
{
    for (Node* temp = first; temp->link != first; temp = temp->link)
    {
        Node* deleteNode = temp->link;
        temp->link = temp->link->link;
        delete deleteNode;
    }
}

template<class T>
HeaderList<T> HeaderList<T>::Split(Node* node)
{
    HeaderList<T> hl;
    Node* temp = first; 

    while (temp->link != node)
        temp = temp->link;

    hl.first->link = temp->link;
    temp->link = first;
    temp = hl.first->link;

    while (temp->link != first)
        temp = temp->link;

    temp->link = hl.first;
    return hl;
}

template<class T>
void HeaderList<T>::Merge(HeaderList<T>& c)
{
    Node* temp = first;
    Node* tempL = first->link;
    Node* tempC = c.first->link;
    temp->link = temp;
    while (tempL != first && tempC != c.first)
    {
        temp->link = tempL;
        tempL = tempL->link;
        temp->link->link = tempC;
        tempC = tempC->link;
        temp = temp->link->link;
    }
    while (tempL != first)
    {
        temp->link = tempL;
        tempL = tempL->link;
        temp = temp->link;
    }
    while (tempC != c.first)
    {
        temp->link = tempC;
        tempC = tempC->link;
        temp = temp->link;
    }
    temp->link = first;
    c.first->link = c.first;
}
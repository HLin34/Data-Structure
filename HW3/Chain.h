#pragma once

#include <iostream>

using namespace std;

template<class T>
class Chain;

template<class T>
class ChainNode;

template <class T>
ostream& operator<< (ostream& os, const Chain<T>& chain);

template<class T>
class ChainNode
{
    friend class Chain<T>;
    friend ostream& operator<<<T> (ostream& os, const Chain<T>& chain);
public:
    ChainNode() = default;
    ChainNode(const T& data, ChainNode<T>* link = 0)
        : data(data), link(link) {}
private:
    T data;
    ChainNode<T>* link;
};

template<class T>
class Chain
{
public:
    Chain()
    {
        first = 0;
    }
    ~Chain();
    void InsertFront(const T& e);
    void DeleteFront();
    void DeleteBack();
    T& Get(int i);
    void Delete(int i);
    void Insert(int i, const T& e);
    int Size();
    void Set(int i, const T& e);
    void DeleteOdd();
    Chain DivideMiddle();
    Chain Split(ChainNode<T>* node);
    void Merge(Chain<T>& c);
private:
    ChainNode<T>* first;
    friend ostream& operator<<<T> (ostream& os, const Chain<T>& chain);
};

template<class T>
ostream& operator<< (ostream& os, const Chain<T>& chain)
{
    for (ChainNode<T>* temp = chain.first; temp; temp = temp->link)
        os << temp->data << " ";
    return os << '\n';
}

template<class T>
Chain<T>::~Chain()
{
    while(first)
    {
        ChainNode<T>* temp = first;
        first = first->link;
        delete temp;
    }
}

template<class T>
void Chain<T>::InsertFront(const T& e)
{
    if (!first)
    {
        first = new ChainNode<T>;
        first->data = e;
        first->link = 0;
    }
    else
    {
        ChainNode<T>* temp = first;
        first = new ChainNode<T>;
        first->data = e;
        first->link = temp;
    }
}

template<class T>
void Chain<T>::DeleteFront()
{
    if (!first)
        throw "The chain is empty!";
    ChainNode<T>* front = first;
    first = first->link;
    delete front;
}

template<class T>
void Chain<T>::DeleteBack()
{
    if (!first)
        throw "The chain is empty!";
    else if (!first->link)
    {
        delete first;
        first = 0;
    }
    else
    {
        ChainNode<T>* temp = first;
        while (temp->link->link)
            temp = temp->link;
        delete temp->link;
        temp->link = 0;
    }
}

template<class T>
T& Chain<T>::Get(int i)
{
    if (i < 0)
        throw "The ith element doesn't exists!";
    else
    {
        ChainNode<T>* temp = first;
        while (i--)
        {
            if (!temp)
                throw "The ith element doesn't exists!";
            temp = temp->link;
        }
        if (temp)
            return temp->data;
        else
            throw "The ith element doesn't exists!";
    }
}

template<class T>
void Chain<T>::Delete(int i)
{
    if (first == 0 || i < 0)
        throw "Cannot delete from empty chain";
    ChainNode<T>* deleteNode;
    if (i == 0)
    {
        deleteNode = first;
        first = first->link;
    }
    else
    {
        ChainNode<T>* temp = first;
        while (--i)
        {
            if (!temp)
                throw "The ith element doesn't exists!";
            temp = temp->link;
        }
        deleteNode = temp->link;
        temp->link = temp->link->link;
    }
    delete deleteNode;
}

template<class T>
void Chain<T>::Insert(int i, const T& e)
{
    if (i < 0)
        throw "Bad insert index";
    if (i == 0)
        first = new ChainNode<T>(e, first);
    else
    {
        ChainNode<T>* temp = first;
        while (--i)
        {
            if (!temp)
                throw "Bad insert index";
            temp = temp->link;
        }
        temp->link = new ChainNode<T>(e, temp->link);
    }
}

template<class T>
int Chain<T>::Size()
{
    int i = 0;
    ChainNode<T>* temp = first;
    while(temp)
    {
        i++;
        temp = temp->link;
    }
    return i;
}

template<class T>
void Chain<T>::Set(int i, const T& e)
{
    if (i < 0)
        throw "Bad index";
    if (i == 0)
    {
        if (first)
            first->data = e;
        else
            throw "Bad index";
    }
    else
    {
        ChainNode<T>* temp = first;
        while (i--)
        {
            temp = temp->link;
            if (!temp)
                throw "Bad index";
        }
        temp->data = e;
    }
}

template<class T>
void Chain<T>::DeleteOdd()
{
    ChainNode<T>* temp = first;
    if (!temp) return;
    first = first->link;
    delete temp;
    temp = first;
    while (temp)
    {
        ChainNode<T>* deleteNode = temp->link;
        temp->link = temp->link->link;
        temp = temp->link;
        if (deleteNode)
            delete deleteNode;
    }
}

template<class T>
Chain<T> Chain<T>::DivideMiddle()
{
    Chain<T> c;
    int size = Size() / 2;
    ChainNode<T>* temp = first;
    while (--size)
        temp = temp->link;
    c.first = temp->link;
    temp->link = 0;
    return c;
}

template<class T>
Chain<T> Chain<T>::Split(ChainNode<T>* node)
{
    ChainNode<T>* temp = first;
    Chain<T> c;
    if (temp == node)
    {
        first = 0;
        c.first = temp;
    }
    else
    {
        while(temp->link != node)
        {
            if (!temp)
                throw "Bad splitting ChainNode<T>";
            temp = temp->link;
        }
        c.first = temp->link;
        temp->link = 0;
    }
    return c;
}

template<class T>
void Chain<T>::Merge(Chain<T>& c)
{
    ChainNode<T> head;
    head.link = 0;
    ChainNode<T>* temp = &head;
    ChainNode<T>* temp_l = first;
    ChainNode<T>* temp_c = c.first;
    while (temp_l && temp_c)
    {
        temp->link = temp_l;
        temp_l = temp_l->link;
        temp->link->link = temp_c;
        temp_c = temp_c->link;
        temp = temp->link->link;
    }
    while (temp_l)
    {
        temp->link = temp_l;
        temp = temp->link;
        temp_l = temp_l->link;
    }
    while (temp_c)
    {
        temp->link = temp_c;
        temp = temp->link;
        temp_c = temp_c->link;
    }
    temp->link = 0;
    first = head.link;
    c.first = 0;
}

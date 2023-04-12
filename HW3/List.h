#pragma once

#include <iostream>

using namespace std;

template <class T> 
class List;

template <class T>
class ChainNode
{
friend class List<T>;
public:
    ChainNode() = default;
    ChainNode(const T& _data, ChainNode<T>* ptr = 0)
        : data(_data), link(ptr) 
    {}
private:  
    T data;
    ChainNode<T>* link;
};

// same as chain list
template <class T>
class List
{
public: 
    using Node = ChainNode<T>;
    List(){first = 0;}
    ~List();
    void DeleteFront();
    void DeleteBack();
    void InsertFront(const T& e);
    void InsertBack(const T& e);
    void Concatenate(List<T>& b);
    T& Get(int i);
    T& Front() const;
    T& Back();
    void Delete(int i);
    void Insert(int i, const T& e);
    void Reverse();
    void Print();

    class Iterator
    {
    public:
        Iterator(Node* startNode = 0) : ptr(startNode) {}
        T& operator *() const { return ptr->data; }
        T* operator ->() const { return &ptr->data; }
        Iterator& operator ++() { ptr = ptr->link; return *this; }
        Iterator& operator ++(int) { Iterator old = *this; ptr = ptr->link; return old; }
        bool operator !=(const Iterator r) const { return ptr != r.ptr; }
        bool operator ==(const Iterator r) const { return ptr == r.ptr; }
    private:
        Node* ptr;
    };
    // using iterator = Iterator;
    Iterator begin();
    Iterator end();
private:
    Node* first;
};

template<class T>
List<T>::~List()
{
  while(first)
    {
        Node* temp = first;
        first = first->link;
        delete temp;
    }  
}


template<class T>
void List<T>::DeleteFront()
{
    if (!first)
        throw "The chain is empty!";
    Node* front = first;
    first = first->link;
    delete front;
}

template<class T>
void List<T>::DeleteBack()
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
        Node* temp = first;
        while (temp->link->link)
            temp = temp->link;
        delete temp->link;
        temp->link = 0;
    }
}

template<class T>
void List<T>::InsertFront(const T& e)
{
    if (!first)
    {
        first = new Node;
        first->data = e;
        first->link = 0;
    }
    else 
    {
        Node* temp = first;
        first = new Node;
        first->data = e;
        first->link = temp;
    }    
}


template <class T>
void List<T>::InsertBack(const T& e)
{   
    if (!first)
    {
        first = new Node;
        first->data = e;
        first->link = 0;
    }
    else
    {
        Node* temp = first;
        for (; temp->link; temp = temp->link);
        Node* newNode = new Node;
        newNode->data = e;
        newNode->link = 0;
        temp->link = newNode;
    }
}

template <class T>
void List<T>::Concatenate(List<T>& c)
{
    Node* temp = first;
    if (!temp)
        first = c.first;
    else
    {
        for (; temp->link; temp = temp->link);
        temp->link = c.first;
    }
    c.first = 0;
}

template<class T>
T& List<T>::Get(int i)
{
    if (i < 0)
        throw "The ith element doesn't exists!";
    else
    {
        Node* temp = first;
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
T& List<T>::Back()
{
    Node* temp = first;
    if (!temp)  
        throw "Can't get elements from an empty list!";
    for (; temp->link; temp = temp->link);
    return temp->data;
}

template<class T>
T& List<T>::Front() const
{
    Node* temp = first;
    if (!temp)  
        throw "Can't get elements from an empty list!";
    return temp->data;
}

template<class T>
void List<T>::Delete(int i)
{
    if (first == 0 || i < 0)
        throw "Cannot delete from empty chain";
    Node* deleteNode;
    if (i == 0)
    {
        deleteNode = first;
        first = first->link;
    }
    else 
    {
        Node* temp = first;
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
void List<T>::Insert(int i, const T& e)
{
    if (i < 0)
        throw "Bad insert index";
    if (i == 0)
        first = new Node(e, first);
    else
    {
        Node* temp = first;
        while (--i)
        {
            if (!temp)
                throw "Bad insert index";
            temp = temp->link;
        }
        temp->link = new Node(e, temp->link);
    }
}

template<class T>
void List<T>::Reverse()
{
    Node* curr = first;
    Node* prev = 0;
    Node* r = 0;
    while (curr)
    {
        r = prev;
        prev = curr;
        curr = curr->link;
        prev->link = r;
    }
    first = prev;
}

template<class T>
void List<T>::Print()
{
    for (Node* temp = first; temp; temp = temp->link)
        cout << temp->data << " ";
    cout << endl;
}

template<class T>
typename List<T>::Iterator List<T>::begin()
{
    return Iterator{first};
}

template<class T>
typename List<T>::Iterator List<T>::end()
{
    return Iterator{0};
}

#include <iostream>

using namespace std;

template<class T>
class CircularList;

template<class T>
class ChainNode;

template <class T>
ostream& operator<< (ostream& os, const CircularList<T>& chain);

template<class T>
class ChainNode
{
    friend class CircularList<T>;
    friend ostream& operator<<<T> (ostream& os, const CircularList<T>& chain);
private:
    T data;
    ChainNode<T>* link;
};


template<class T>
class CircularList
{
    using Node = ChainNode<T>;
public:
    CircularList()
    {
        first = 0;
    }
    ~CircularList();
    void InsertFront(const T& e);
    void InsertBack(const T& e);
    void DeleteFront();
    void DeleteBack();
    int Size() const;
    void DeleteOdd();
    CircularList Split(Node* node);
    void Merge(CircularList<T>& c);
private:
    Node* first;
    friend ostream& operator<<<T> (ostream& os, const CircularList<T>& chain);
};

template<class T>
ostream& operator<< (ostream& os, const CircularList<T>& chain)
{
    ChainNode<T>* first = chain.first;
    if (!first)
        return os << '\n';
    else
    {
        os << first->data << " ";
        for (ChainNode<T>* temp = first->link; temp != first; temp = temp->link)
            os << temp->data << " ";
    }
    return os << '\n';
}

template<class T>
CircularList<T>::~CircularList()
{
    Node* temp = first->link;
    while(temp != first)
    {
        Node* deleteNode = temp;
        temp = temp->link;
        delete deleteNode;
    }
    delete first;
    first = 0;
}

template<class T>
void CircularList<T>::InsertFront(const T& e)
{
    if (!first)
    {
        first = new Node;
        first->link = first;
        first->data = e;
    }
    else
    {
        Node* front = first;
        Node* temp = first;
        first = new Node;
        first->data = e;
        first->link = temp;
        while (temp->link != front)
        {
            temp = temp->link;
        }
        temp->link = first;
    }
}

template<class T>
void CircularList<T>::InsertBack(const T& e)
{
    if (!first)
    {
        first = new Node;
        first->data = e;
        first->link = first;
    }
    else
    {
        Node* temp = first;
        while(temp->link != first)
        {
            temp = temp->link;
        }
        temp->link = new Node;
        temp->link->data = e;
        temp->link->link = first;
    }
}

template<class T>
void CircularList<T>::DeleteFront()
{
    if (!first)
        throw "The CircularList is empty!";
    Node* temp = first;
    while (temp->link != first)
    {
        temp = temp->link;
    }
    if (temp == first)
    {
        delete first;
        first = 0;
    }
    else
    {
        temp->link = first->link;
        delete first;
        first = temp->link;
    }
}

template<class T>
void CircularList<T>::DeleteBack()
{
    if (!first)
        throw "The CircularList is empty!";
    else if (first->link == first)
    {
        delete first;
        first = 0;
    }
    else
    {
        Node* temp = first;
        while (temp->link->link != first)
            temp = temp->link;
        delete temp->link;
        temp->link = first;
    }
}

template<class T>
int CircularList<T>::Size() const
{
    if (!first)
        return 0;
    Node* temp = first;
    int i = 1;
    while(temp->link != first)
    {
        i++;
        temp = temp->link;
    }
    return i;
}

template<class T>
void CircularList<T>::DeleteOdd()
{
    if (!first) return;
    Node* newFirst = first->link;
    Node* temp = first->link;
    Node* pre = first;
    // delete first;
    while (temp != first)
    {
        pre = temp;
        Node* deleteNode = temp->link;
        if (temp->link != first)
            temp->link = temp->link->link;
        temp = temp->link;
        delete deleteNode;
    }
    if (pre == first)
    {
        delete first;
        first = 0;
    }
    else
    {
        pre->link = newFirst;
        first = newFirst;
    }
}

template<class T>
CircularList<T> CircularList<T>::Split(Node* node)
{
    Node* temp = first;
    CircularList<T> c;
    if (temp == node)
    {
        first = 0;
        c.first = temp;
    }
    else
    {
        while(temp->link != node)
        {
            if (temp == first)
                throw "Bad splitting node";
            temp = temp->link;
        }
        c.first = temp->link;
        temp->link = first;
        temp = c.first;
        while (temp->link != first)
            temp = temp->link;
        temp->link = c.first;
    }
    return c;
}

template<class T>
void CircularList<T>::Merge(CircularList<T>& c)
{
    if (!first)
    {
        first = c.first;
        c.first = 0;
        return;
    }
    if (!c.first)
    {
        return;
    }

    ChainNode<T> head;
    head.link = 0;
    ChainNode<T>* temp = &head;
    ChainNode<T>* temp_l = first;
    ChainNode<T>* temp_c = c.first;
    do
    {
        temp->link = temp_l;
        temp_l = temp_l->link;
        temp->link->link = temp_c;
        temp_c = temp_c->link;
        temp = temp->link->link;
    }
    while (temp_l != first && temp_c != c.first);

    while (temp_l != first)
    {
        temp->link = temp_l;
        temp = temp->link;
        temp_l = temp_l->link;
    }
    while (temp_c != c.first)
    {
        temp->link = temp_c;
        temp = temp->link;
        temp_c = temp_c->link;
    }
    temp->link = head.link;
    first = head.link;
    c.first = 0;
}

int main()
{
    CircularList<int> list;
    list.InsertBack(4);
    cout << " list.InsertBack(4): " << list;
    list.InsertFront(5);
    cout << " list.InsertFront(5): " << list;
    list.InsertFront(6);
    cout << " list.InsertFront(6): " << list;
    list.InsertBack(2);
    cout << " list.InsertBack(2): " <<list;
    list.DeleteFront();
    cout << " list.DeleteFront(): " <<list;
    list.DeleteBack();
    cout << " list.DeleteBack(): " << list;
    list.InsertBack(8);
    cout << " list.InsertBack(8): " << list;
    list.InsertBack(9);
    cout << " list.InsertBack(9): " << list;
    list.InsertFront(1);
    cout << " list.InsertFront(1): " << list;
    list.InsertBack(4);
    cout << " list.InsertBack(4): " << list;
    list.DeleteOdd();
    cout << " list.DeleteOdd(): " << list;

    CircularList<int> list_2;
    for (int i = 1; i < 3; i++)
        list_2.InsertBack(i);
    for (int i = 5; i < 9; i++)
        list_2.InsertFront(i);
    cout << " list2: " << list_2;

    list_2.Merge(list);
    cout << " Merge list2 with list: " << list_2;
}

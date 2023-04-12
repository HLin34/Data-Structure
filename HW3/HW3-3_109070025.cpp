#include <iostream>

using namespace std;

//List
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

//Stack
template <class T>
class Stack : private List<T>
{
public:
    // using print = List<T>::Print;
    Stack() : List<T>() {};
    void Push(const T& e);
    void Pop();
    void Print();
    T& Top() const;
};

template<class T>
void Stack<T>::Push(const T& e)
{
    this->InsertFront(e);
}

template<class T>
void Stack<T>::Pop()
{
    this->DeleteFront();
}

template<class T>
void Stack<T>::Print()
{
    List<T>::Print();
}

template<class T>
T& Stack<T>::Top() const
{
    return this->Front();
}

//Queue
template <class T>
class Queue : private List<T>
{
public:
    // class Iterator : public List<T>::Iterator {};
    // using Iterator = List<T>::Iterator;
    Queue() : List<T>() {};
    void Push(const T& e);
    void Pop();
    void Print();
    T& Front();
    T& Back();
};

template<class T>
void Queue<T>::Push(const T& e)
{
    this->InsertBack(e);
}

template<class T>
void Queue<T>::Pop()
{
    this->DeleteFront();
}

template<class T>
void Queue<T>::Print()
{
    List<T>::Print();
}

template<class T>
T& Queue<T>::Front()
{
    return List<T>::Front();
}

template<class T>
T& Queue<T>::Back()
{
    return List<T>::Back();
}

int compute(List<int>& list)
{
    int sum = 0;
    List<int>::Iterator start = list.begin();
    List<int>::Iterator five  = list.begin();
    for (int i = 0; i < 5; i++)
        if (five == list.end())
            return 0;
        else
            five++;
    for (; five != list.end(); start++, five++)
        sum += (*start) * (*five);
    return sum;
}

int main ()
{
    List<int> list;
    for (int i = 7; i < 12; i++)
        list.InsertFront(i);
    for (int i = 3; i < 9; i++)
        list.InsertBack(i);
    cout << " list: " ;
    list.Print();
    list.Delete(7);
    cout << " list.Delete(7): " ;
    list.Print();
    list.DeleteBack();
    cout << " list.DeleteBack: " ;
    list.Print();
    list.DeleteFront();
    cout << " list.DeleteFront: " ;
    list.Print();
    list.Insert(3, 5);
    cout << " list.Insert(3, 5): " ;
    list.Print();
    list.Reverse();
    cout << " list.Reverse: " ;
    list.Print();
    cout << " The Front of list: " << list.Front() << endl;
    cout << " The Back of list: " <<list.Back() << endl;
    cout << " list.Get(5): " << list.Get(2) << endl << endl;
    cout << endl;

    Stack<int> stack;
    for (int i = 5 ; i < 10; i++)
        stack.Push(i);
    cout << " Stack: ";
    stack.Print();
    cout << " The top of the Stack: " << stack.Top() << endl;
    for (int i = 0; i < 2; i++)
        stack.Pop();
    cout << " Stack after Pop 0~1: ";
    stack.Print();
    cout << " The top of the Stack: " << stack.Top() << endl;

    Queue<int> queue;
    cout << endl;
    for (int i = 8; i < 17; i++)
        queue.Push(i);
    cout << " Queue: ";
    queue.Print();
    cout << " The Front of the Queue: " << queue.Front() << endl;
    cout << " The Back of the Queue: " << queue.Back() << endl;
    for (int i = 0; i < 5; i++)
        queue.Pop();
    cout << " Queue after Pop 0~4: ";
    queue.Print();
    cout << " The Front of the Queue: " <<queue.Front() << endl;
    cout << " The Back of the Queue: " <<queue.Back() << endl;

    return 0;
}

#include "List.h"

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

#include "List.h"

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

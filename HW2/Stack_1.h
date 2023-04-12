#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>

using namespace std;

#include "ChangeSize1D.h"

template<class T>
class Stack;

template<class T>
ostream& operator<<(ostream& os, Stack<T>& s);

// @param T datatype;
template<class T>
class Stack
{
public:
    Stack(int stackCapacity = 10);
    bool IsEmpty() const;
    T& Top() const;
    void Push(const T& item);
    void Pop();
private:
    T* stack;
    int top;
    int capacity;
friend ostream& operator<<<T>(ostream& os, Stack<T>& s); 
};

template<class T>
ostream& operator<<(ostream& os, Stack<T>& s)
{
    os << s.top << endl;
    for (int i = 0; i <= s.top; i++)
        os << i << ": " << s.stack[i] << endl;
    return os;
}

template<class T>
Stack<T>::Stack(int stackCapacity)
    : capacity (stackCapacity)
{
    if (capacity < 1) throw "Stack capacity must be > 0";
    stack = new T[capacity];
    top = -1;
}

template<class T>
bool Stack<T>::IsEmpty() const
{
    return top == -1;
}

template<class T>
T& Stack<T>::Top() const
{
    if (IsEmpty())
        throw "Stack is empty";
    return stack[top];
}

template<class T>
void Stack<T>::Push(const T& item)
{
    if (top == capacity - 1)
    {
        ChangeSize1D(stack, capacity, 2 * capacity);
        capacity *= 2;
    }    
    stack[++top] = item;
}

template<class T>
void Stack<T>::Pop()
{
    if (IsEmpty()) 
        throw "Stack is empty. Cannot delete.";
    stack[top--].~T();    
}


#endif // __STACK_H__
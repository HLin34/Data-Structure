#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include "Stack.h"

using namespace std;

template<class T>
class Queue;

template<typename T>
ostream& operator<<(ostream& os, Queue<T>& rhs);

template<class T>
Queue<T> reverseQueue(const Queue<T>& other);

template<class T>
class Queue
{
public:
    Queue(int queueCapacity = 10);
    bool IsEmpty() const;
    T& Front() const;
    T& Rear() const;
    void Push(const T& item);
    void Pop();
    int Size() const;
    int Capacity() const;
    Queue<T> Merge(const Queue& other);
private:
    T* queue;
    int front;
    int rear;
    int capacity;

    friend ostream& operator<< <T> (ostream& os, Queue<T>& rhs);
    friend Queue<T> reverseQueue<T> (const Queue<T>& other);
};

template<typename T>
ostream& operator<< (ostream& os, Queue<T>& rhs)
{
    if (rhs.rear == rhs.front) return os << "No elements!" << "\n";
    int start = (rhs.front + 1) % rhs.capacity;
    for (int i = start; i <= rhs.rear; i++)
        os << rhs.queue[i] << " ";
    os << "\n";
    return os;
}

template<class T>
Queue<T>::Queue(int queueCapacity)
    : capacity(queueCapacity)
{
    if (capacity < 1) throw "Queue capacity must be > 0";
    queue = new T[capacity];
    front = rear = 0;
}

template<class T>
bool Queue<T>::IsEmpty() const
{
    return front == rear;    
}

template<class T>
T& Queue<T>::Front() const
{
    if (IsEmpty()) throw "Queue is empty. No front element";
    return queue[(front + 1) % capacity];   
}

template<class T>
T& Queue<T>::Rear() const
{
    if (IsEmpty()) throw "Queue is empty. No rear element";
    return queue[rear];
}

template<class T>
void Queue<T>::Push(const T& item)
{
    if ((rear + 1) % capacity == front)
    {
        T* newQu = new T[2 * capacity];
        int start = (front + 1) % capacity;
        if (start < 2)
            copy(queue + start, queue + start + capacity - 1, newQu);
        else
        {
            copy(queue + start, queue + capacity, newQu);
            copy(queue, queue + rear + 1, newQu + capacity - start);
        }
        front = 2 * capacity - 1;
        rear = capacity - 2;
        delete[] queue;
        queue = newQu;
        capacity *= 2;
    }
    rear = (rear + 1) % capacity;
    queue[rear] = item;
}

template<class T>
void Queue<T>::Pop()
{
    if (IsEmpty()) 
        throw "Queue is empty. Cannot delete.";
    front = (front + 1) % capacity;
    queue[front].~T();
}

template<class T>
int Queue<T>::Size() const
{
    int start = (front + 1) % capacity;
    return rear - start + 1;
}

template<class T>
int Queue<T>::Capacity() const
{
    return capacity;
}

template<class T>
Queue<T> Queue<T>::Merge(const Queue& other)
{
    int size1 = Size();
    int size2 = other.Size();
    Queue<T> newQu(size1 + size2 + 1);
    int start1 = (front + 1) % capacity;
    int start2 = (other.front + 1) % other.capacity;
    int index1, index2;
    for (index1 = 0, index2 = 0; index1 < size1 && index2 < size2; index1++, index2++)
    {
        newQu.Push(queue[(start1 + index1) % capacity]);
        newQu.Push(other.queue[(start2 + index2) % other.capacity]);
    }
    for (;index1 < size1; index1++)
        newQu.Push(queue[(start1 + index1) % capacity]);
    for (;index2 < size2; index2++)
        newQu.Push(other.queue[(start2 + index2) % other.capacity]);
    return newQu;
}

#endif
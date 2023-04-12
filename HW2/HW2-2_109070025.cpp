#include <iostream>

using namespace std;

template < class T >
class Queue
{
public:
    //friend Stack<T>;
    Queue (int queueCapacity = 10);
    bool IsEmpty( ) const;
    void Push(const T& item);    // add an item into the queue
    void Pop( );    // delete an item
    T& Front() const;    // return top element of stack
    T& Rear() const;    // return top element of stack
    void reverseQueue(Queue<int>& Queue);
    int size();
private:
    T*queue;
    int front;
    int rear;
    int capacity;
} ;
template<class T>
Queue<T>::Queue(int queueCapacity):capacity(queueCapacity)
{
    if(capacity<1) throw "Queue capacity must be>0";
    queue=new T[capacity];
    front=rear=0;
}
template <class T>
inline bool Queue<T>::IsEmpty()const
{
    return front==rear;
}
template <class T>
inline T&Queue<T>::Front()const
{
    if(IsEmpty()) throw "Queue is empty. No front element";
    return queue[(front+1)%capacity];
}
template <class T>
inline T&Queue<T>::Rear()const
{
    if(IsEmpty()) throw "Queue is empty. No rear element";
    return queue[rear];
}
template<class T>
void Queue<T>::Push(const T&x)
{
    if((rear+1) % capacity == front)
    {
        T*newQueue= new T[2*capacity];
        int start=(front +1)%capacity;
        if(start<2)
        {
            copy(queue+start,queue+start+capacity-1,newQueue);
        }

        else
        {
            copy(queue+start,queue+capacity,newQueue);
            copy(queue,queue+rear+1,newQueue+capacity-start);
        }
        front =2*capacity-1;
        rear=capacity-2;
        capacity*=2;
        delete[]queue;
        queue=newQueue;
        // ChangeSize1D(stack,capacity,2*capacity);
    }
    rear=(rear+1)%capacity;
    queue[rear]=x;
}
template<class T>
void Queue<T>::Pop()
{
    if(IsEmpty()) throw "Queue is empty. Cannot delete.";
    front =(front+1)%capacity;
    queue[front].~T();
}

template <class T>
class Stack
{
public:
    Stack(int stackCapacity=10);
    bool IsEmpty()const;
    T& Top()const;
    void Push(const T&item);
    void Pop( );
private:
    T*stack;
    int top;
    int capacity;
};
template <class T>
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity)
{
    if(capacity<1) throw "Stack capacity must be>0";
    stack=new T[capacity];
    top=-1;
}
template<class T>
inline bool Stack<T>::IsEmpty()const
{
    return top==-1;
}
template<class T>
inline T&Stack<T>::Top()const
{
    if(IsEmpty()) throw"Stack is empty";
    return stack[top];
}
template<class T>
void Stack<T>::Push(const T&x)
{
    if(top == capacity-1)
    {
        T*newStack= new T[2*capacity];
        copy(stack,stack+top+1,newStack);
        delete[]stack;
        stack=newStack;
        // ChangeSize1D(stack,capacity,2*capacity);
        capacity*=2;
    }
    stack[++top]=x;
}
template<class T>
void Stack<T>::Pop()
{
    if(IsEmpty()) throw "Stack is empty. Cannot delete.";
    stack[top--].~T();
}



template <class T>
void Queue<T>::reverseQueue(Queue<int>& Queue)
{
    Stack<int> Stack;
    while (!Queue.IsEmpty())
    {
        Stack.Push(Queue.Front());
        Queue.Pop();
    }
    while (!Stack.IsEmpty())
    {
        Queue.Push(Stack.Top());
        Stack.Pop();
    }
}


int main()
{
    Queue<int> Queue, q;
    Queue.Push(51);
    Queue.Push(23);
    Queue.Push(56);
    Queue.Push(42);
    Queue.Push(58);
    Queue.Push(16);
    Queue.Push(92);
    Queue.Push(66);
    Queue.Push(35);
    Queue.Push(80);

    cout<<"The front of Queue1 = "<<Queue.Front()<<endl;
    cout<<"The rear of Queue1 = "<<Queue.Rear()<<endl;
    cout<<"Whether Queue1 is empty = "<<Queue.IsEmpty()<<endl;

    cout<<"Queue before reverse : ";
    while (!Queue.IsEmpty())
    {
        cout << Queue.Front() << " ";
        q.Push(Queue.Front());
        Queue.Pop();
    }
    while (!q.IsEmpty())
    {
        Queue.Push(q.Front());
        q.Pop();
    }
    cout<<endl;
    cout<<"Queue after reverse : ";
    Queue.reverseQueue(Queue);
    while (!Queue.IsEmpty())
    {
        cout << Queue.Front() << " ";
        Queue.Pop();
    }
    cout<<endl;
}

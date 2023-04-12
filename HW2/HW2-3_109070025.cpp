#include <iostream>

using namespace std;

template < class T >
class Bag
{
public:
    Bag (int bagCapacity = 10);
    ~Bag();
    int Size() const;
    bool IsEmpty( ) const;
    T& Element() const;
    void Push(const T&);
    void Pop( );
protected:
    T*array;
    int top;
    int capacity;
} ;
template < class T >
class Stack:public Bag<T>
{
public:
    T& Top() const;
    void Pop();
    using Bag<T>::Bag;
    using Bag<T>::Size;
    using Bag<T>::IsEmpty;
    using Bag<T>::Push;
private:
    using Bag<T>::array;
    using Bag<T>::top;
    using Bag<T>::capacity;

};

template < class T >
inline T& Stack<T>::Top()const
{
    if(IsEmpty()) throw "Stack is empty.";
    return array[top];
}
template < class T >
void Stack<T>::Pop()
{
    if(IsEmpty()) throw "Stack is empty. Cannot delete.";
    top--;
}
template < class T >
class Queue:public Bag<T>
{
public:
    Queue(int queueCapacity = 10);
    void Pop();
    void Push(const T&item);
    T& Front() const;
    T& Rear() const;
    int Size();
    bool IsEmpty( ) const;
protected:
    using Bag<T>::array;
    using Bag<T>::capacity;
    int front,rear;
};
template <class T>
Queue<T>::Queue(int queueCapacity):Bag<T>(queueCapacity)
{
    if(capacity<1) throw "Queue capacity must be>0";
    array=new T[capacity];
    front=rear=0;
}
template <class T>
inline bool Queue<T>::IsEmpty()const
{
    return front ==rear;
}
template <class T>
inline T& Queue<T>::Front() const
{
    if(IsEmpty()) throw "Queue is empty. No front element";
    return array[(front+1)%capacity];
}
template <class T>
inline T&Queue<T>::Rear()const
{
    if(IsEmpty()) throw "Queue is empty. No rear element";
    return array[rear];
}
template<class T>
void Queue<T>::Push(const T&x)
{
    if((rear+1) % capacity == front)
    {
        T*newArray= new T[2*capacity];
        int start=(front +1)%capacity;
        if(start<2)
        {
            copy(array+start,array+start+capacity-1,newArray);
        }

        else
        {
            copy(array+start,array+capacity,newArray);
            copy(array,array+rear+1,newArray+capacity-start);
        }
        front =2*capacity-1;
        rear=capacity-2;
        capacity*=2;
        delete[]array;
        array=newArray;
        // ChangeSize1D(stack,capacity,2*capacity);
    }
    rear=(rear+1)%capacity;
    array[rear]=x;
}
template<class T>
void Queue<T>::Pop()
{
    if(IsEmpty()) throw "Queue is empty. Cannot delete.";
    front =(front+1)%capacity;
    array[front].~T();
}
template<class T>
int Queue<T>::Size()
{
    return((rear-front+capacity)%capacity);
}
template < class T >
class Deque:public Queue<T>
{
public:
//    Deque(int dequeCapacity = 10);
    using Queue<T>::Queue;
    using Queue<T>::Pop;
    using Queue<T>::Push;
    using Queue<T>::Front;
    using Queue<T>::Rear;
    using Queue<T>::Size;
    using Queue<T>::IsEmpty;
    void Rearpop();
    void Frontpush(const T& );
private:
    using Bag<T>::array;
    using Bag<T>::capacity;
    using Queue<T>::front;
    using Queue<T>::rear;
};
//template < class T >
//Deque<T>::Deque(int dequeCapacity):Queue<T>(dequeCapacity)
//{
//    if(capacity<1) throw "Deque capacity must be>0";
//    array=new T[capacity];
//    front=rear=0;
//}
template <class T>
void Deque<T>::Rearpop()
{
    if(IsEmpty()) throw "Deque is empty, cannot delete";
    array[rear].~T();
    rear=(rear-1)%capacity;
}
template <class T>
void Deque<T>::Frontpush(const T& x)
{
    if((rear+1) % capacity == front)
    {
        T*newArray= new T[2*capacity];
        int start=(front +1)%capacity;
        if(start<2)
        {
            copy(array+start,array+start+capacity-1,newArray);
        }

        else
        {
            copy(array+start,array+capacity,newArray);
            copy(array,array+rear+1,newArray+capacity-start);
        }
        front =2*capacity-1;
        rear=capacity-2;
        capacity*=2;
        delete[]array;
        array=newArray;
        // ChangeSize1D(stack,capacity,2*capacity);
    }
    array[front]=x;
    front=(front+capacity-1)%capacity;
}
template <class T>
Bag<T>::Bag(int bagCapacity):capacity(bagCapacity)
{
    if(capacity<1) throw "Bag capacity must be>0";
    array=new T[capacity];
    top=-1;
}
template<class T>
Bag<T>::~Bag()
{
    delete[]array;
}
template<class T>
inline int Bag<T>::Size()const
{
    return top+1;
}
template<class T>
inline bool Bag<T>::IsEmpty()const
{
    return top==-1;
}
template<class T>
inline T& Bag<T>::Element()const
{
    if(IsEmpty()) throw"Bag is empty";
    return array[0];
}
template <class T>
void Bag<T>::Push(const T&x)
{
    if(capacity == top+1)
    {
        T*newArray= new T[2*capacity];
        copy(array,array+top+1,newArray);
        delete[]array;
        array=newArray;
        // ChangeSize1D(stack,capacity,2*capacity);
        capacity*=2;
    }
    array[++top]=x;
}
template <class T>
void Bag<T>::Pop()
{
    if(IsEmpty()) throw "Bag is empty. Cannot delete.";
    int deletePos = top/2;
    copy(array+deletePos+1,array+top+1,array+deletePos);
    array[top--].~T();
}

int main()
{
    cout <<"The <int> mode "<< endl;
    Stack<int>stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    stack.Push(40);
    stack.Push(50);
    //stack.Pop();
    cout<<"The Stack before pop: Size="<<stack.Size()<<" => ";
    while (!stack.IsEmpty())
    {
        cout << stack.Top() << " ";
        stack.Pop();
    }

    cout<<endl;

    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    stack.Push(40);
    stack.Push(50);
    stack.Pop();
    cout<<"The Stack after pop: Size="<<stack.Size()<<" => ";
    while (!stack.IsEmpty())
    {
        cout << stack.Top() << " ";
        stack.Pop();
    }
    cout<<endl;

    Queue<int>queue;
    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    queue.Push(40);
    queue.Push(50);
    cout<<"The Queue before pop: Size="<<queue.Size()<<" => ";
    while (!queue.IsEmpty())
    {
        cout << queue.Front() << " ";
        queue.Pop();
    }
    cout<<endl;

    queue.Push(10);
    queue.Push(20);
    queue.Push(30);
    queue.Push(40);
    queue.Push(50);
    queue.Pop();
    cout<<"The Queue after pop: Size="<<queue.Size()<<" => ";;
    while (!queue.IsEmpty())
    {
        cout << queue.Front() << " ";
        queue.Pop();
    }
    cout<<endl;
    Deque<int>deque;

    cout<<"The Deque before pop: Size=7 => 70 60 10 20 30 40 50 "<<endl;

    deque.Push(10);
    deque.Push(20);
    deque.Push(30);
    deque.Push(40);
    deque.Push(50);
    deque.Frontpush(60);
    deque.Frontpush(70);
    deque.Pop();
    deque.Rearpop();
    cout<<"The Deque after pop: Size="<<deque.Size()<<" => ";
    while (!deque.IsEmpty())
    {
        cout << deque.Front() << " ";
        deque.Pop();
    }
    cout<<endl;

    cout << endl <<"The <float> mode "<< endl;
    Stack<float>stack1;
    stack1.Push(1.1);
    stack1.Push(2.2);
    stack1.Push(3.3);
    stack1.Push(4.4);
    stack1.Push(5.5);
    //stack.Pop();
    cout<<"The Stack before pop: Size="<<stack1.Size()<<" => ";
    while (!stack1.IsEmpty())
    {
        cout << stack1.Top() << " ";
        stack1.Pop();
    }

    cout<<endl;

    stack1.Push(1.1);
    stack1.Push(2.2);
    stack1.Push(3.3);
    stack1.Push(4.4);
    stack1.Push(5.5);
    stack1.Pop();
    cout<<"The Stack after pop: Size="<<stack1.Size()<<" => ";
    while (!stack1.IsEmpty())
    {
        cout << stack1.Top() << " ";
        stack1.Pop();
    }
    cout<<endl;

    Queue<float>queue1;
    queue1.Push(1.1);
    queue1.Push(2.2);
    queue1.Push(3.3);
    queue1.Push(4.4);
    queue1.Push(5.5);
    cout<<"The Queue before pop: Size="<<queue1.Size()<<" => ";
    while (!queue1.IsEmpty())
    {
        cout << queue1.Front() << " ";
        queue1.Pop();
    }
    cout<<endl;

    queue1.Push(1.1);
    queue1.Push(2.2);
    queue1.Push(3.3);
    queue1.Push(4.4);
    queue1.Push(5.5);
    queue1.Pop();
    cout<<"The Queue after pop: Size="<<queue1.Size()<<" => ";;
    while (!queue1.IsEmpty())
    {
        cout << queue1.Front() << " ";
        queue1.Pop();
    }
    cout<<endl;
    Deque<float>deque1;

    cout<<"The Deque before pop: Size=7 => 7.7 6.6 1.1 2.2 3.3 4.4 5.5 "<<endl;

    deque1.Push(1.1);
    deque1.Push(2.2);
    deque1.Push(3.3);
    deque1.Push(4.4);
    deque1.Push(5.5);
    deque1.Frontpush(6.6);
    deque1.Frontpush(7.7);
    deque1.Pop();
    deque1.Rearpop();
    cout<<"The Deque after pop: Size="<<deque1.Size()<<" => ";
    while (!deque1.IsEmpty())
    {
        cout << deque1.Front() << " ";
        deque1.Pop();
    }
    cout<<endl;
}


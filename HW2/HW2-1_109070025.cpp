#include <iostream>

using namespace std;

int count;
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
    int Size();
    int Capacity();
    void mergeQueue(Queue<int>& Queue1,Queue<int>& Queue2);
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
template<class T>
int Queue<T>::Size()
{
    return (rear-front+capacity)%capacity;
}
template<class T>
int Queue<T>::Capacity()
{
    return capacity;
}
template<class T>
void Queue<T>::mergeQueue(Queue<int>& Queue1,Queue<int>& Queue2)
{
    Queue<int> Queuetemp;
    while (!Queue1.IsEmpty()&&!Queue2.IsEmpty())
    {
        Queuetemp.Push(Queue1.Front());
        Queue1.Pop();
        Queuetemp.Push(Queue2.Front());
        Queue2.Pop();
    }
    while (!Queue1.IsEmpty()&&Queue2.IsEmpty())
    {
        Queuetemp.Push(Queue1.Front());
        Queue1.Pop();
    }
    while (Queue1.IsEmpty()&&!Queue2.IsEmpty())
    {
        Queuetemp.Push(Queue2.Front());
        Queue2.Pop();
    }
    while (!Queuetemp.IsEmpty())
    {
        Queue1.Push(Queuetemp.Front());
        Queuetemp.Pop();
    }
}

int main()
{
    Queue<int> Queue1;
    Queue<int> p;

    Queue1.Push(1);
    Queue1.Push(2);
    Queue1.Push(3);
    Queue1.Push(4);
    Queue1.Push(5);
    Queue1.Push(6);
    Queue1.Push(7);
    Queue1.Push(8);
    Queue1.Push(9);
    Queue1.Push(10);

    Queue<int> Queue2;
    Queue<int> p1;
    while (!Queue2.IsEmpty())
    {
        cout << Queue2.Front() << " ";
        p1.Push(Queue2.Front());
        Queue2.Pop();
    }
    while (!p1.IsEmpty())
    {
        Queue1.Push(p1.Front());
        p1.Pop();
    }

    Queue2.Push(1);
    Queue2.Push(2);
    Queue2.Push(3);
    Queue2.Push(4);
    Queue2.Push(5);
    Queue2.Push(6);
    Queue2.Push(7);
    Queue2.Push(8);

    cout<<"Queue1 after push = ";
    Queue<int> q;
    while (!Queue1.IsEmpty())
    {
        cout << Queue1.Front() << " ";
        q.Push(Queue1.Front());
        Queue1.Pop();
    }
    while (!q.IsEmpty())
    {
        Queue1.Push(q.Front());
        q.Pop();
    }

    cout<<endl;

    cout<<"Queue2 after push = ";
    Queue<int> s;
    while (!Queue2.IsEmpty())
    {
        cout << Queue2.Front() << " ";
        s.Push(Queue2.Front());
        Queue2.Pop();
    }
    while (!s.IsEmpty())
    {
        Queue2.Push(s.Front());
        s.Pop();
    }

    cout<<endl;

    Queue1.Pop();
    cout<<"Queue1 after pop = ";
    Queue<int> j;
    while (!Queue1.IsEmpty())
    {
        cout << Queue1.Front() << " ";
        j.Push(Queue1.Front());
        Queue1.Pop();
    }
    while (!j.IsEmpty())
    {
        Queue1.Push(j.Front());
        j.Pop();
    }
    cout<<"\n";
    cout<<"The front of Queue1 = "<<Queue1.Front()<<endl;
    cout<<"The rear of Queue1 = "<<Queue1.Rear()<<endl;
    cout<<"Whether Queue1 is empty = "<<Queue1.IsEmpty()<<endl;
    cout<<"The size of Queue1 = "<<Queue1.Size()<<endl;
    cout<<"The capacity of Queue1 = "<<Queue1.Capacity()<<endl;
    cout<<"The size of Queue2 = "<<Queue2.Size()<<endl;
    cout<<"The capacity of Queue2 = "<<Queue2.Capacity()<<endl;
    cout<<"After merge Queue1 and Queue2 = ";
    Queue1.mergeQueue(Queue1,Queue2);
    while (!Queue1.IsEmpty())
    {
        cout << Queue1.Front() << " ";
        Queue1.Pop();
    }
    cout<<endl;

    return 0;
}

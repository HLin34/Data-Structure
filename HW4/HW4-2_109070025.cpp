#include <iostream>
using namespace std;

template<class T>
class MinPQ
{
public:
    virtual ~MinPQ() {};
    virtual bool IsEmpty()const = 0;
    virtual const T& Top()const = 0;
    virtual void Push(const T &x) = 0;
    virtual void Pop() = 0;
};

template<class T>
class MinHeap : public MinPQ<T>
{
public:
    MinHeap(int theCapacity = 10);
    bool IsEmpty() const;
    const T& Top() const;
    void Push(const T& x);
    void Pop();
    void ChangeSize(T* &a, const int oldSize, const int newSize);

private:
    T *heap;
    int heapSize;
    int capacity;
};

template<class T>
MinHeap<T> :: MinHeap(int theCapacity)
{
    capacity = theCapacity;
    heapSize = 0;
    heap = new T[capacity+1];
}

template<class T>
void MinHeap<T> :: ChangeSize(T* &a, const int oldSize, const int newSize)
{
    T *temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a+1, a + number+1, temp+1);
    delete []a;
    a = temp;
}

template<class T>
bool MinHeap<T> :: IsEmpty() const
{
    if(heapSize == 0) return true;
    else return false;
}

template<class T>
const T& MinHeap<T> :: Top()const
{
    return this->heap[1];
}

template<class T>
void MinHeap<T> :: Pop()
{
    heap[1].~T();
    T lastE = heap[heapSize--];
    int currentNode = 1, child = 2;
    while (child <= heapSize)
    {
        if (child < heapSize && heap[child] > heap[child+1]) child++;
        if(lastE <= heap[child]) break;
        heap[currentNode] = heap[child];
        currentNode = child;
        child *= 2;
    }
    heap[currentNode] = lastE;
}

template<class T>
void MinHeap<T> :: Push(const T &x)
{
    if (heapSize == capacity)
    {
        ChangeSize(heap, capacity, 2*capacity);
        capacity *= 2;
    }
    int currentNode = ++heapSize;
    while(currentNode != 1 && heap[currentNode/2] > x)
    {
        heap[currentNode] = heap[currentNode/2];
        currentNode /=2;
    }
    heap[currentNode] = x;
}

template<class T>
class MaxPQ{
    public:
        virtual ~MaxPQ(){};
        virtual bool IsEmpty()const = 0;
        virtual const T& Top()const = 0;
        virtual void Push(const T &x) = 0;
        virtual void Pop() = 0;
};

template<class T>
class MaxHeap:public MinPQ<T>{
    public:
        MaxHeap(int theCapacity = 10);
        bool IsEmpty() const;
        const T& Top() const;
        void Push(const T& x);
        void Pop();
        void ChangeSize(T* &a, const int oldSize, const int newSize);

    private:
        T *heap;
        int heapSize;
        int capacity;
};
template<class T>
MaxHeap<T>::MaxHeap(int theCapacity){
    capacity = theCapacity;
    heapSize = 0;
    heap = new T[capacity+1];
}
template<class T>
void MaxHeap<T>::ChangeSize(T* &a, const int oldSize, const int newSize){
    T *temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a+1, a + number+1, temp+1);
    delete []a;
    a = temp;
}
template<class T>
bool MaxHeap<T>::IsEmpty() const{
    if(heapSize == 0) return true;
    else return false;
}
template<class T>
const T& MaxHeap<T>::Top()const{
    return this->heap[1];
}
template<class T>
void MaxHeap<T>::Push(const T &x){
    if(heapSize == capacity){
        ChangeSize(heap, capacity, 2*capacity);
        capacity*=2;
    }
    int currentNode =++heapSize;
    while(currentNode!=1 && heap[currentNode/2]<x){
        heap[currentNode]=heap[currentNode/2];
        currentNode/=2;
    }
    heap[currentNode]=x;
}
template<class T>
void MaxHeap<T>::Pop(){
    heap[1].~T();
    T lastE = heap[heapSize--];
    int currentNode = 1, child = 2;
    while (child <= heapSize) {
        if (child < heapSize && heap[child] < heap[child+1]) child++;
        if(lastE >= heap[child]) break;
        heap[currentNode] = heap[child];
        currentNode = child;
        child *= 2;
    }
    heap[currentNode] = lastE;
}

int main()
{
    MaxHeap<int> m;
    cout << "Push the element into the MaxHeap." << endl;
    cout << " elements : 50, 5, 30, 40, 80, 35, 2, 20, 15, 60, 70, 8, 10" << endl;
    m.Push(50);
    m.Push(5);
    m.Push(30);
    m.Push(40);
    m.Push(80);
    m.Push(35);
    m.Push(2);
    m.Push(20);
    m.Push(15);
    m.Push(60);
    m.Push(70);
    m.Push(8);
    m.Push(10);
    cout << "Whether MaxHeap is Empty: " << m.IsEmpty() << endl;
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Min in the MaxHeap : " << m.Top() << endl << "Pop the element in MaxHeap." << endl;
    m.Pop();
    cout << "Whether MaxHeap is Empty : " << m.IsEmpty() << endl << endl ;

    MinHeap<int> m1;
    cout << "Push the element into the MinHeap." << endl;
    cout << " elements : 50, 5, 30, 40, 80, 35, 2, 20, 15, 60, 70, 8, 10" << endl;
    m1.Push(50);
    m1.Push(5);
    m1.Push(30);
    m1.Push(40);
    m1.Push(80);
    m1.Push(35);
    m1.Push(2);
    m1.Push(20);
    m1.Push(15);
    m1.Push(60);
    m1.Push(70);
    m1.Push(8);
    m1.Push(10);
    cout << "Whether MinHeap is Empty: " << m1.IsEmpty() << endl;
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Min in the MinHeap : " << m1.Top() << endl << "Pop the element in MinHeap." << endl;
    m1.Pop();
    cout << "Whether MinHeap is Empty : " << m1.IsEmpty() << endl ;
    return 0;
}

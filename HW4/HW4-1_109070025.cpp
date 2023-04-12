#include <iostream>

using namespace std;

template <class T> class BinaryTree;

// Queue
template <class T>
class Queue
{
    friend class BinaryTree<T>;
public:
    Queue (int queueCapacity = 10);
    T& Front() const;
    bool IsEmpty() const;
    void Push(T &x);
    void Pop();
private:
    T *queue;
    int front, rear, capacity;
};

template <class T>
Queue<T> :: Queue(int queueCapacity)
{
    capacity = queueCapacity;
    rear = 0;
    front = 0;
    queue = new T[capacity];
}

template <class T>
inline bool Queue<T> :: IsEmpty() const
{
    return (front == rear);
}

template <class T>
inline  T& Queue<T> :: Front() const
{
    return queue[(front + 1) % capacity];
}

template <class T>
void Queue<T> :: Push(T &x)
{
    int start = (front + 1) % capacity;
    if (((rear + 1)%capacity) == front)
    {
        T* NewQueue = new T[2*capacity];
        if (start < 2) copy(queue + start, queue + start + capacity - 1, NewQueue);
        else
        {
            copy(queue + start, queue + capacity, NewQueue);
            copy(queue, queue + rear + 1, NewQueue + capacity - start);
        }
        front = 2*capacity - 1;
        rear = capacity - 2;
        capacity *= 2;
        delete []queue;
        queue = NewQueue;
    }
    rear = (rear + 1) % capacity;
    queue[rear] = x;
}

template <class T>
void Queue<T> :: Pop()
{
    front = (front + 1) % capacity;
    queue[front].~T();
}

//Stack
template <class T>
class Stack
{
public:
    Stack(int stackCapactiy = 10);
    bool IsEmpty() const;
    T Top() const;
    void Pop();
    void Push(T x);
    void ChangeSize(T* &a, const int oldSize, const int NewSize);
private:
    T *array;
    int capacity;
    int top;
};

template <class T>
Stack<T> :: Stack(int stackCapacity)
{
    capacity = stackCapacity;
    array = new T[capacity];
    top = -1;
}

template <class T>
bool Stack<T> :: IsEmpty() const
{
    if (top == -1) return true;
    else return false;
}

template <class T>
void Stack<T> :: Push(T x)
{
    if (capacity == (top + 1))
    {
        ChangeSize(array, capacity, 2*capacity);
        capacity *= 2;
    }
    array[++top] = x;
}

template <class T>
void Stack<T> :: ChangeSize(T* &a, const int oldSize, const int NewSize)
{
    T *temp = new T[NewSize];
    int number = min(oldSize, NewSize);
    copy(a, a + number, temp);
    delete []a;
    a = temp;
}

template <class T>
T Stack<T> :: Top() const
{
    return this->array[this->top];
}

template <class T>
void Stack<T> :: Pop()
{
    this->top--;
}

// TreeNode
template <class T>
class TreeNode
{
    friend class BinaryTree<T>;
public:
    TreeNode(TreeNode<T> *a, T item, TreeNode<T> *b);
private:
    T data;
    TreeNode<T> *leftchild;
    TreeNode<T> *rightchild;
};

template<class T>
TreeNode<T> :: TreeNode(TreeNode<T> *a, T item, TreeNode<T> *b)
{
    data = item;
    leftchild = a;
    rightchild = b;
}

// Binary Tree
template <class T>
class BinaryTree
{
public:
    BinaryTree();
    BinaryTree(const BinaryTree<T> &bt1);
    TreeNode<T>* Copy(TreeNode<T> *origNode);
    ~BinaryTree();
    bool IsEmpty();
    BinaryTree(const BinaryTree<T> &bt1,const T &item, const BinaryTree<T> &bt2);
    BinaryTree<T> LeftSubtree();
    BinaryTree<T> RightSubtree();
    T RootData();
    void Inorder();
    void Inorder(TreeNode<T> *p);
    void Preorder();
    void Preorder(TreeNode<T> *p);
    void Postorder();
    void Postorder(TreeNode<T> *p);
    void Visit(TreeNode<T> *p);
    void NoStackInorder();
    void LevelOrder();
    void NonrecInorder();
    void Set_one();
    void Set_two();
    bool operator==(const BinaryTree<T> &t)const;
    bool check(TreeNode<T> *p, TreeNode<T> *q)const;
private:
    TreeNode<T> *root;
};

template<class T>
BinaryTree<T> :: BinaryTree()
{
    root = 0;
}

template<class T>
BinaryTree<T> :: BinaryTree(const BinaryTree<T> &bt1)
{
    root = Copy(bt1.root);
}

template<class T>
TreeNode<T>* BinaryTree<T> :: Copy(TreeNode<T> *origNode)
{
    if (!origNode) return 0;
    return new TreeNode<T>(Copy(origNode->leftchild), origNode->data, Copy(origNode->rightchild));
}

template<class T>
BinaryTree<T> :: ~BinaryTree()
{
    root = 0;
}

template<class T>
bool BinaryTree<T> :: IsEmpty()
{
    if (root) return false;
    else return true;
}

template<class T>
BinaryTree<T> :: BinaryTree(const BinaryTree<T> &bt1, const T &item, const BinaryTree<T> &bt2)
{
    root = new TreeNode<T>(bt1.root, item, bt2.root);
}

template<class T>
BinaryTree<T> BinaryTree<T> :: LeftSubtree()
{
    BinaryTree<T> bt;
    bt.root = new TreeNode<T>(root->leftchild->leftchild, root->leftchild->data, root->leftchild->rightchild);
    return bt;
}

template<class T>
BinaryTree<T> BinaryTree<T> :: RightSubtree()
{
    BinaryTree<T> bt;
    bt.root = new TreeNode<T>(root->rightchild->leftchild, root->rightchild->data, root->rightchild->rightchild);
    return bt;
}

template<class T>
T BinaryTree<T> :: RootData()
{
    return root->data;
}

template<class T>
void BinaryTree<T> :: Inorder()
{
    Inorder(root);
}

template<class T>
void BinaryTree<T> :: Inorder(TreeNode<T> *p)
{
    if(p)
    {
        Inorder(p->leftchild);
        Visit(p);
        Inorder(p->rightchild);
    }
}

template<class T>
void BinaryTree<T> :: Preorder()
{
    Preorder(root);
}

template<class T>
void BinaryTree<T> :: Preorder(TreeNode<T> *p)
{
    if(p)
    {
        Visit(p);
        Preorder(p->leftchild);
        Preorder(p->rightchild);
    }
}

template<class T>
void BinaryTree<T> :: Postorder()
{
    Postorder(root);
}

template<class T>
void BinaryTree<T> :: Postorder(TreeNode<T> *p)
{
    if(p)
    {
        Postorder(p->leftchild);
        Postorder(p->rightchild);
        Visit(p);
    }
}

template<class T>
void BinaryTree<T> :: NonrecInorder()
{
    Stack<TreeNode<T>*> s;
    TreeNode<T> *currentNode = root;
    while(1)
    {
        while(currentNode)
        {
            s.Push(currentNode);
            currentNode = currentNode->leftchild;
        }
        if(s.IsEmpty()) return;
        currentNode = s.Top();
        s.Pop();
        Visit(currentNode);
        currentNode = currentNode->rightchild;
    }
}

template<class T>
void BinaryTree<T> :: Visit(TreeNode<T> *p)
{
    cout << p->data;
}

template<class T>
void BinaryTree<T> :: LevelOrder()
{
    Queue<TreeNode<T>*> q;
    TreeNode<T> *currentNode = root;
    while(currentNode)
    {
        Visit(currentNode);
        if(currentNode->leftchild) q.Push(currentNode->leftchild);
        if(currentNode->rightchild) q.Push(currentNode->rightchild);
        if(q.IsEmpty()) return;
        currentNode = q.Front();
        q.Pop();
    }
}

template<class T>
void BinaryTree<T> :: NoStackInorder()
{
    if (!root) return;
    TreeNode<T> *top = 0, *lastright = 0, *p, *q, *r, *r1;
    q = root;
    p = q;
    while(1)
    {
        while(1)
        {
            if ((!p->leftchild) && (!p->rightchild))
            {
                Visit(p);
                break;
            }
            if (!p->leftchild)
            {
                Visit(p);
                r = p->rightchild;
                p->rightchild = q;
                q = p;
                p = r;
            }
            else
            {
                r = p->leftchild;
                p->leftchild = q;
                q = p;
                p = r;
            }
        }
        TreeNode<T> *av = p;
        while(1)
        {
            if (p == root) return;
            if(!q->leftchild)
            {
                r = q->rightchild;
                q->rightchild = p;
                p = q;
                q = r;
            }
            else if(!q->rightchild)
            {
                r = q->leftchild;
                q->leftchild = p;
                p = q;
                q = r;
                Visit(p);
            }
            else
            {
                if (q == lastright)
                {
                    r = top;
                    lastright = r->leftchild;
                    top = r->rightchild;
                    r->leftchild = 0;
                    r->rightchild = 0;
                    r = q->rightchild;
                    q->rightchild = p;
                    p = q;
                    q = r;
                }
                else
                {
                    Visit(q);
                    av->leftchild = lastright;
                    av->rightchild = top;
                    top = av;
                    lastright = q;
                    r = q->leftchild;
                    q->leftchild = p;
                    r1 = q->rightchild;
                    q->rightchild = r;
                    p = r1;
                    break;
                }
            }
        }
    }
}

template<class T>
void BinaryTree<T> :: Set_one()
{
    TreeNode<T> *current;
    root = new TreeNode<T>(new TreeNode<T>(new TreeNode<T>(0,'*',new TreeNode<T>(0,'C',0)),'*',new TreeNode<T>(0,'D',0)),'+', new TreeNode<T>(0, 'E', 0));
    current = root->leftchild->leftchild;
    current->leftchild = new TreeNode<T>(new TreeNode<T>(0,'A',0),'-',new TreeNode<T>(0,'B',0));
}

template<class T>
void BinaryTree<T> :: Set_two()
{
    TreeNode<T> *current;
    root = new TreeNode<T>(new TreeNode<T>(0, 'B', new TreeNode<T>(0,'E',0)), 'A', new TreeNode<T>(new TreeNode<T>(0,'F',0), 'C', new TreeNode<T>(0,'G',0)));
    current = root->leftchild;
    current->leftchild = new TreeNode<T>(new TreeNode<T>(0,'H',0), 'D', new TreeNode<T>(0,'J',0));
}

template<class T>
bool BinaryTree<T> :: operator==(const BinaryTree<T> &t)const
{
    if (root->data != t.root->data) return false;
    else return (true && check(root->leftchild, t.root->leftchild) && check(root->rightchild, t.root->rightchild));
}

template<class T>
bool BinaryTree<T> :: check(TreeNode<T> *p, TreeNode<T> *q) const
{
    if (p == 0 && q == 0) return true;
    else if(p->data != q->data) return false;
    else return (true && check(p->leftchild, q->leftchild) && check(p->rightchild, q->rightchild));
}

int main()
{
    BinaryTree<char> bt1, bt2, bt3, bt4;
    bt1.Set_one();
    cout << " Set up binart tree named Binary_Tree_one : " << endl;
    cout << " Whether Binary_Tree_one  is empty : " << bt1.IsEmpty() << endl;
    cout << " Inorder of Binary_Tree_one : ";
    bt1.Inorder();
    cout << endl;
    cout << " The Preorder of Binary_Tree_one : ";
    bt1.Preorder();
    cout << endl;
    cout << " Postorder of Binary_Tree_one : ";
    bt1.Postorder();
    cout << endl;
    cout << " Levelorder of Binary_Tree_one : ";
    bt1.LevelOrder();
    cout << endl;
    cout << " NonrecInorder of Binary_Tree_one : ";
    bt1.NonrecInorder();
    cout << endl;
    cout << " NoStackInorder of Binary_Tree_one : ";
    bt1.NoStackInorder();
    cout << endl;
    cout << " Root data of Binary_Tree_one : " << bt1.RootData() << endl<<endl;

    bt2.Set_two();
    cout << " Set up binary tree named Binary_Tree_two." << endl ;
    cout << " Whether Binary_Tree_two is empty : " << bt2.IsEmpty() << endl;
    cout << " Inorder of Binary_Tree_two : ";
    bt2.Inorder();
    cout << endl;
    cout << " Preorder of Binary_Tree_two : ";
    bt2.Preorder();
    cout << endl;
    cout << " Postorder of Binary_Tree_two : ";
    bt2.Postorder();
    cout << endl;
    cout << " Levelorder of Binary_Tree_two : ";
    bt2.LevelOrder();
    cout << endl;
    cout << " NonrecInorder of Binary_Tree_two : ";
    bt2.NonrecInorder();
    cout << endl;
    cout << " NoStackInorder of Binary_Tree_two : ";
    bt2.NoStackInorder();
    cout << endl;
    cout << " Root data of Binary_Tree_two: " << bt2.RootData() << endl;
    cout << " Whether Binary_Tree_one == Binary_Tree_two : " << bt1.operator==(bt2) << endl<<endl;

    cout << " Set Binary_Tree_three is LeftSubtree of Binary_Tree_one and Binary_Tree_four is RightSubtree of Binary_Tree_two" << endl;
    bt3 = bt1.LeftSubtree();
    bt4 = bt2.RightSubtree();
    cout << " Inorder of Binary_Tree_three : ";
    bt3.Inorder();
    cout << endl << " Inorder of Binary_Tree_four : ";
    bt4.Inorder();
    cout << endl << endl;
    cout << " Set Binary_Tree_five, which leftsubtree as Binary_Tree_three and rightsubtree is Binary_Tree_four with the root data is 'X'." << endl;
    BinaryTree<char> bt5(bt3, 'X', bt4);
    cout << " Inorder of Binary_Tree_five: ";
    bt5.Inorder();
    cout << endl << endl;
    cout << " Use copy constuctor to make Binary_Tree_six copy Binary_Tree_one." << endl;
    cout << " Inorder of Binary_Tree_six : ";
    BinaryTree<char> bt6(bt1);
    bt6.Inorder();
    cout << endl;

    return 0;
}

#include<iostream>
#include<fstream>

using namespace std;

struct Offsets
{
    int di, dj;
};

enum directions
{
    N, NE, E, SE, S, SW, W, NW
};

struct Items
{
    int x, y, dir;
};

template <class T>
class Stack
{
    public:
        Stack(int stackCapacity = 10);
        ~Stack();
        bool IsEmpty() const;
        T& Top() const;
        void Push(const T& item);
        void Pop();
        void ChangeSize1D(T*& a, const int oldSize, const int newSize);
        friend ostream &operator<<(ostream &output, Items& item);
        template <class C>
        friend ostream &operator<<(ostream &output, Stack<C> &Sta);

    private:
        T* stack;
        int top;
        int capacity;
};

template <class T>
Stack<T>::Stack(int stackCapacity):capacity(stackCapacity)
{
    if (capacity < 1) throw "Capacity must be > 0";
    stack = new T[capacity];
    top = -1; // indicate empty stack
}

template <class T>
Stack<T>::~Stack()
{
    delete [] stack;
}

template <class T>
inline bool Stack<T>::IsEmpty() const
{
    return top == -1;
}

template <class T>
T& Stack<T>::Top() const
{
    if ( IsEmpty() ) throw "Stack is empty";
    return stack[top];
}

template <class T>
void Stack<T>::Push(const T& x)
{  // add x to stack
    if (top == capacity - 1) {
        ChangeSize1D(stack, capacity, 2 * capacity);
        capacity *=2;
    }
    stack[++top] = x;
}

template <class T>
void Stack<T>::Pop()
{
    if ( IsEmpty() ) throw "Stack is Empty. Cannot delete";
    stack[top--].~T(); //destructor for T
}

template <class T>
void Stack<T>::ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
    if (newSize < 0) throw "New length must be >= 0";
    T* temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);

    delete [] a;
    a = temp;
}


ostream &operator<<(ostream &output, Items& item)
{
    return output << item.x << ", " << item.y << ", " << item.dir;
}

template <class T>
ostream &operator<<(ostream &output, Stack<T> &Sta)
{
    output << endl << "Total times = " << Sta.top << endl << endl;
    output << "The action each time made : " << endl;
    for (int i = 0; i <= Sta.top; i++)
        output << i << " => " << Sta.stack[i] << endl;

    return output;
}

void Path(const int m, const int p)
{
    int i,  j;
    int mark[m+2][p+2], maze[m + 2][p + 2];

    ifstream file;
    file.open("C:\\Users\\allue\\Desktop\\My_program\\Data_Structure\\maze.txt");

    file >> i >> j;

    //define mark
    for (int i = 0; i < m + 2; i++)
        for (int j = 0; j < p + 2; j++)
            mark[i][j] = 0;

    //define maze
    for (int i = 0; i < m + 2; i++)
    {
        maze[i][0] = 1;
        maze[i][p + 1] = 1;
    }

    for (int i = 0; i < p + 2; i++)
    {
        maze[0][i] = 1;
        maze[m + 1][i] = 1;
    }

    for (int i = 1; i < m + 1; i++)
        for (int j = 1; j < p + 1; j++)
            file >> maze[i][j];


    file.close();

    Offsets move[8];

    move[N].di = -1;
    move[N].dj = 0;

    move[NE].di = -1;
    move[NE].dj = 1;

    move[E].di = 0;
    move[E].dj = 1;

    move[SE].di = 1;
    move[SE].dj = 1;

    move[S].di = 1;
    move[S].dj = 0;

    move[SW].di = 1;
    move[SW].dj = -1;

    move[W].di = 0;
    move[W].dj = -1;

    move[NW].di = -1;
    move[NW].dj = -1;

    mark[1][1] = 1; //start

    // initialize a stack, and add the starting point
    Stack<Items> stack(m * p);
    Items temp;
    temp.x = 1;
    temp.y = 1;
    temp.dir = E;
    stack.Push(temp);

    // start finding
    while (!stack.IsEmpty())
    {
        temp = stack.Top();
        cout << "Pop: " << temp << endl;
        stack.Pop();
         i = temp.x;
         j = temp.y;
        int dir = temp.dir;

        while (dir < 8) // 8 ways of direction
        {
            int g = i + move[dir].di;
            int h = j + move[dir].dj;

            if ((g == m) && (h == p)) //success
            {
                cout << stack <<endl;
                cout << "The final position is : ("<< i << ", " << j << ")" << endl;
                cout << "The exit is : ("<< m << ", " << p << ")" << endl;
                return;
            }
            if ((!maze[g][h]) && (!mark[g][h])) {
                mark[g][h] = 1;
                temp.x = i;
                temp.y = j;
                temp.dir = dir;
                stack.Push(temp); //prepare for a dead end
                cout << "Push: "<< temp << endl;
                // move to (g, h), start from N
                i = g;
                j = h;
                dir = N;
            }
            else dir++;
        }
    }
    cout << "No path in maze." << endl;
}

int main()
{
    ifstream file;
    file.open("C:\\Users\\allue\\Desktop\\My_program\\Data_Structure\\maze.txt");

    int rows, cols;
    file >> rows >> cols;
    file.close();

    cout << "The trace out action is below : " << endl << endl;
    Path(rows, cols);

    return 0;
}

#include <iostream>

using namespace std;

struct Triple
{
    int row;
    int col;
    int value;
};

class Matrix;

istream& operator>> (istream&, Matrix&);
ostream& operator<< (ostream&, Matrix&);

class MatrixNode
{
friend class Matrix;
friend istream& operator>> (istream&, Matrix&);
friend ostream& operator<< (ostream&, Matrix&);
private:
    MatrixNode* down;
    MatrixNode* right;
    bool head;
    union {
        MatrixNode* next;
        Triple triple;
    };
    MatrixNode(bool, Triple*);
};

MatrixNode::MatrixNode(bool b, Triple* t)
{
    head = b;
    if (b)
    {
        right = down = this;
        next = this;
    }
    else
        triple = *t;
}

class Matrix
{
friend istream& operator>> (istream&, Matrix&);
friend ostream& operator<< (ostream&, Matrix&);
private:
    static MatrixNode* av;
public:
    ~Matrix();
    Matrix operator+ (const Matrix& b) const;
    Matrix operator* (const Matrix& b) const;
    Matrix Transpose() const;
private:
    MatrixNode* headnode;
};

MatrixNode* Matrix::av = 0;

Matrix::~Matrix()
{
    if (!headnode)
        return;
    MatrixNode* x = headnode->right;

    headnode->right = av;
    av = headnode;

    while (x != headnode)
    {
        MatrixNode* y = x->right;
        x->right = av;
        av = y;
        x = x->next;
    }

    headnode = 0;
}

Matrix Matrix::Transpose() const
{
    Matrix m;
    m.headnode = new MatrixNode(false, &headnode->triple);
    int size = max(headnode->triple.row, headnode->triple.col);
    MatrixNode** heads = new MatrixNode* [size];
    for (int i = 0; i < size; i++)
        heads[i] = new MatrixNode(true, 0);

    int rowSize = headnode->triple.col;
    int colSize = headnode->triple.row;
    MatrixNode* head = headnode->right;
    for (int i = 0; i < rowSize; i++)
    {
        MatrixNode* last = heads[i];
        MatrixNode* temp = head->down;
        while (temp != head)
        {
            Triple t = { temp->triple.col, temp->triple.row, temp->triple.value };
            MatrixNode* newNode = new MatrixNode(false, &t);
            last = last->right = newNode;
            heads[t.col]->next = heads[t.col]->next->down = newNode;
            temp = temp->down;
        }
        last->right = heads[i];
        head = head->next;
    }

    for (int i = 0; i < colSize; i++)
        heads[i]->next->down = heads[i];
    for (int i = 0; i < size - 1; i++)
        heads[i]->next = heads[i + 1];
    heads[size - 1]->next = m.headnode;
    m.headnode->right = heads[0];

    delete[] heads;
    return m;
}

Matrix Matrix::operator* (const Matrix& b) const
{
    Matrix m;
    m.headnode = new MatrixNode(false, &headnode->triple);
    m.headnode->triple.col = headnode->triple.row;
    int rowSize = headnode->triple.row;
    int colSize = headnode->triple.col;
    int size = max(rowSize, colSize);

    MatrixNode** heads = new MatrixNode* [size];
    for(int i = 0; i < size; i++)
        heads[i] = new MatrixNode(true, 0);

    for (MatrixNode* heada = headnode->right; heada != headnode; heada = heada->next)
    {
        if (heada->right == heada) continue;
        MatrixNode* last = heads[heada->right->triple.row];
        for (MatrixNode* headb = b.headnode->right; headb != b.headnode; headb = headb->next)
        {
            if (headb->right == headb)  continue;
            int sum = 0;
            MatrixNode* tempA = heada->right;
            MatrixNode* tempB = headb->down;
            Triple t = { tempA->triple.row, tempB->triple.col, 0 };
            while (tempB != headb && tempA != heada)
            {
                if (tempA->triple.col < tempB->triple.row)
                    tempA = tempA->right;
                else if (tempA->triple.col > tempB->triple.row)
                    tempB = tempB->down;
                else
                {
                    sum += tempA->triple.value * tempB->triple.value;
                    tempA = tempA->right;
                    tempB = tempB->down;
                }
            }
            if (sum)
            {
                t.value = sum;
                MatrixNode* newNode = new MatrixNode(false, &t);
                heads[t.col]->next = heads[t.col]->next->down = newNode;
                last = last->right = newNode;
            }
        }
        last->right = heads[last->triple.row];
    }
    for (int i = 0; i < colSize; i++)
        heads[i]->next->down = heads[i];
    for (int i = 0; i < size - 1; i++)
        heads[i]->next = heads[i + 1];
    heads[size - 1]->next = m.headnode;
    m.headnode->right = heads[0];
    delete[] heads;
    return m;
}

Matrix Matrix::operator+ (const Matrix& b) const
{
    Matrix m;
    if (headnode->triple.row != b.headnode->triple.row ||
        headnode->triple.col != b.headnode->triple.col)
        return m;

    m.headnode = new MatrixNode(false, &headnode->triple);
    int size = max(headnode->triple.row, headnode->triple.col);
    int rowSize = headnode->triple.row;
    int colSize = headnode->triple.col;
    MatrixNode** heads = new MatrixNode* [size];
    for (int i = 0; i < size; i++)
        heads[i] = new MatrixNode(true, 0);

    MatrixNode* tempa = headnode->right;
    MatrixNode* tempb = b.headnode->right;

    int count = 0;
    for (int i = 0; i < rowSize; i++)
    {
        MatrixNode* last = heads[i];
        MatrixNode* terma = tempa->right;
        MatrixNode* termb = tempb->right;
        while (terma != tempa && termb != tempb)
        {
            Triple t;
            if (terma->triple.col == termb->triple.col)
            {
                t = { i, terma->triple.col, terma->triple.value + termb->triple.value };
                terma = terma->right;
                termb = termb->right;
            }
            else if (terma->triple.col < termb->triple.col)
            {
                t = { i, terma->triple.col, terma->triple.value };
                terma = terma->right;
            }
            else
            {
                t = { i, termb->triple.col, termb->triple.value };
                termb = termb->right;
            }
            count++;
            MatrixNode* newNode = new MatrixNode(false, &t);
            last = last->right = newNode;
            heads[t.col]->next = heads[t.col]->next->down = newNode;
        }
        while (terma != tempa)
        {
            Triple t = { i, terma->triple.col, terma->triple.value };
            count++;
            MatrixNode* newNode = new MatrixNode(false, &t);
            last = last->right = newNode;
            heads[t.col]->next = heads[t.col]->next->down = newNode;
            terma = terma->right;
        }
        while (termb != tempb)
        {
            Triple t = { i, termb->triple.col, termb->triple.value };
            count++;
            MatrixNode* newNode = new MatrixNode(false, &t);
            last = last->right = newNode;
            heads[t.col]->next = heads[t.col]->next->down = newNode;
            termb = termb->right;
        }
        last->right = heads[i];
        tempa = tempa->next;
        tempb = tempb->next;
    }
    for (int i = 0; i < colSize; i++)
        heads[i]->next->down = heads[i];
    for (int i = 0; i < size - 1; i++)
        heads[i]->next = heads[i + 1];
    heads[size - 1]->next = m.headnode;
    m.headnode->right = heads[0];
    m.headnode->triple.value = count;

    delete[] heads;
    return m;
}

ostream& operator<< (ostream& os, const Triple& vec)
{
    return os << vec.row << " " << vec.col << " " << vec.value;
}

istream& operator>> (istream& is, Matrix& matrix)
{
    Triple s;
    is >> s.col >> s.row >> s.value;
    int p = max(s.row, s.col);

    matrix.headnode = new MatrixNode(false, &s);
    if (p == 0)
    {
        matrix.headnode->right = matrix.headnode;
        return is;
    }

    MatrixNode** head = new MatrixNode* [p];
    for (int i = 0; i < p; i++)
        head[i] = new MatrixNode(true, 0);
    int currentRow = 0;
    MatrixNode* last = head[0];
    for (int i = 0; i < s.value; i++)
    {
        Triple t;
        is >> t.row >> t.col >> t.value;
        if (t.row > currentRow)
        {
            last->right = head[currentRow];
            currentRow = t.row;
            last = head[currentRow];
        }

        last = last->right = new MatrixNode(false, &t);
        head[t.col]->next = head[t.col]->next->down = last;
    }

    last->right = head[currentRow];
    for (int i = 0; i < s.col; i++)
        head[i]->next->down = head[i];
    for (int i = 0; i < p - 1; i++)
        head[i]->next = head[i + 1];
    head[p - 1]->next = matrix.headnode;
    matrix.headnode->right = head[0];
    delete[] head;
    return is;
}

ostream& operator<< (ostream& os, Matrix& matrix)
{
    MatrixNode* head = matrix.headnode;
    int rowSize = head->triple.row;
    head = matrix.headnode->right;
    for (int i = 0; i < rowSize; i++)
    {
        MatrixNode* temp = head->right;
        while (temp != head)
        {
            os << temp->triple << endl;
            temp = temp->right;
        }
        head = head->next;
    }

    return os << "\n";
}

int main()
{
    Matrix m1, m2;
    cout << "Enter matrix 1: "<< endl;
    cin >> m1;
    cout << "Enter matrix 2: "<< endl;
    cin >> m2;
    Matrix m3 = m1 + m2;
    cout << endl << "The sum of two matrix: "<<endl;
    cout << m3;
    Matrix m4 = m1.Transpose();
    cout << "The transpose of matrix 1: "<<endl;
    cout << m4;
    Matrix m5 = m1 * m2;
    cout << "The result of multiplying two matrix: "<<endl;
    cout << m5;
}

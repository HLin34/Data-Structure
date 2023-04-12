#include <iostream>

using namespace std;

struct Node
{
    double  coef;
    int     exp;
    Node*   link;
};

class Polynomial
{
public:
    Polynomial();
    Polynomial(const Polynomial& a);
    ~Polynomial();

    const Polynomial& operator= (const Polynomial& a);

    Polynomial operator+(const Polynomial&);
    Polynomial operator-(const Polynomial&);
    Polynomial operator*(const Polynomial&);
    double Evaluate(double x) const;
private:
    Node* GetNode();
    void RetNode(Node*& x);
private:
    Node* first;
    Node* av;
friend istream& operator>> (istream& is, Polynomial& x);
friend ostream& operator<< (ostream& os, Polynomial& x);
};

Polynomial::Polynomial()
    : av(0)
{
    first = GetNode();
    first->link = first;
}


Polynomial::Polynomial(const Polynomial& a)
    : av(0)
{
    first = GetNode();
    Node* newNode = first;
    newNode->link = first;
    Node* temp = a.first->link;
    while (temp != a.first)
    {
        newNode->link = GetNode();
        newNode = newNode->link;
        newNode->coef = temp->coef;
        newNode->exp = temp->exp;
        temp = temp->link;
    }
    newNode->link = first;
}

Polynomial::~Polynomial()
{
    av = 0;
}

const Polynomial& Polynomial::operator= (const Polynomial& a)
{
    this->~Polynomial();
    first = GetNode();
    Node* newNode = first;
    newNode->link = first;
    Node* temp = a.first->link;
    while (temp != a.first)
    {
        newNode->link = GetNode();
        newNode = newNode->link;
        newNode->coef = temp->coef;
        newNode->exp = temp->exp;
        temp = temp->link;
    }
    newNode->link = first;
    return *this;
}

double Polynomial::Evaluate(double x) const
{
    int maxExp;
    if (first->link == first)
        return 0;
    else
        maxExp = first->link->exp;

    Node* temp = first->link;
    double value = 0;
    for (int i = maxExp; i >= 0; i--)
    {
        value *= x;
        if (temp != first && temp->exp == i)
        {
            value += temp->coef;
            temp = temp->link;
        }
    }

    return value;
}

Node* Polynomial::GetNode()
{
    Node* x;
    if (av)
    {
        x = av;
        av = av->link;
    }
    else
        x = new Node;

    return x;
}

void Polynomial::RetNode(Node*& x)
{
    x->link = av;
    av = x;
    x = 0;
}

Polynomial Polynomial::operator+(const Polynomial& b)
{
    Polynomial poly;
    Node* tempa = first->link;
    Node* tempb = b.first->link;
    Node* temp  = poly.first;
    while (tempa != first && tempb != b.first)
    {
        temp->link = GetNode();
        temp = temp->link;
        if (tempa->exp == tempb->exp)
        {
            temp->exp = tempa->exp;
            temp->coef = tempa->coef + tempb->coef;
            tempa = tempa->link;
            tempb = tempb->link;
        }
        else if (tempa->exp > tempb->exp)
        {
            temp->exp = tempa->exp;
            temp->coef = tempa->coef;
            tempa = tempa->link;
        }
        else
        {
            temp->exp = tempb->exp;
            temp->coef = tempb->coef;
            tempb = tempb->link;
        }
    }
    while (tempa != first)
    {
        temp->link = GetNode();
        temp = temp->link;
        temp->coef = tempa->coef;
        temp->exp = tempa->exp;
        tempa = tempa->link;
    }
    while (tempb != b.first)
    {
        temp->link = GetNode();
        temp = temp->link;
        temp->coef = tempb->coef;
        temp->exp = tempb->exp;
        tempb = tempb->link;
    }
    temp->link = poly.first;

    return poly;
}

Polynomial Polynomial::operator-(const Polynomial& b)
{
    Polynomial poly;
    poly.first = poly.GetNode();
    Node* tempa = first->link;
    Node* tempb = b.first->link;
    Node* temp = poly.first;
    while (tempa != first && tempb != b.first)
    {
        temp->link = GetNode();
        temp = temp->link;
        if (tempa->exp == tempb->exp)
        {
            temp->exp = tempa->exp;
            temp->coef = tempa->coef - tempb->coef;
            tempa = tempa->link;
            tempb = tempb->link;
        }
        else if (tempa->exp > tempb->exp)
        {
            temp->exp = tempa->exp;
            temp->coef = -tempa->coef;
            tempa = tempa->link;
        }
        else
        {
            temp->exp = tempb->exp;
            temp->coef = -tempb->coef;
            tempb = tempb->link;
        }
    }
    while (tempa != first)
    {
        temp->link = GetNode();
        temp = temp->link;
        temp->coef = -tempa->coef;
        temp->exp = tempa->exp;
        tempa = tempa->link;
    }
    while (tempb != b.first)
    {
        temp->link = GetNode();
        temp = temp->link;
        temp->coef = -tempb->coef;
        temp->exp = tempb->exp;
        tempb = tempb->link;
    }
    temp->link = poly.first;

    return poly;
}

Polynomial Polynomial::operator*(const Polynomial& b)
{
    Polynomial poly;
    if (first->link == first || b.first->link == b.first)
        return poly;
    int maxExp = first->link->exp + b.first->link->exp;
    double* Coef = new double[maxExp + 1];
    for (int i = 0; i < maxExp + 1; i++)
        Coef[i] = 0.0;
    for (Node* tempa = first->link; tempa != first; tempa = tempa->link)
        for (Node* tempb = b.first->link; tempb != b.first; tempb = tempb->link)
            Coef[tempa->exp + tempb->exp] += tempa->coef * tempb->coef;

    Node* temp = poly.first;
    for (int i = maxExp; i >= 0; i--)
    {
        if (Coef[i] != 0.0)
        {
            temp->link = poly.GetNode();
            temp = temp->link;
            temp->coef = Coef[i];
            temp->exp = i;
        }
    }
    temp->link = poly.first;
    delete[] Coef;
    return poly;
}

istream& operator>>(istream& is, Polynomial& x)
{
    x.~Polynomial();
    x.first = x.GetNode();
    x.first->link = x.first;
    Node* temp = x.first;

    int n = 0;
    is >> n;

    while (n--)
    {
        temp->link = x.GetNode();
        is >> temp->link->coef;
        is >> temp->link->exp;
        temp = temp->link;
    }
    temp->link = x.first;

    return is;
}

ostream& operator<< (ostream& os, Polynomial& x)
{
    Node* temp = x.first->link;
    while (temp != x.first)
    {
        os << temp->coef << " " << temp->exp << " ";
        temp = temp->link;
    }
    return os << "\n";
}

int main()
{
    Polynomial p1;
    cout << "Enter the number of the nonzero items of polynomial, then enter their coef & exp: " << endl;
    cin >> p1;
    Polynomial p2 = p1;
    cout << "Copy a same polynoimal as enter:  ";
    cout << p2;
    cout << "Evalute the quality use 5: ";
    cout << p1.Evaluate(5) << endl;
    Polynomial p3 = p1 + p2;
    cout << "Add two polynomial: ";
    cout << p3;
    Polynomial p4 = p1 - p2;
    cout << "Subtract two polynomial: ";
    cout << p4;
    Polynomial p5;
    cout << "Multiply two polynomial: ";
    p5 = p1 * p2;
    cout << p5;
    cout << "Evaluate the multiplied polynomial using 3: ";
    cout << p5.Evaluate(3) << endl;

    return 0;
}

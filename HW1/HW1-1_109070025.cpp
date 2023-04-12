#include<iostream>

using namespace std;

class Polynomial; //forward declaration

class Term
{
    friend Polynomial;
    friend istream &operator>>(istream &input, Polynomial &Poly);
    friend ostream &operator<<(ostream &output, Polynomial &Poly);
private:
    int exp;
    float coef;

};

class Polynomial
{
// p(x) = a0 x^e0 + ¡K + an x^en
// where ai is nonzero float and ei is non-negative int

    friend istream &operator>>(istream &input, Polynomial &Poly);
    friend ostream &operator<<(ostream &output, Polynomial &Poly);

public:
    Polynomial( )
    {
        terms = 0;
        capacity = terms + 5;
        termArray = new Term[capacity];
    };
    //construct the polynomial p(x) = 0
    ~Polynomial() {};
    //destruct the polynomial p(x) = 0
    Polynomial Add(Polynomial poly);
    //return the sum of *this and poly
    Polynomial Mult(Polynomial poly);
    //return the product of *this and poly
    void NewTerm(const float theCoef, const int thExp);
    //make sure the capacity is large enough
    float Eval(float f );
    //Evaluate the polynomial *this at f and return the results
    int operator!();
    // if *this is the zero polynomial, return 1; else return 0;
    float Coef(float e);
    // return the coefficient of e in *this
    int LeadExp();
    // return the largest exponent in *this

private:
    Term *termArray;
    int terms;
    int capacity;
};

istream &operator>>(istream &input, Polynomial &Poly)
{

    cout << "Enter the nonzero terms of the polynomial: ";
    input >> Poly.terms;
    cout << "Enter the capacity of the polynomial : ";
    input >> Poly.capacity;
    if (Poly.terms > Poly.capacity )
    {
        cout << "There must be something wrong about the polynomial !!! "<<endl;
        exit(1);
    }
    Poly.termArray = new Term[Poly.capacity];
    cout << "Enter the coefficient and exponent of the polynomial:" << endl;
    for (int i = 0; i < Poly.terms; i++)
        input >> Poly.termArray[i].coef >> Poly.termArray[i].exp;

    return input;
}

ostream &operator<<(ostream &output, Polynomial &Poly)
{
    for ( int i = 0; i < Poly.terms; i++)
    {
        if (i == 0)
        {
            if (Poly.termArray[i].coef != -1 && (Poly.termArray[i].coef < 0))
                output << " - " << -Poly.termArray[i].coef;
            else if (Poly.termArray[i].coef != 1 && (Poly.termArray[i].coef > 0))
                output << Poly.termArray[i].coef;
            else
                output << " - ";
        }
        else if (Poly.termArray[i].coef > 0)
        {
            if (Poly.termArray[i].coef != 1)
                output << " + " << Poly.termArray[i].coef;
            else if (Poly.termArray[i].exp == 0)
                output << " + 1";
            else
                output << " + ";
        }
        else
        {
            if (Poly.termArray[i].coef != -1 && (Poly.termArray[i].coef < 0))
                output << " - " << -Poly.termArray[i].coef;
            else if (Poly.termArray[i].exp == 0)
                output << " - 1";
            else
                output << " - ";
        }
        if (Poly.termArray[i].exp != 0)
            output <<"x^" << Poly.termArray[i].exp;
    }

    return output;
}

Polynomial Polynomial::Add(Polynomial Poly)
{
    Polynomial c;
    int apos = 0;
    int bpos = 0;

    while ((apos < terms) && (bpos < Poly.terms))
    {
        if (termArray[apos].exp == Poly.termArray[bpos].exp)
        {
            float t = termArray[apos].coef + Poly.termArray[bpos].coef;
            if (t != 0)
                c.NewTerm(t, termArray[apos].exp);
            apos++;
            bpos++;
        }
        else if (termArray[apos].exp < Poly.termArray[bpos].exp)
        {
            c.NewTerm(Poly.termArray[bpos].coef, Poly.termArray[bpos].exp);
            bpos++;
        }
        else
        {
            c.NewTerm(termArray[apos].coef, termArray[apos].exp);
            apos++;
        }
    }
    for (; apos < terms; apos++)
        c.NewTerm(termArray[apos].coef, termArray[apos].exp);
    for (; bpos < Poly.terms; bpos++)
        c.NewTerm(Poly.termArray[bpos].coef, Poly.termArray[bpos].exp);

    return c;
}

Polynomial Polynomial::Mult(Polynomial Poly)
{
    Polynomial x;
    Polynomial y;

    for (int i = 0; i < terms; i++)
    {
        for (int j = 0; j < Poly.terms; j++)
            x.NewTerm(termArray[i].coef * Poly.termArray[j].coef, termArray[i].exp + Poly.termArray[j].exp);
    }

    for (int i = 0; i < x.terms; i++)
    {
        int j = i;
        for (int k = i + 1; k < x.terms; k++)
        {
            if ((x.termArray[k].exp == x.termArray[j].exp) && (x.termArray[j].coef != 0))
            {
                x.termArray[j].coef += x.termArray[k].coef;
                x.termArray[k].coef = 0;
            }
        }
    }

    for (int i = 0; i < x.terms; i++)
    {
        if (x.termArray[i].coef != 0)
        {
            y.NewTerm(x.termArray[i].coef, x.termArray[i].exp);
        }
    }
    delete [] x.termArray;

    return y;
}

void Polynomial::NewTerm(const float theCoef, const int theExp)
{
    if (terms == capacity) //termArray is full
    {
        capacity *= 2;
        Term *temp = new Term[capacity];
        copy(termArray, termArray + terms, temp);
        delete [] termArray;
        termArray = temp;
    }

    termArray[terms].coef = theCoef;
    termArray[terms++].exp = theExp;
}

float Polynomial::Eval(float f)
{
    float mult;
    float sum = 0;

    for (int i = 0; i < terms; i++)
    {
        mult = termArray[i].coef;
        for (int j = 0; j < termArray[i].exp; j++)
            mult *= f;

        sum += mult;
    }

    return sum;
}

int Polynomial::operator!()
{

    for (int i = 0; i < terms; i++)
    {
        if(termArray[i].coef != 0)
            return 0;
    }

    return 1;
}

float Polynomial::Coef(float e)
{
    for (int i = 0; i < terms; i++)
    {
        if (termArray[i].exp == e)
        {
            return termArray[i].coef;
        }
    }
    return -1;
}

int Polynomial::LeadExp()
{
    return termArray[0].exp;
}


int main()
{
    Polynomial poly_A, poly_B, poly_add, poly_mult;
    float Eval_num, Eval_result;
    int time;

    cout << "Enter the total times of execution: ";
    cin >> time;

    for(int i = 0; i<time; i++)
    {
        cin >> poly_A;
        cin >> poly_B;
        cout << "The number that would like to evaluate: " ;
        cin >> Eval_num;

        poly_add = poly_A.Add(poly_B);
        poly_mult = poly_A.Mult(poly_B);
        Eval_result = poly_A.Eval(Eval_num);

        cout << endl;
        cout << "The result of addition: " <<  poly_add << endl << endl;
        cout << "The result of Multiplication: " << poly_mult << endl << endl;
        cout << "The result of Evaluation of " << Eval_num << " from " << poly_A <<": " << Eval_result << endl;

        poly_A.~Polynomial();
        poly_B.~Polynomial();
        poly_add.~Polynomial();
        poly_mult.~Polynomial();

        if( i != time-1 )
            cout<< endl << "=============================" << endl << endl;
        else
            cout << endl << "The end of the execution."<<endl;
    }

    return 0;
}

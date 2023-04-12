#include<iostream>
#include<iomanip>

using namespace std;

class SparseMatrix; // forward declaration

class MatrixTerm
{
    friend SparseMatrix;
    friend istream &operator>>(istream &input, SparseMatrix &Matrix);
    friend ostream &operator<<(ostream &output, SparseMatrix &Matrix);

private:
    int row, col, value; // a triple representing a term
};

class SparseMatrix
{
    // a triple representing a term, row, col are non-negative integer and value is also a integer
    friend istream &operator>>(istream &input, SparseMatrix &Matrix);
    friend ostream &operator<<(ostream &output, SparseMatrix &Matrix);

public:
    SparseMatrix(int r, int c, int t);
    //constructor.
    //r is #row, c is #col, t is #non-zero terms
    SparseMatrix Add(SparseMatrix b);
    // same row and col => add, or throw to exception
    SparseMatrix Multiply(SparseMatrix b);
    // if col of *this is the same as row of b => d= *this & b
    // d[i][j]=£U(a[i][k]¡Db[k][j]¡C
    // the range of k is 0 to col of *this-1, or throw to the exception
    SparseMatrix FastTranspose( );
    //return *this exchange its row and col value to SparseMatrix
    void ChangeSize1D(const int newSize);
    //change the array size to newSize
    void StoreSum(const int sum, const int r, const int c);

private:
    int rows, cols, terms, capacity;
    MatrixTerm *smArray;
};

istream &operator>>(istream &input, SparseMatrix &Matrix)
{

    int value[Matrix.rows][Matrix.cols];

    cout << "Enter the amount of rows: ";
    input >> Matrix.rows;
    cout << "Enter the amount of columns: ";
    input >> Matrix.cols;
    cout << "Enter the amount of nonzero terms: ";
    input >> Matrix.terms;
    cout << "Enter the SparseMatrix: " << endl;
    int current = 0;
    for (int i = 0; i < Matrix.rows; i++)
    {
        for (int j = 0; j < Matrix.cols; j++)
        {
            input >> value[i][j];
            if (value[i][j] != 0)
            {
                Matrix.smArray[current].row = i;
                Matrix.smArray[current].col = j;
                Matrix.smArray[current].value = value[i][j];
                current++;
            }
        }
    }

    return input;
}

ostream &operator<<(ostream &output, SparseMatrix &Matrix)
{
    int current = 0;

    output << "The SparseMatrix: " << endl;
    for (int i = 0; i < Matrix.rows; i++)
    {
        for (int j = 0; j < Matrix.cols; j++)
        {
            if ((Matrix.smArray[current].row == i) && (Matrix.smArray[current].col == j))
                output << setw(5) << Matrix.smArray[current++].value;
            else
                output << setw(5) << " 0";
        }
        output << endl;
    }

    return output;
}

SparseMatrix::SparseMatrix(int r, int c, int t)
{
    cols = c;
    rows = r;
    terms = t;
    capacity = terms + 5;
    smArray = new MatrixTerm[capacity];
}

SparseMatrix SparseMatrix::Add(SparseMatrix b)
{
    if ((cols != b.cols) || (rows != b.rows))
        throw " incapable matrices";

    int start = 0;
    int apos = 0;
    int bpos = 0;
    SparseMatrix c(rows, cols, terms + b.terms);

    while((apos < terms) && (bpos < b.terms))
    {
        if (smArray[apos].row == b.smArray[bpos].row)
        {
            if (smArray[apos].col == b.smArray[bpos].col)
            {
                c.smArray[start].value = smArray[apos].value + b.smArray[bpos].value;
                c.smArray[start].col = smArray[apos].col;
                c.smArray[start].row = smArray[apos].row;
                start++;
                apos++;
                bpos++;
            }
            else if (smArray[apos].col < b.smArray[bpos].col)
            {
                c.smArray[start].value = smArray[apos].value;
                c.smArray[start].col = smArray[apos].col;
                c.smArray[start].row = smArray[apos].row;
                apos++;
                start++;
            }
            else
            {
                c.smArray[start].value = b.smArray[bpos].value;
                c.smArray[start].col = b.smArray[bpos].col;
                c.smArray[start].row = b.smArray[bpos].row;
                bpos++;
                start++;
            }
        }
        else if (smArray[apos].row < b.smArray[bpos].row)
        {
            c.smArray[start].value = smArray[apos].value;
            c.smArray[start].col = smArray[apos].col;
            c.smArray[start].row = smArray[apos].row;
            apos++;
            start++;

        }
        else if (smArray[apos].row > b.smArray[bpos].row)
        {
            c.smArray[start].value = b.smArray[bpos].value;
            c.smArray[start].col = b.smArray[bpos].col;
            c.smArray[start].row = b.smArray[bpos].row;
            bpos++;
            start++;
        }
    }
    for (; apos < terms; apos++)
    {
        c.smArray[start].value = smArray[apos].value;
        c.smArray[start].col = smArray[apos].col;
        c.smArray[start].row = smArray[apos].row;
        start++;
    }
    for (; bpos < b.terms; bpos++)
    {
        c.smArray[start].value = b.smArray[bpos].value;
        c.smArray[start].col = b.smArray[bpos].col;
        c.smArray[start].row = b.smArray[bpos].row;
        start++;
    }

    return c;
}


SparseMatrix SparseMatrix::Multiply(SparseMatrix b)
{
    if (cols != b.rows) // error handling
        throw "Incompatible Matrices";

    SparseMatrix bXpose = b.FastTranspose();  // transpose b
    SparseMatrix d(rows, b.cols, 0);  // create the output matrix d
    int currRowIndex = 0;
    int currRowBegin = 0;
    int currRowA = smArray[0].row;

    // introduce dummy terms for handling boundary condition
    if (terms == capacity)
        ChangeSize1D(terms + 1);

    // introduce dummy terms for handling boundary condition
    bXpose.ChangeSize1D(bXpose.terms + 1);
    smArray[terms].row = rows;
    bXpose.smArray[b.terms].row = b.cols;
    bXpose.smArray[b.terms].col = -1;

    int sum = 0;
    while (currRowIndex < terms)
    {
        // check currRowA is valid
        int currColB = bXpose.smArray[0].row;
        int currColIndex = 0;
        while (currColIndex <= b.terms)
        {
            // process B matrix term by term
            if (smArray[currRowIndex].row != currRowA)
            {
                //row end
                d.StoreSum(sum, currRowA, currColB); // store the sum
                sum = 0;  // reset the sum
                currRowIndex = currRowBegin;  // rewind the row
                while (bXpose.smArray[currColIndex].row == currColB)
                    currColIndex++;   // skip terms in the curr col

                currColB = bXpose.smArray[currColIndex].row;  //next col
            }
            else if (bXpose.smArray[currColIndex].row != currColB)
            {
                // col end
                d.StoreSum(sum, currRowA, currColB); //output the sum
                sum = 0; // reset the sum
                currRowIndex = currRowBegin; //rewind the row
                currColB = bXpose.smArray[currColIndex].row; //next col
            }
            else
            {
                if (smArray[currRowIndex].col < bXpose.smArray[currColIndex].col)
                    currRowIndex++;
                else if (smArray[currRowIndex].col == bXpose.smArray[currColIndex].col)
                {
                    sum += smArray[currRowIndex].value * bXpose.smArray[currColIndex].value;
                    currRowIndex++;
                    currColIndex++;
                }
                else
                    currColIndex++;
            }  // end of it-else if-else
        }  // end of the inner while ( currColIndex <= b.term )
        while (smArray[currRowIndex].row == currRowA)
            currRowIndex++;   //skip terms in the curr col

        currRowBegin = currRowIndex;  //next row
        currRowA = smArray[currRowIndex].row; //next row
    }   // end of the outer while ( currColIndex < terms )

    return d;
}

SparseMatrix SparseMatrix::FastTranspose( )
{
    SparseMatrix b(cols, rows, terms);
    if (terms > 0)
    {
        int *rowSize = new int[cols];
        int *rowStart = new int[cols];

        //calculate the row size of the new matrix
        fill(rowSize, rowSize + cols, 0);
        for (int i = 0 ; i < terms ; i++)
            rowSize[smArray[i].col]++;

        //calculate the starting array index of each row of the new matrix
        rowStart[0] = 0;
        for (int i = 1 ; i < cols ; i++)
            rowStart[i] = rowStart[i-1] + rowSize[i-1];
        for (int i = 0 ; i < terms ; i++)
        {
            int j = rowStart[smArray[i].col];
            b.smArray[j].row= smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            rowStart[smArray[i].col]++;
        } //end of for

        delete [] rowSize;
        delete [] rowStart;
    }//end of if

    return b;
}

void SparseMatrix::ChangeSize1D(const int newSize)
{
    // change the array size to newsize
    if (newSize < terms)
        throw"New size must be >= number of terms";

    MatrixTerm *temp = new MatrixTerm[newSize];
    // new array

    copy(smArray, smArray+terms, temp);
    delete [] smArray;

    smArray = temp;
    // make smArray point to the newly created array
    capacity = newSize;
}

void SparseMatrix::StoreSum(const int sum, const int r, const int c)
{
    if (sum != 0)
    {
        if (terms == capacity)
        {
            ChangeSize1D(2 * capacity);
        }
        smArray[terms].row = r;
        smArray[terms].col = c;
        smArray[terms++].value  = sum;
    }
}

int main()
{
    SparseMatrix Matrix_A(0,0,0);
    SparseMatrix Matrix_B(0,0,0);
    SparseMatrix Matrix_add(0,0,0);
    SparseMatrix Matrix_mult(0,0,0);
    SparseMatrix Matrix_trans(0,0,0);
    int time;

    cout << "Enter the total times of the execution: ";
    cin >> time;

    for (int i=0; i<time; i++ )
    {
        cin >> Matrix_A;
        cin >> Matrix_B;
        Matrix_add = Matrix_A.Add(Matrix_B);
        Matrix_mult = Matrix_A.Multiply(Matrix_B);
        Matrix_trans = Matrix_A.FastTranspose();

        cout << endl;
        cout << "The result of addition: " << endl << Matrix_add << endl;
        cout << "The result of Multiplication: " << endl << Matrix_mult  << endl;
        cout << "The transpose of " << Matrix_A <<"is below :" << endl << Matrix_trans << endl;

        Matrix_A.~SparseMatrix();
        Matrix_B.~SparseMatrix();
        Matrix_add.~SparseMatrix();
        Matrix_mult.~SparseMatrix();
        Matrix_trans.~SparseMatrix();

        if( i != time-1 )
            cout<< endl << "=============================" << endl << endl;
        else
            cout << endl << "The end of the execution."<<endl;
    }


    return 0;
}

#include <iostream>

#define MAX_DISTANCE 11050
#define CANT_REACH -1

using namespace std;

class MatrixWDigraph
{
public:
    MatrixWDigraph(int s);
    void SetUpA_1();
    void SetUpA_2();
    void SetUpA_3();
    void SetUpB_1();
    void SetUpB_2();
    void SetUpC();

    void ShortestPath(const int n, const int v);
    void BellmanFord(const int n, const int v);
    void AllLengths(const int n);
private:
    int Choose(int u);

    void print_dist(int n);
    void print_path(int n);
    void print_a();
private:
    int**   length;
    int**   a;
    int*    p;
    int*    dist;
    int     size;
    bool*   s;
};

MatrixWDigraph::MatrixWDigraph(int Size)
{
    size = Size;
    length = new int*[size];
    for (int n = 0; n < size; n++)
        length[n] = new int[size];


    a = new int*[size];
    for (int n = 0; n < size; n++)
        a[n] = new int[size];

    dist = new int[size];
    s = new bool[size];
    p = new int[size];
}

void MatrixWDigraph::SetUpA_1()
{
    for (int n = 0; n < size; n++)
        for (int m = 0; m < size; m++)
            length[n][m] = MAX_DISTANCE;
    length[2][1] = 800;
    length[1][0] = 300;
    length[7][0] = 1700;
    length[2][0] = 1000;
    length[3][2] = 1200;
    length[5][3] = 1000;
    length[4][3] = 1500;
    length[5][7] = 1400;
    length[6][7] = 1000;
    length[4][5] = 250;
    length[5][6] = 900;
}

void MatrixWDigraph::SetUpA_2()
{
    for (int n = 0; n < size; n++)
        for (int m = 0; m < size; m++)
            length[n][m] = 11050;
    length[0][1] = 50;
    length[0][2] = 45;
    length[0][3] = 10;
    length[1][2] = 10;
    length[1][3] = 15;
    length[2][4] = 30;
    length[3][0] = 20;
    length[3][4] = 15;
    length[4][1] = 20;
    length[4][2] = 35;
    length[5][4] = 3;
}

void MatrixWDigraph::SetUpA_3()
{
    for (int n = 0; n < size; n++)
        for (int m = 0; m < size; m++)
            length[n][m] = 11050;
    length[0][1] = 20;
    length[0][2] = 15;
    length[1][0] = 2;
    length[1][4] = 10;
    length[1][5] = 30;
    length[2][3] = 4;
    length[2][5] = 10;
    length[4][3] = 15;
    length[5][3] = 4;
    length[5][4] = 10;
}

void MatrixWDigraph::SetUpB_1()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            length[i][j] = MAX_DISTANCE;
    length[0][1] =  6;
    length[0][2] =  5;
    length[0][3] =  5;
    length[1][4] = -1;
    length[2][1] = -2;
    length[2][4] =  1;
    length[3][2] = -2;
    length[3][5] = -1;
    length[4][6] =  3;
    length[5][3] =  3;
}

void MatrixWDigraph::SetUpB_2()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            length[i][j] = MAX_DISTANCE;
    length[0][1] =  7;
    length[1][2] =  -5;
    length[0][2] =  5;
}

void MatrixWDigraph::SetUpC()
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            length[i][j] = i == j ? 0 : MAX_DISTANCE;
    length[0][1] =  4;
    length[0][2] = 11;
    length[1][2] =  2;
    length[1][0] =  6;
    length[2][0] =  3;
}

void MatrixWDigraph::ShortestPath(const int n, const int v)
{
    cout << "Vertex:  ";
    for (int i = 0; i < n; i++)
        cout << "    [" << i << "]";
    cout << endl;
    for (int i = 0; i < n; i++)
    {
        s[i] = false;
        dist[i] = length[v][i];
        p[i] = dist[i] == MAX_DISTANCE ? -1 : v;
    }
    p[v] = CANT_REACH;
    s[v] = true;
    dist[v] = 0;
    cout << "Select " << v << ": ";
    print_dist(n);

    for (int i = 0; i < n - 2; i++)
    {
        int u = Choose(n);
        s[u] = true;
        for (int w = 0; w < n; w++)
            if (!s[w] && dist[u] + length[u][w] < dist[w])
            {
                dist[w] = dist[u] + length[u][w];
                p[w] = u;
            }
        cout << "Select " << u << ": ";
        print_dist(n);
    }

    for (int i = 0; i < n; i++)
    {
        cout << "path: ";
        print_path(i);
        cout << "length: ";
        if (dist[i] == MAX_DISTANCE)
            cout << "Inf" << endl;
        else
            cout << dist[i] << endl;
    }
}

void MatrixWDigraph::print_dist(int n)
{
    for (int i = 0; i < n; i++)
    {
        if (dist[i] == MAX_DISTANCE)
            cout << "   Inf";
        else
        {
            int space = 1;
            for (int value = dist[i]; value >= 10; value /= 10)
                space++;
            space = 6 - space;
            while (space--)
                cout << " ";
            cout << dist[i];
        }
        cout  << " ";
    }
    cout << endl;
}

void MatrixWDigraph::print_path(int n)
{
    if (n == CANT_REACH)
        return;
    print_path(p[n]);
    cout << n << " ";
}

int MatrixWDigraph::Choose(int u)
{
    int v = 0;
    for (int i = 0; i < u; i++)
        if (!s[i])
        {
            v = i;
            break;
        }

    for (int i = v + 1; i < u; i++)
        if (!s[i] && dist[i] < dist[v])
            v = i;
    return v;
}

void MatrixWDigraph::BellmanFord(const int n, const int v)
{
    cout << "Vertex:";
    for (int i = 0; i < n; i++)
        cout << "    [" << i << "]";
    cout << endl;
    for (int i = 0; i < n; i++)
        dist[i] = length[v][i];
    dist[v] = 0;
    for (int k = 2; k <= n - 1; k++)
    {
        cout << "dist^" << k - 1 << ": ";
        print_dist(n);
        for (int u = 0; u < n; u++)
        {
            if (u == v)
                continue;
            for (int i = 0; i < n; i++)
            {
                if (length[i][u] == MAX_DISTANCE)
                    continue;
                if (dist[u] > dist[i] + length[i][u])
                    dist[u] = dist[i] + length[i][u];
            }
        }
    }
    cout << "dist^" << n - 1 << ": ";
    print_dist(n);
}

void MatrixWDigraph::AllLengths(const int n)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            a[i][j] = length[i][j];
    for (int k = 0; k < n; k++)
    {
        cout << "A^" << k - 1 << "[][]: " << endl;
        print_a();
        cout << endl;
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if ((a[i][k] + a[k][j]) < a[i][j])
                    a[i][j] = a[i][k] + a[k][j];
    }
    cout << "A^" << n - 1 << "[][]: " << endl;
    print_a();
}

void MatrixWDigraph::print_a()
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (a[i][j] == MAX_DISTANCE)
                cout << "Infinity";
            else
                cout << a[i][j];
            cout << " ";
        }
        cout << endl;
    }
}

int main()
{
    MatrixWDigraph G1_1(8);
    G1_1.SetUpA_1();
    cout << "G1.ShortestPath(8, 4):" << endl;
    G1_1.ShortestPath(8, 4);
    cout << endl;
    MatrixWDigraph G1_2(6);
    G1_2.SetUpA_2();
    cout << "G1'.ShortestPath(6, 0):" << endl;
    G1_2.ShortestPath(6, 0);
    cout << endl;
    MatrixWDigraph G1_3(6);
    G1_3.SetUpA_3();
    cout << "G1''.ShortestPath(6, 0):" << endl;
    G1_3.ShortestPath(6, 0);
    cout << endl;

    MatrixWDigraph G2_1(7);
    G2_1.SetUpB_1();
    cout << "G2.BellmanFord(7, 0):" << endl;
    G2_1.BellmanFord(7, 0);
    cout << endl;
    MatrixWDigraph G2_2(3);
    G2_2.SetUpB_2();
    cout << "G2'.BellmanFord(3, 0):" << endl;
    G2_2.BellmanFord(3, 0);
    cout << endl;

    MatrixWDigraph G3(3);
    G3.SetUpC();
    cout << "G3.AllLengths(3):" << endl;
    G3.AllLengths(3);
}

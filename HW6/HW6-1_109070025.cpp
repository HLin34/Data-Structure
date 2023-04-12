#include <iostream>
#include <array>
#include <vector>

using namespace std;

template <class T>
void Print(T* a, int n)
{
    for (int k = 1; k < n; k++)
        cout << a[k] << " ";
    cout << endl;
}

template <class T>
void InsertionSort(T* a, const int n)
{
    for (int j = 2; j <= n; j++)
    {
        a[0] = a[j];
        int i = j - 1;
        for (; a[i] > a[0]; i--)
            a[i + 1] = a[i];
        a[i + 1] = a[0];
    }
}

template <class T>
void QuickSort(T* a, const int left, const int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        int b, c, d;
        int median;

        if (a[left] < a[right])
            { b = left; c = right; }
        else
            { b = right; c = left; }
        if (a[mid] > a[c])
            d = c;
        else
            d = mid;
        if (a[b] > a[d])
            median = b;
        else
            median = d;

        swap(a[left],   a[median]);
        T& pivot = a[left];
        int i = left - 1;
        int j = right + 1;
        do
        {
            do j--; while (a[j] > pivot);
            do i++; while (a[i] <= pivot);
            if (i < j) swap(a[i], a[j]);
        } while (i < j);
        swap(pivot, a[j]);
        QuickSort(a, left, j-1);
        QuickSort(a, j + 1, right);
    }
}

template <class T>
void Merge(T* a, T* b, const int k, const int m, const int n)
{
    int i1 = k, i2 = m + 1, i3 = k;
    for (; i1 <= m && i2 <= n; i3++)
        if (a[i1] <= a[i2])
        {
            b[i3] = a[i1];
            i1++;
        }
        else
        {
            b[i3] = a[i2];
            i2++;
        }
    if (i2 > n)
        copy(a + i1, a + m + 1, b + i3);
    if (i1 > m)
        copy(a + i2, a + n + 1, b + i3);
}

template <class T>
void MergePass(T* a, T* b, const int n, const int s)
{
    int i;
    for (i = 1; i <= n - (2 * s) + 1; i += 2 * s)
        Merge(a, b, i, i + s - 1, i + (2 * s) - 1);
    if ((i + s - 1) < n)
        Merge(a, b, i, i + s - 1, n);
    else
        copy(a + i, a + n + 1, b + i);
}

template <class T>
void MergeSort(T* a, const int n)
{
    T* tempList = new T[n + 1];

    for (int s = 1; s < n; s *= 2)
    {
        MergePass(a, tempList, n, s);
        s *= 2;
        MergePass(tempList, a, n, s);
    }
    delete [] tempList;
}

template <class T>
int ListMerge(T* a, int* link, const int start1, const int start2)
{
    int iResult = 0;
    int i1 = start1, i2 = start2;
    for (; i1 && i2; )
        if (a[i1] <= a[i2])
        {
            link[iResult] = i1;
            iResult = i1;
            i1 = link[i1];
        }
        else
        {
            link[iResult] = i2;
            iResult = i2;
            i2 = link[i2];
        }

    if (i1 == 0)
        link[iResult] = i2;
    else
        link[iResult] = i1;
    return link[0];
}

template <class T>
int rMergeSort(T* a, int* link, const int left, const int right)
{
    if (left >= right)
        return left;
    int mid = (left + right) / 2;
    return ListMerge(a, link,
        rMergeSort(a, link, left, mid),
        rMergeSort(a, link, mid + 1, right));
}

template <class T>
void Adjust(T* a, const int root, const int n)
{
    T e = a[root];
    int j;
    for (j = 2 * root; j <= n; j *= 2)
    {
        if (j < n && a[j] < a[j + 1])
            j++;
        if (e >= a[j])
            break;
        a[j / 2] = a[j];
    }
    a[j / 2] = e;
}

template <class T>
void HeapSort(T* a, const int n)
{
    for (int i = n / 2; i >= 1; i--)
    {
        Adjust(a, i, n);
    }
    for (int i = n - 1; i >= 1; i--)
    {
        swap(a[1], a[i + 1]);
        Adjust(a, 1, i);
    }
}


int main()
{
// QuickSort
    cout << " QuickSort : "<< endl;
    cout << " The unsorted characters list :";
    cout << " z g e h x u q m b " << endl;
    cout << " The sorted characters list : ";
    vector<char> b = { 'z', 'g', 'e', 'h', 'x', 'u', 'q', 'm', 'b' };
    QuickSort(b.data(), 1, b.size() - 1);
    Print(b.data(), b.size());

    cout << endl;

// Insertion Sort
    cout << " Insertion Sort : "<< endl;
    cout << " The unsorted integers list :";
    cout << " 0 5 7 8 2 3 5 7 1 16 23 13 10 " << endl;
    cout << " The sorted integers list : ";
    vector<int> a = { 0, 5, 7, 8, 2, 3, 5, 7, 1, 16, 23, 13, 10 };
    InsertionSort(a.data(), a.size() - 1);
    Print(a.data(), a.size());

    cout << endl;

// HeapSort
    cout << " HeapSort : "<< endl;
    cout << " The unsorted floats list :";
    cout << " 2.1 3.4 2.1 4.7 6.3 2.6 7.3 1.2 " << endl;
    cout << " The sorted floats list : ";
    vector<float> c = { 2.1f, 3.4f, 2.1f, 4.7f, 6.3f, 2.6f, 7.3f, 1.2f };
    HeapSort(c.data(), c.size() - 1);
    Print(c.data(), c.size());

    cout << endl;

// rMergeSort
    cout << " Recursive MergeSort : "<< endl;
    cout << " The unsorted objects list :";
    cout << " egg dog apple bag frog hot grass " << endl;
    cout << " The sorted objects list : ";
    vector<string> e = { "0", "egg", "dog", "apple", "bag", "frog", "hot", "grass" };
    int* link = new int[e.size()];
    for (int i = 0; i < e.size(); i++)
        link[i] = 0;

    int index = rMergeSort(e.data(), link, 1, e.size() - 1);

    for (int i = 0; i < e.size() - 1; i++)
    {
        cout << e[index] << " ";
        index = link[index];
    }
    cout << endl;
    delete[] link;

    cout << endl;

    // MergeSort
    cout << " Iterative MergeSort : "<< endl;
    cout << " The unsorted integers list :";
    cout << "  4 2 5 6 1 4 6 2 1 6 5 7 0 " << endl;
    cout << " The sorted integers list : ";
    vector<int> d = { 4, 2, 5, 6, 1, 4, 6, 2, 1, 6, 5, 7, 0 };
    MergeSort(d.data(), d.size() - 1);
    Print(d.data(), d.size());
}

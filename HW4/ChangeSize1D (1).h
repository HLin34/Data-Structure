#pragma once
#include <iostream>
using namespace std;
template<class T>
void ChangeSize1D(T*& a, const int oldSize, const int newSize)
{
    if (newSize < 0)
        throw " Now length must be >= 0";
    T* temp = new T[newSize];
    int number = min(oldSize, newSize);
    copy(a, a + number, temp);
    delete[] a;
    a = temp;
}
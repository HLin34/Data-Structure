#include <iostream>

using namespace std;

class String
{
    friend ostream &operator<<(ostream &output, String &t);

public:
    String(char *init, int m); // constructor using input string init of length m
    bool operator==(String t); // equality test
    bool operator!(); //whether it is empty
    int Length(); // get the number of characters of *this
    int FastFind(String pat);
    // Return an index i such that pat matches the substring of the object begins at position i.
    // Return -1 if pat is empty or not a substring of the object
    int Compare(String y); //compare two strings of letters of alphabet.
    String Concat(String t);  // concatenation with another string t
    String Substr(int i, int j); // generate a substring i~j-1
    String Delete(int start, int length);  //remove length characters beginning at start
    String CharDelete(char c); //returns the string with all occurrence of c removed.

private:
    char *str;
    int length;
    int *f;
};

String::String(char *init = "", int m = 0)
{
    str = new char[m + 1];
    str = init;
    length = m;
}

bool String::operator==(String t)
{
    if (Length() != t.Length())
        return false;
    for (int start= 0; start <= Length() - t.Length(); start++)
    {
        int i;
        for(i = 0; i < t.Length() && str[start + i] == t.str[i]; i++);
        if (i == t.Length())
            return true;
    }

    return false;
}

bool String::operator!()
{

    if (str == NULL)
        return true;
    else
        return false;
}

int String::Length()
{
    int L = 0;

    for (int i = 0; i < length; i++)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= '0' && str[i] <= '9'))
        {
            L++;
            if ((str[i + 1] == ' ') &&  str[i + 2] == ' ')
            {
                return L;
            }
        }
        else if (str[i] == ' ')
        {
            L++;
            if (str[i+1] == ' ')
            {
                L--;
                return L;
            }
        }
    }

    return L;
}

ostream &operator<<(ostream &output, String &t)
{

    output << t.str << endl;
    output << "Length: "<< t.Length();
    output << endl;

    return output;
}

int String::FastFind(String pat)
{
    int posP = 0, posS = 0;
    int lengthP = pat.Length(), lengthS = Length();

    while((posP < lengthP) && (posS < lengthS))
    {
        if (pat.str[posP] == str[posS])
        {
            posP++;
            posS++;
        }
        else
        {
            if (posP == 0)
                posS++;
            else
                posP = pat.f[posP -1] + 1;
        }
    }
    if (posP < lengthP)
        return -1;
    else
        return posS-lengthP;
}

String String::Concat(String t)
{
    int i;
    int j;
    String c;

    c.str = new char[Length() + t.Length() + 1];
    for (i = 0; i < Length(); i++)
    {
        c.str[i] = str[i];
    }
    for (j = 0; j < t.Length(); i++, j++)
    {
        c.str[i] = t.str[j];
    }
    c.str[i] = '\0';
    c.length = i;

    return c;
}

String String::Substr(int i, int j)
{
    int start;
    String c;

    c.str = new char[j];
    for (start = 0; start < j; i++, start++)
        c.str[start] = str[i];
    c.str[start] = '\0';
    c.length = start - 1;

    return c;
}

String String::Delete(int start, int len)
{
    String c;
    int i;
    int j;

    c.str = new char[Length()];
    for (i = 0; i < start; i++)
    {
        c.str[i] = str[i];
    }
    for (j = 0; j < (Length() - len - start); i++, j++)
    {
        c.str[i] = str[i + len];
    }

    c.str[i] = '\0';
    c.length = i;
    return c;
}

String String::CharDelete(char c)
{
    int i;
    int j = 0;
    int record[Length()];
    int times = 0;
    String New;

    for (int i = 0; i < Length(); i++)
        record[i] = 0;
    for (int i = 0; i < Length(); i++)
        if (str[i] == c)
        {
            record[i]++;
            times++;
        }
    New.str = new char[Length() - times + 1];
    for (int i = 0; i < Length(); i++)
    {
        if (record[i] == 0)
        {
            if (str[i] == ' ')
            {
                for (; str[i + 1] == c; i++);
                if (str[i + 1] == ' ')
                {
                    i += 1;
                    New.str[j] = str[i];
                    j++;
                }
                else
                {
                    New.str[j] = str[i];
                    j++;
                }
            }
            else
            {
                New.str[j] = str[i];
                j++;
            }
        }
    }
    New.str[j] = '\0';
    New.length = Length() - times;

    return New;
}

int String::Compare(String y)
{
    int i;

    for (i = 0; i < Length() && i < y.Length() && str[i] == y.str[i]; i++);
    if (i == Length() && i == y.Length())
        return 0;
    else if (i < Length() && i < y.Length())
    {
        if (str[i] < y.str[i])
            return -1;
        else if (str[i] > y.str[i])
            return 1;
    }
    else if (i == Length() && i < y.Length())
        return -1;
    else if (i < Length() && i == y.Length())
        return 1;
}

int main ()
{
    cout << "The first time execution: " << endl;
    String A("GadeurtNTHUeday", 15);
    String B("NTHU", 4);
    int ans;


    cout << "String A: "<< A;
    cout << "String B: " << B;
    cout << "Whether string A is empty: " << A.operator!() <<endl;
    cout << "Whether string A is equally to string B: " << A.operator==(B) <<endl;
    cout << "Get the number of characters of A: " << A.Length() << endl;
    cout << "Where string B is in string A: " << A.FastFind(B) << endl;
    //cout << "Concatenate string A with string B: " << A.Concat(B) << endl;
    //cout << "Substring of string A from 1 to 3: " << A.Substr(1,3) << endl;
    //cout << "Delete string A from 1 of length 3: " << A.Delete(1,3) << endl;
    //cout << "Delete char c of string : " << A.CharDelete(char c) << endl;
    ans = A.Compare(B);
    cout << "The comparation result of A & B is: " << ans << endl;

    cout << endl << "The second time execution: " << endl;
    String C("Jkiojucgdougps", 14);
    String D("gdou", 4);


    cout << "String C: "<< C;
    cout << "String D: "<< D;
    cout << "Whether string C is empty: " << C.operator!() <<endl;
    cout << "Whether string C is equally to string D: " << C.operator==(D) <<endl;
    cout << "Get the number of characters of C: " << C.Length() << endl;
    cout << "Where string D is in string C: " << C.FastFind(D) << endl;
    //cout << "Concatenate string A with string B: " << A.Concat(B) << endl;
    //cout << "Substring of string A from 1 to 3: " << A.Substr(1,3) << endl;
    //cout << "Delete string A from 1 of length 3: " << A.Delete(1,3) << endl;
    //cout << "Delete char c of string : " << A.CharDelete(char c) << endl;
    ans = C.Compare(D);
    cout << "The comparation result of C & D is: " << ans << endl;


    return 0;
}

#include <iostream>
#include <string>

using namespace std;

class SymbleTable1
{
public:
    SymbleTable1();
    void Insert(const string& key);
    bool search(const string& key);
    void display();
private:
    int h(const string& key);
private:
    string** ht;
    int  ts = 26;
};

SymbleTable1::SymbleTable1()
{
    ht = new string*[26];
    for (int i = 0; i < 26; i++)
        ht[i] = new string;
}

void SymbleTable1::Insert(const string& key)
{
    int hv = h(key);
    int i;
    for (i = hv; !ht[i]->empty(); i = (i + 1) % ts);

    *ht[i] = key;
}

bool SymbleTable1::search(const string& key)
{
    int hv = h(key);
    int j;
    for (j = hv; *ht[j] != key;)
    {
        j = (j + 1) % ts;
        if (j == hv) return false;
    }
    return true;
}

int SymbleTable1::h(const string& key)
{
    return (int)key[0] % 26;
}

struct KeyNode
{
    string key;
    KeyNode* next = nullptr;
};

void SymbleTable1::display()
{
    for (int i = 0; i < ts; i++)
    {
        cout << i << ": ";
        cout << *ht[i] << endl;
    }
}

class SymbleTable2
{
public:
    SymbleTable2();
    void Insert(const string& key);
    bool search(const string& key);
    void display();
private:
    int h(const string& key);
private:
    KeyNode** ht;
    int  ts = 26;
};

SymbleTable2::SymbleTable2()
{
    ht = new KeyNode*[26];
    for (int i = 0; i < ts; i++)
        ht[i] = nullptr;
}

void SymbleTable2::Insert(const string& key)
{
    int hv = h(key);
    KeyNode* Newnode;
    Newnode = new KeyNode;
    Newnode->key = key;
    Newnode->next = nullptr;
    if (!ht[hv])
        ht[hv] = Newnode;
    else
    {
        KeyNode* node;
        for (node = ht[hv]; node->next; node = node->next);
        node->next = Newnode;
    }
}

bool SymbleTable2::search(const string& key)
{
    int hv = h(key);
    for (KeyNode* node = ht[hv]; node; node = node->next)
        if (node->key == key)
            return true;
    return false;
}

int SymbleTable2::h(const string& key)
{
    return (int)key[0] % 26;
}

void SymbleTable2::display()
{
    for (int i = 0; i < ts; i++)
    {
        cout << i << ": ";
        for (KeyNode* node = ht[i]; node; node = node->next)
            cout << node->key << " ";
        cout << endl;
    }
}

int main()
{
    SymbleTable1 table1;
    cout << "Table1: " << endl;
    table1.Insert("abc");
    table1.Insert("abcd");
    table1.Insert("b");
    table1.Insert("cc");
    table1.Insert("d");
    table1.Insert("dog");
    table1.Insert("dead");
    table1.Insert("egg");
    table1.Insert("eat");
    table1.Insert("frog");
    table1.Insert("fall");
    table1.Insert("g");
    table1.Insert("hot");
    table1.display();
    cout << "search for \"abc\": " << endl;
    if (table1.search("abc"))
        cout << "abc found!" << endl;
    cout << "search for \"ac\": " << endl;
    if (table1.search("ac"))
        cout << "ac found!" << endl;
    cout << "search for \"eat\": " << endl;
    if (table1.search("eat"))
        cout << "eat found!" << endl;
    cout << "search for \"goat\": " << endl;
    if (table1.search("goat"))
        cout << "goat found!" << endl;

    SymbleTable2 table2;
    cout << endl << "Table2: " << endl;
    table2.Insert("abc");
    table2.Insert("abcd");
    table2.Insert("b");
    table2.Insert("cc");
    table2.Insert("d");
    table2.Insert("dog");
    table2.Insert("dead");
    table2.Insert("egg");
    table2.Insert("eat");
    table2.Insert("frog");
    table2.Insert("fall");
    table2.Insert("g");
    table2.Insert("hot");
    table2.display();
    cout << "search for \"abc\": " << endl;
    if (table2.search("abc"))
        cout << "abc found!" << endl;
    cout << "search for \"ac\": " << endl;
    if (table2.search("ac"))
        cout << "ac found!" << endl;
    cout << "search for \"eat\": " << endl;
    if (table2.search("eat"))
        cout << "eat found!" << endl;
    cout << "search for \"goat\": " << endl;
    if (table2.search("goat"))
        cout << "goat found!" << endl;
}

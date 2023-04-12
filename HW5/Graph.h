#pragma once

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct Node
{
    Node() = default;
    Node(int d, Node* n = nullptr)
        : data(d), next(n) {}
    int data = 0;
    Node* next = nullptr;
};

class Graph
{
public:
    Graph(int size);
    void Setup1();
    void Setup2();
    void Setup3();
    void BFS(int index);
    void DFS(int index);
    void Components();
    void DfnLow(int index);
private:
    void DFSrec(const int v);
    void visit(Node* node);
    void DfnLow(const int u, const int v);
    void OutputNewComponents();
private:
    Node** adjLists;
    int n;
    bool* visited;
    int num;
    int* dfn;
    int* low;
};

Graph::Graph(int size)
    : n(size)
{
    adjLists = new Node*[n];
}

void Graph::Setup1()
{
    adjLists[0] = new Node(1, new Node(2));
    adjLists[1] = new Node(0, new Node(3));
    adjLists[2] = new Node(0, new Node(3));
    adjLists[3] = new Node(1, new Node(2));
    adjLists[4] = new Node(5);
    adjLists[5] = new Node(4, new Node(6));
    adjLists[6] = new Node(5, new Node(7));
    adjLists[7] = new Node(6);
}

void Graph::Setup2()
{
    adjLists[0] = new Node(1, new Node(2));
    adjLists[1] = new Node(0, new Node(3, new Node(4)));
    adjLists[2] = new Node(0, new Node(5, new Node(6)));
    adjLists[3] = new Node(1, new Node(7));
    adjLists[4] = new Node(1, new Node(7));
    adjLists[5] = new Node(2, new Node(7));
    adjLists[6] = new Node(2, new Node(7));
    adjLists[7] = new Node(3, new Node(4, new Node(5, new Node(6))));
}

void Graph::Setup3()
{
    adjLists[0] = new Node(1);
    adjLists[1] = new Node(0, new Node(2, new Node(3)));
    adjLists[2] = new Node(1, new Node(4));
    adjLists[3] = new Node(1, new Node(4, new Node(5)));
    adjLists[4] = new Node(2, new Node(3));
    adjLists[5] = new Node(3, new Node(6, new Node(7)));
    adjLists[6] = new Node(5, new Node(7));
    adjLists[7] = new Node(5, new Node(6, new Node(8, new Node(9))));
    adjLists[8] = new Node(7);
    adjLists[9] = new Node(7);
}

void Graph::DFS(int index)
{
    visited = new bool[n];
    fill(visited, visited + n, false);   
    DFSrec(index);
    delete[] visited;
    cout << endl;
}

void Graph::DFSrec(const int v)
{
    cout << v << " ";
    visited[v] = true;
    for (Node* temp = adjLists[v]; temp; temp = temp->next)
    {
        if (!visited[temp->data])
            DFSrec(temp->data);
    }

}

void Graph::BFS(int v)
{
    visited = new bool[n];
    fill(visited, visited + n, false);
    queue<int> q;
    q.push(v);
    while (!q.empty())
    {
        v = q.front();
        q.pop();
        cout << v << " ";
        visited[v] = true;
        for (Node* temp = adjLists[v]; temp; temp = temp->next)
            if (!visited[temp->data])
            {
                q.push(temp->data);
                visited[temp->data] = true;
            }
    }
    delete[] visited;
    cout << endl;
}

void Graph::Components()
{
    visited = new bool[n];
    fill(visited, visited + n, false);
    for (int i = 0; i < n; i++)
        if (!visited[i])
        {
            DFSrec(i);
            OutputNewComponents();
        }
    delete[] visited;
}

void Graph::visit(Node* node)
{
    cout << node->data << " ";
}

void Graph::OutputNewComponents()
{
    cout << "//" << endl;
}

void Graph::DfnLow(int x)
{
    num = 1;
    dfn = new int[n];
    low = new int[n];
    fill(dfn, dfn + n, 0);
    fill(low, low + n, 0);
    DfnLow(x, -1);
    cout << "Vertex:";
    for (int i = 0; i < n; i++)
        cout << "[" << i << "]";
    cout << endl;
    cout << "dfn:   ";
    for (int i = 0; i < n; i++)
        cout << " " << dfn[i] << " ";
    cout << endl;
    cout << "low:   ";
    for (int i = 0; i < n; i++)
        cout << " " << low[i] << " ";
    cout << endl;
    delete[] dfn;
    delete[] low;
}

void Graph::DfnLow(const int u, const int v)
{
    dfn[u] = low[u] = num++;
    for (Node* temp = adjLists[u]; temp; temp = temp->next)
    {
        int w = temp->data;
        if (dfn[w] == 0)
        {
            DfnLow(w, u);
            low[u] = min(low[u], low[w]);
        }
        else if (w != v)
            low[u] = min(low[u], dfn[w]);
    }
    // for (int i = 0; i < n; i++)
    //     cout << dfn[i] << " ";
    // cout << endl;
    // for (int i = 0; i < n; i++)
    //     cout << low[i] << " ";
    // cout << endl;
}
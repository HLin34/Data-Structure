#pragma once

#include <utility>
#include <iostream>
#include <vector>

using namespace std;

template <class K, class E>
struct TreeNode;

template <class K, class E>
class Dictinoary;

template <class K, class E>
class BST;

template <class K, class E>
struct TreeNode
{
    TreeNode() = default;
    TreeNode(const TreeNode& node) : data(node.data) {}
    TreeNode(const pair<K, E>& _data, TreeNode<K, E>* lc = nullptr, TreeNode<K, E>* rc = nullptr)
        : data(_data), leftChild(lc), rightChild(rc) {}

    pair<K, E> data;
    TreeNode<K, E>* leftChild = nullptr;
    TreeNode<K, E>* rightChild = nullptr;
    int leftSize = 1;
};

template <class K, class E>
class Dictinoary
{
public:
    virtual bool IsEmpty() const = 0;
    virtual pair<K, E>* Get(const K&) const = 0;
    virtual void Insert(const pair<K, E>&) = 0;
    virtual void Delete(const K&) = 0;
};

template <class K, class E>
class BST : Dictinoary <K, E>
{
public:
    BST() = default;
    BST(const vector<K>& arr);
    virtual bool IsEmpty() const override;
    virtual pair<K, E>* Get(const K&) const override;
    virtual void Insert(const pair<K, E>&) override;
    virtual void Delete(const K&) override;

    pair<K, E>* RankGet(int r);
    void Split(const K& k, BST<K, E>& small, pair<K, E>*& mid, BST<K, E>& big);
    void InorderPrint();

private:
    pair<K, E>* Get(TreeNode<K, E>* p, const K& k) const;
    void InorderPrintRec(TreeNode<K, E>* node);
private:
    TreeNode<K, E>* root = nullptr;
};

template <class K, class E>
BST<K, E>::BST(const vector<K>& arr)
{
    for (const K& key : arr)
        Insert({key, 0});
}

template <class K, class E>
bool BST<K, E>::IsEmpty() const
{
    return root == nullptr;
}

template <class K, class E>
pair<K, E>* BST<K, E>::Get(const K& k) const
{
    return Get(root, k);
}

template <class K, class E>
void BST<K, E>::Insert(const pair<K, E>& thePair)
{
    TreeNode<K, E>* p = root;
    TreeNode<K, E>* pp = nullptr;
    while (p)
    {
        pp = p;
        if (thePair.first < p->data.first)
        {    
            p->leftSize++;
            p = p->leftChild;
        }
        else if (thePair.first > p->data.first)
            p = p->rightChild;
        else 
        {
            p->data.second = thePair.second;
            return;
        }
    }   

    p = new TreeNode<K, E> (thePair);
    if (root)
        if (thePair.first < pp->data.first)
            pp->leftChild = p;
        else 
            pp->rightChild = p;
    else 
        root = p;

}

template <class K, class E>
pair<K, E>* BST<K, E>::Get(TreeNode<K, E>* p, const K& k) const
{
    if (!p) return nullptr;
    if (k < p->data.first) return Get(p->leftChild, k);
    if (k > p->data.first) return Get(p->rightChild, k);
    return &p->data;
}

template <class K, class E>
void BST<K, E>::Delete(const K& key)
{
    TreeNode<K, E>* deleteKey = root;
    TreeNode<K, E>** parentOfDeleteKey = &root;
    if (!root)
        throw "The key doesn't exist, cannot delete!";
    while (deleteKey->data.first != key)
    {
        if (deleteKey->data.first > key)
        {
            parentOfDeleteKey = &deleteKey->leftChild;
            deleteKey->leftSize--;
            deleteKey = deleteKey->leftChild;
        }
        else
        {
            parentOfDeleteKey = &deleteKey->rightChild;
            deleteKey = deleteKey->rightChild;
        }
        if (!deleteKey)
            throw "The key doesn't exist, cannot delete!";
    }

    if (deleteKey->leftChild && deleteKey->rightChild)
    {
        TreeNode<K, E>* largestofLeftSubTree = deleteKey->leftChild;
        TreeNode<K, E>** parentofLargestofLeftSubTree = &deleteKey->leftChild;
        while (largestofLeftSubTree->rightChild)
        {
            parentofLargestofLeftSubTree = &largestofLeftSubTree->rightChild;
            largestofLeftSubTree = largestofLeftSubTree->rightChild;
        }
        (*parentofLargestofLeftSubTree) = largestofLeftSubTree->leftChild;
        largestofLeftSubTree->leftChild = deleteKey->leftChild;
        largestofLeftSubTree->rightChild = deleteKey->rightChild;
        largestofLeftSubTree->leftSize = deleteKey->leftSize - 1;
        (*parentOfDeleteKey) = largestofLeftSubTree;
    }
    else if (deleteKey->leftChild)
        (*parentOfDeleteKey) = deleteKey->leftChild;
    else if (deleteKey->rightChild)
        (*parentOfDeleteKey) = deleteKey->rightChild;
    else
        (*parentOfDeleteKey) = nullptr;

    delete deleteKey;
}

template <class K, class E>
pair<K, E>* BST<K, E>:: RankGet(int r)
{
    TreeNode<K, E>* currentNode = root;
    while (currentNode)
    {
        if (r < currentNode->leftSize)
            currentNode = currentNode->leftChild;
        else if (r > currentNode->leftSize)
        {
            r -= currentNode->leftSize;
            currentNode = currentNode->rightChild;
        }
        else 
            return &currentNode->data;
    }
    return nullptr;
}

template <class K, class E>
void BST<K, E>::Split(const K& k, BST<K, E>& small, pair<K, E>*& mid, BST<K, E>& big)
{
    if (!root)
    {
        small.root = big.root = 0; 
        return;
    }

    TreeNode<K, E>* sHead  = new TreeNode<K, E>;
    TreeNode<K, E>* s      = sHead;
    TreeNode<K, E>* bHead  = new TreeNode<K, E>;
    TreeNode<K, E>* b      = bHead;
    TreeNode<K, E>* currentNode = root;

    while (currentNode)
    {
        if (k < currentNode->data.first)
        {
            b->leftChild = currentNode;
            b = currentNode; 
            currentNode = currentNode->leftChild;
        }
        else if (k > currentNode->data.first)
        {
            s->leftChild = currentNode;
            s = currentNode; 
            currentNode = currentNode->rightChild;
        }
        else 
        {
            s->rightChild = currentNode->leftChild;
            b->leftChild = currentNode->rightChild;
            small.root = sHead->rightChild;
            delete sHead;
            big.root = bHead->leftChild;
            delete bHead;
            mid = new pair<K, E>(currentNode->data.first, 
                                 currentNode->data.second);
            delete currentNode;
            return;
        }
    }

    s->rightChild = b->leftChild = 0;
    small.root = sHead->rightChild;
    delete sHead;
    big.root = bHead->leftChild;
    delete bHead;
    mid = 0;
    return;
}

template <class K, class E>
void BST<K, E>::InorderPrint()
{
    InorderPrintRec(root);
}

template <class K,  class E>
void BST<K, E>::InorderPrintRec(TreeNode<K, E>* node)
{
    if (node)
    {
        InorderPrintRec(node->leftChild);
        cout << node->data.first << " " << node->data.second << endl;
        InorderPrintRec(node->rightChild);
    }
}
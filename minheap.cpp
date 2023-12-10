/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// Write your code below this line
void DEST2(HeapNode *root)
{  
    if(root==NULL){
        return;
    }
    else{
    if(root->left!=NULL) DEST2(root->left);
    if(root->right!=NULL) DEST2(root->right);
        delete root;
        root=NULL;
    }
}

HeapNode *getnode(HeapNode *root, int idx)
{
    if (idx == 0)
    {
        return root;
    }
    int pidx = (idx - 1) / 2;
    HeapNode *par = getnode(root, pidx);
    if (idx == 2 * pidx + 1)
    {
        return par->left;
    }
    else if (idx == 2 * pidx + 2)
    {
        return par->right;
    }
    return NULL;
}

void Heapifyup(HeapNode *root, HeapNode *t)
{
    while (t->par != NULL)
    {   int temp;
        if (t->par->val > t->val)
        {
            temp = t->val;
            t->val = t->par->val;
            t->par->val = temp;
        }
        t = t->par;
    }
}

void Heapifydown(HeapNode *t)
{
    HeapNode *smallest = t;
    if (t->left != NULL and t->left->val < t->val)
    {
        smallest = t->left;
    }
    if (t->right != NULL and t->right->val < smallest->val)
    {
        smallest = t->right;
    }
    if (smallest != t)
    {
        int temp = smallest->val;
        smallest->val = t->val;
        t->val = temp;
        Heapifydown(smallest);
    }
}

MinHeap::MinHeap()
{
    size = 0;
    root = NULL;
}

void MinHeap::push_heap(int num)
{
    size++;
    if (size == 1)
    {
        root = new HeapNode(num);
        return;
    }
    else
    {
        HeapNode *n = new HeapNode(num);
        int pi = ((size - 1) - 1) / 2; // we have increased size earlier only;
        HeapNode *par = getnode(root, pi);
        if (size - 1 == 2 * pi + 1)
        {
            par->left = n;
            n->par = par;
        }
        else
        {
            par->right = n;
            n->par = par;
        }
        Heapifyup(root, n);
    }
}

int MinHeap::get_min()
{
    return root->val;
}

void MinHeap::pop()
{
    if (size == 1)
    {
        delete root;
        root=NULL;
        size--;
        return;
    }
    HeapNode *e = getnode(root, size - 1);
    root->val = e->val;
    if (e->par->left == e)
    {   
        e->par->left = NULL;
        delete e;
    }
    else
    {
        e->par->right = NULL;
        delete e;
    }
    size--;
    Heapifydown(root);
}

MinHeap::~MinHeap()
{   
    if(root!=NULL)delete root;
}
/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
// Write your code below this line

SymNode::SymNode()
{
    key = "";
    height = -1;
    address = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k)
{
    key = k;
    height = 0;
    address = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode *SymNode::LeftLeftRotation()
{
    SymNode *y = right; // atleast y must exsist due to which right imbalance is created
    SymNode *T2 = y->left;
    if (this->par != NULL)
    {
        if (this->par->left == this)
        {
            this->par->left = y;
        }
        else
        {
            this->par->right = y;
        }
    }
    y->par = this->par;
    y->left = this;
    this->par = y;
    this->right = T2;
    int h1, h2, h3;
    if (this->left != NULL)
    {
        h1 = this->left->height;
    }
    else
    {
        h1 = -1;
    }
    if (T2 != NULL)
    {
        T2->par = this;
        h2 = T2->height;
    }
    else
    {
        h2 = -1;
    }
    if (y->right != NULL)
    {
        h3 = y->right->height;
    }
    else
    {
        h3 = -1;
    }
    this->height = max(h1, h2) + 1;
    y->height = max(this->height, h3) + 1;
    return y;
}

SymNode *SymNode::RightRightRotation()
{
    SymNode *y = left;
    SymNode *T3 = y->right;
    if (this->par != NULL)
    {
        if (this->par->left == this)
        {
            this->par->left = y;
        }
        else
        {
            this->par->right = y;
        }
    }
    y->par = this->par;
    y->right = this;
    this->par = y;
    this->left = T3;
    int h1, h2, h3;
    if (this->right != NULL)
    {
        h1 = this->right->height;
    }
    else
    {
        h1 = -1;
    }
    if (T3 != NULL)
    {
        T3->par = this;
        h2 = T3->height;
    }
    else
    {
        h2 = -1;
    }
    if (y->left != NULL)
    {
        h3 = y->left->height;
    }
    else
    {
        h3 = -1;
    }
    this->height = max(h1, h2) + 1;
    y->height = max(this->height, h3) + 1;
    return y;
}

SymNode *SymNode::LeftRightRotation()
{
    SymNode *y = this->right;
    SymNode *x = y->left;
    SymNode *T2 = x->left;
    SymNode *T3 = x->right;
    if (this->par != NULL)
    {
        if (this->par->left == this)
        {
            this->par->left = x;
        }
        else
        {
            this->par->right = x;
        }
    }
    x->par = this->par;
    x->left = this;
    this->par = x;
    x->right = y;
    y->par = x;
    this->right = T2;
    y->left = T3;
    int h1, h2, h3, h4;
    if (this->left != NULL)
    {
        h1 = this->left->height;
    }
    else
    {
        h1 = -1;
    }
    if (T2 != NULL)
    {
        T2->par = this;
        h2 = T2->height;
    }
    else
    {
        h2 = -1;
    }
    if (T3 != NULL)
    {
        T3->par = y;
        h3 = T3->height;
    }
    else
    {
        h3 = -1;
    }
    if (y->right != NULL)
    {
        h4 = y->right->height;
    }
    else
    {
        h4 = -1;
    }
    this->height = max(h1, h2) + 1;
    y->height = max(h3, h4) + 1;
    x->height = max(y->height, this->height) + 1;
    return x;
}

SymNode *SymNode::RightLeftRotation()
{
    SymNode *y = this->left;
    SymNode *x = y->right;
    SymNode *T2 = x->left;
    SymNode *T3 = x->right;
    if (this->par != NULL)
    {
        if (this->par->left == this)
        {
            this->par->left = x;
        }
        else
        {
            this->par->right = x;
        }
    }
    x->par = this->par;
    x->left = y;
    y->par = x;
    x->right = this;
    this->par = x;
    this->left = T3;
    y->right = T2;
    int h1, h2, h3, h4;
    if (y->left != NULL)
    {
        h1 = y->left->height;
    }
    else
    {
        h1 = -1;
    }
    if (T2 != NULL)
    {
        T2->par = y;
        h2 = T2->height;
    }
    else
    {
        h2 = -1;
    }
    if (T3 != NULL)
    {
        T3->par = this;
        h3 = T3->height;
    }
    else
    {
        h3 = -1;
    }
    if (this->right != NULL)
    {
        h4 = this->right->height;
    }
    else
    {
        h4 = -1;
    }
    this->height = max(h3, h4) + 1;
    y->height = max(h1, h2) + 1;
    x->height = max(y->height, this->height) + 1;
    return x;
}

SymNode::~SymNode()
{
    // do not delete parent,left,right;as that will affect the remove in symtable
    if(left!=NULL)delete left;
    if(right!=NULL)delete right;
}
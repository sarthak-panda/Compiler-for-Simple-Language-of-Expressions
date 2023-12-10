/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// Write your code below this line

void DEST(SymNode *root)
{   
    if(root==NULL){
        return;
    }
    else{
        DEST(root->left);
        DEST(root->right);
        delete root;
        root=NULL;
        return;
    }
}

string Status(SymNode *n)
{
    int h1, h2;
    string s;
    if (n->left != NULL)
    {
        h1 = n->left->height;
    }
    else
    {
        h1 = -1;
    }
    if (n->right != NULL)
    {
        h2 = n->right->height;
    }
    else
    {
        h2 = -1;
    }
    if (h1 == h2)
    {
        s = "PB"; // perfectly balanced node
    }
    else if (h1 - h2 == 1)
    {
        s = "LH"; // left heavy
    }
    else if (h2 - h1 == 1)
    {
        s = "RH"; // right heavy
    }
    else if (h1 - h2 == 2)
    {
        s = "LIB"; // left imbalance
    }
    else if (h2 - h1 == 2)
    {
        s = "RIB"; // right imbalance
    }
    return s;
}

SymbolTable::SymbolTable()
{
    size = 0;
    root = NULL;
}

void SymbolTable::insert(string k)
{
    SymNode *n = new SymNode(k);
    if (root==NULL)
    {
        size=0;
        root = n;
    }
    else
    {
        SymNode *temp = root, *temppar = root, *temp2 = NULL, *z;
        // insertion of BST
        while (temp != NULL)
        {
            if (k > temp->key)
            {
                temppar = temp;
                temp = temp->right;
            }
            else
            {
                temppar = temp;
                temp = temp->left;
            }
        }
        if (k > temppar->key)
        {
            temppar->right = n;
            n->par = temppar;
        }
        else
        {
            temppar->left = n;
            n->par = temppar;
        }
        temp2 = n->par;
        // recalculation of heights along the path of ancestors
        //  along with simultanous checking for rotations if needed
        while (temp2 != NULL)
        {
            int h1, h2;
            if (temp2->left != NULL)
            {
                h1 = temp2->left->height;
            }
            else
            {
                h1 = -1;
            }
            if (temp2->right != NULL)
            {
                h2 = temp2->right->height;
            }
            else
            {
                h2 = -1;
            }
            temp2->height = max(h1, h2) + 1;
            if (Status(temp2) == "LIB")
            {
                if (temp2->left != NULL and Status(temp2->left) == "RH")
                { // can it be PB too
                    z = temp2->RightLeftRotation();
                    if (z->par == NULL)
                    {
                        root = z;
                    }
                }
                else
                {
                    z = temp2->RightRightRotation();
                    if (z->par == NULL)
                    {
                        root = z;
                    }
                }
            }
            else if (Status(temp2) == "RIB")
            {
                if (temp2->right != NULL and Status(temp2->right) == "LH")
                {
                    z = temp2->LeftRightRotation();
                    if (z->par == NULL)
                    { // handling of root change edge case
                        root = z;
                    }
                }
                else
                {
                    z = temp2->LeftLeftRotation();
                    if (z->par == NULL)
                    {
                        root = z;
                    }
                }
            }
            temp2 = temp2->par;
        }
    }
    size++;
}

void SymbolTable::remove(string k)
{
    SymNode *temp = root, *temppar = root, *temp2 = NULL, *z;
    while (temp!=NULL and temp->key != k)
    {
        if (k > temp->key)
        {
            temppar = temp;
            temp = temp->right;
        }
        else
        {
            temppar = temp;
            temp = temp->left;
        }
    }
    if(temp==NULL){
        return;
    }
    size--;
    if(size==0){
        root->left=NULL;
        root->right=NULL;
        root=NULL;
        return;
    }
    // case1 the key is leaf node
    if (temp->left == NULL and temp->right == NULL)
    {
        if (temppar->left == temp)
        {
            temppar->left = NULL;
        }
        else
        {
            temppar->right = NULL;
        }
        temp2 = temppar;
        temp->left=NULL;
        temp->right=NULL;
        delete temp;
    }
    // case 2 one child only
    else if ((temp->left == NULL and temp->right != NULL) or (temp->left != NULL and temp->right == NULL))
    {
        if (temp == root)
        {
            if (temp->left != NULL)
            {
                root = temp->left;
            }
            else
            {
                root = temp->right;
            }
            root->par = NULL;
        }
        else
        {
            if (temppar->right == temp)
            {
                if (temp->left != NULL)
                {
                    temppar->right = temp->left;
                    temp->left->par = temppar;
                }
                else
                {
                    temppar->right = temp->right;
                    temp->right->par = temppar;
                }
            }
            else
            {
                if (temp->left != NULL)
                {
                    temppar->left = temp->left;
                    temp->left->par = temppar;
                }
                else
                {
                    temppar->left = temp->right;
                    temp->right->par = temppar;
                }
            }
            temp2 = temppar;
        }
        temp->left=NULL;
        temp->right=NULL;
        delete temp;
    }
    // case 3 both the child are present
    else
    {
        SymNode *s, *spar;
        spar = temp;
        s = temp->right;
        while (s->left != NULL)
        {
            spar = s;
            s = s->left;
        }
        temp->key = s->key;
        temp->address = s->address;
        // temp height is maintained
        if (spar == temp)
        {
            spar->right = s->right;
            if (s->right != NULL)
                s->right->par = spar;
        }
        else
        {
            if (s->right == NULL)
            {
                spar->left = NULL;
            }
            else
            {
                spar->left = s->right;
                s->right->par = spar;
            }
        }
        temp2 = spar;
        s->left=NULL;
        s->right=NULL;
        delete s;
    }
    // recalculation of heights along the path of ancestors
    //  along with simultanous checking for rotations if needed
    while (temp2 != NULL)
    {
        int h1, h2;
        if (temp2->left != NULL)
        {
            h1 = temp2->left->height;
        }
        else
        {
            h1 = -1;
        }
        if (temp2->right != NULL)
        {
            h2 = temp2->right->height;
        }
        else
        {
            h2 = -1;
        }
        temp2->height = max(h1, h2) + 1;
        if (Status(temp2) == "LIB")
        {
            if (temp2->left != NULL and Status(temp2->left) == "RH")
            { // can it be PB too
                z = temp2->RightLeftRotation();
                if (z->par == NULL)
                {
                    root = z;
                }
            }
            else
            {
                z = temp2->RightRightRotation();
                if (z->par == NULL)
                {
                    root = z;
                }
            }
        }
        else if (Status(temp2) == "RIB")
        {
            if (temp2->right != NULL and Status(temp2->right) == "LH")
            {
                z = temp2->LeftRightRotation();
                if (z->par == NULL)
                {
                    root = z;
                }
            }
            else
            {
                z = temp2->LeftLeftRotation();
                if (z->par == NULL)
                {
                    root = z;
                }
            }
        }
        temp2 = temp2->par;
    }
}

int SymbolTable::search(string k)
{
    SymNode *temp = root;
    while (temp!=NULL and temp->key != k)
    {
        if (k > temp->key)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }
    if(temp==NULL){
        return -2;
    }
    return temp->address;
}

void SymbolTable::assign_address(string k, int idx)
{
    SymNode *temp = root;
    while (temp->key != k)
    {
        if (k > temp->key)
        {
            temp = temp->right;
        }
        else
        {
            temp = temp->left;
        }
    }
    temp->address = idx;
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}

SymbolTable::~SymbolTable()
{   
    if(root!=NULL)delete root;
}

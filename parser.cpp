/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
// Write your code below this line
ExprTreeNode *Node_creator(string t)
{
    ExprTreeNode *temp = new ExprTreeNode();
    if (t == "+" or t == "-" or t == "*" or t == "/" or t == "%")
    {
        if (t == "+")
        {
            temp->type = "ADD";
        }
        else if (t == "-")
        {
            temp->type = "SUB";
        }
        else if (t == "*")
        {
            temp->type = "MUL";
        }
        else if (t == "/")
        {
            temp->type = "DIV";
        }
        else
        {
            temp->type = "MOD";
        }
    }
    else if ((t[0] == '-' and isdigit(t[1])) or isdigit(t[0]))
    { // to implement isnum.ASSUMING C TYPE VARIABLE can neither begin from digit or a minus symbol
        temp->type = "VAL";
        temp->num = stoi(t);
    }
    else if (t == "(")
    {
        temp->type = "BKT";
    }
    else if (t == "del")
    {
        temp->type = "DEL";
    }
    else if (t == "ret")
    {
        temp->type = "RET";
    }
    else
    {
        temp->type = "VAR";
        temp->id = t;
    }
    return temp;
}

Parser::Parser()
{
    symtable = new SymbolTable();
}

void Parser::parse(vector<string> expression)
{   
    vector<ExprTreeNode *> stack; // we will be pushing at back and popping back only.
    ExprTreeNode *e = new ExprTreeNode(), *lv;
    e->type = "EQL";
    e->id = expression[1];
    lv = Node_creator(expression[0]);
    e->left = lv;
    if(lv->type=="DEL"){
        last_deleted=symtable->search(expression[2]);
        symtable->remove(expression[2]);
    }    
    if (lv->type == "VAR")
    {
        symtable->insert(expression[0]);
    }
    if (expression.size() == 3)
    {
        string t = expression[2];
        ExprTreeNode *rgt = Node_creator(t);
        e->right = rgt;
    }
    else
    {
        for (long unsigned int i = 2; i < expression.size(); i++)
        {
            string t = expression[i];
            if (t != ")")
            {
                stack.push_back(Node_creator(t));
            }
            else
            {
                ExprTreeNode *rgt = stack.back();
                stack.pop_back();
                ExprTreeNode *mid = stack.back();
                stack.pop_back();
                ExprTreeNode *lft = stack.back();
                stack.pop_back();
                stack.pop_back(); // popping the left bracket
                mid->right = rgt;
                mid->left = lft;
                stack.push_back(mid);
            }
        }
        e->right = stack.back();
        stack.pop_back();
    }
    expr_trees.push_back(e);
}

Parser::~Parser()
{   
    while (expr_trees.empty() == false)
    {
        ExprTreeNode *t = expr_trees.back();
        expr_trees.pop_back();
        if(t!=NULL)delete t;
        t=NULL;
    }
    if(symtable!=NULL) delete symtable;
    symtable=new SymbolTable();
}
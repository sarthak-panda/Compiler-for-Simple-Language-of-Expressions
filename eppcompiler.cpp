/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
string targen(ExprTreeNode *n, SymbolTable *st)
{ // handles RHS
    string type = n->type;
    string res;
    if (type == "VAL")
    {
        res = "PUSH " + to_string(n->num);
    }
    else if (type == "VAR")
    {
        int ad = st->search(n->id);
        res = "PUSH mem[" + to_string(ad) + "]";
    }
    else if (type == "ADD" or type == "SUB" or type == "MUL" or type == "DIV")
    {
        res = type;
    }
    return res;
}
void rpostod(ExprTreeNode *root, SymbolTable *st, vector<string> &v)
{
    string s1, s2, s3;
    if (root->right != NULL)
    {
        rpostod(root->right, st, v);
    }
    if (root->left != NULL)
    {
        rpostod(root->left, st, v);
    }
    s3 = targen(root, st);
    v.push_back(s3);
    return;
}
EPPCompiler::EPPCompiler()
{
    targ = Parser();
    memory_size = 0;
    output_file = "";
    least_mem_loc = MinHeap();
}
EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    targ = Parser();
    memory_size = mem_limit;
    output_file = out_file;
    for (int i = 0; i < mem_limit; i++)
    {
        least_mem_loc.push_heap(i);
    }
}
void EPPCompiler::compile(vector<vector<string>> code)
{
    vector<string> v;
    ofstream out;
    out.open(output_file);
    out.close();
    for (long unsigned int i = 0; i < code.size(); i++)
    {
        targ.parse(code[i]);
        v = generate_targ_commands();
        write_to_file(v);
    }
}
vector<string> EPPCompiler::generate_targ_commands()
{
    vector<string> v;
    string z;
    ExprTreeNode *root = targ.expr_trees.back();
    SymbolTable *s = targ.symtable;
    if (root->left->type == "DEL")
    {
        //int ad = s->search(root->right->id);
        least_mem_loc.push_heap(targ.last_deleted);
        z = "DEL = mem[" + to_string(targ.last_deleted) + "]";
        v.push_back(z);
    }
    else if (root->left->type == "RET")
    {
        rpostod(root->right, s, v);
        z = "RET = POP";
        v.push_back(z);
    }
    else if (root->left->type == "VAR")
    {
        int ad = s->search(root->left->id);
        if (ad == -1)
        {
            ad = least_mem_loc.get_min();
            least_mem_loc.pop();
            // should be inseted during parsing and deleted during this process
            s->assign_address(root->left->id, ad);
        }
        rpostod(root->right, s, v);
        z = "mem[" + to_string(ad) + "] = POP";
        v.push_back(z);
    }
    return v;
}
void EPPCompiler::write_to_file(vector<string> commands)
{
    ofstream out;
    out.open(output_file, ios::app);
    for (long unsigned int i = 0; i < commands.size(); i++)
    {
        out << commands[i] << "\n";
    }
    out.close();
}
EPPCompiler::~EPPCompiler()
{
}
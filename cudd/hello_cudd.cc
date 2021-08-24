#include <iostream>
#include "cuddObj.hh"

using namespace std;

struct DdChildren
{
    DdNode* T;
    DdNode* E;
};

struct DdNode
{
    uint32_t index;
    uint32_t ref;
    union
    {
        CUDD_VALUE_TYPE value;
        DdChildren kids;
    };
};

struct DdManager{
    DdNode* one;
    DdNode* zero;
};

int main()
{
    Cudd mgr;
    BDD x = mgr.bddVar();
    BDD y = mgr.bddVar();
    // BDD z = mgr.bddVar();
    BDD f = x * y;
    BDD g = y + !x;
    BDD h = x + y;

    // cout << "f is" << (f <= g ? "" : " not")
    //      << " less than or equal to g" << endl;

    // Cudd_PrintDebug(mgr.getManager(), x.getNode(), 2, 3);
    // Cudd_PrintDebug(mgr.getManager(), y.getNode(), 2, 3);
    // Cudd_PrintDebug(mgr.getManager(), f.getNode(), 2, 3);
    // Cudd_PrintDebug(mgr.getManager(), g.getNode(), 2, 3);
    // Cudd_PrintDebug(mgr.getManager(), h.getNode(), 2, 3);

    // x.PrintCover();
    // y.PrintCover();
    // f.PrintCover();
    // g.PrintCover();
    // h.PrintCover();

    // x.PrintMinterm();
    // y.PrintMinterm();
    // f.PrintMinterm();
    // g.PrintMinterm();

    cout << mgr.getManager()->one << endl;
    cout << mgr.getManager()->zero << endl;
    cout << endl;

    DdNode *node = x.getNode();
    cout << node->index << endl;
    cout << node->value << endl;
    cout << endl;

    DdNode *nodeT = node->kids.T;
    cout << nodeT->index << endl;
    cout << nodeT->value << endl;
    // cout << (nodeT == (mgr.getManager()->one)) << endl;
    cout << endl;

    DdNode *nodeE = node->kids.E;
    cout << nodeE->index << endl;
    cout << nodeE->value << endl;
    // cout << (nodeE == (mgr.getManager()->one)) << endl;
    cout << endl;

    return 0;
}
#include <iostream>
#include <chrono>
#include <string.h>
#include "meddly.h"

using namespace std;
using namespace MEDDLY;

typedef long element_type;

int main(int argc, char *argv[])
{
    int nVariables = 10000;
    int variableBound = 2;
    int nElements = nVariables;

    // initialize the variable bounds array to provide to the domain
    int *bounds = (int *)malloc(nVariables * sizeof(int));
    assert(bounds != 0);
    for (int i = 0; i < nVariables; ++i)
    {
        bounds[i] = variableBound;
    }

    // create the elements
    int **element = (int **)malloc(nElements * sizeof(int *));
    for (int i = 0; i < nElements; ++i)
    {
        element[i] = (int *)malloc((nVariables + 1) * sizeof(int));
        element[i][0] = 0;
        for (int j = 1; j <= nVariables; ++j)
        {
            if (i + 1 == j)
            {
                element[i][j] = 1;
            }
            else
            {
                element[i][j] = DONT_CARE;
            }
        }
    }

    initialize();

    domain *d = createDomainBottomUp(bounds, nVariables);
    assert(d != 0);

    forest::policies p(false);
    // p.setPessimistic();

    forest *bdd = d->createForest(false, forest::BOOLEAN, forest::MULTI_TERMINAL, p);

    // varsに各変数を代入
    dd_edge A(bdd);
    dd_edge *vars = new dd_edge[nVariables];
    FILE_output meddlyout(stdout);
    for (int i = 0; i < nVariables; i++)
    {
        vars[i] = A;
        bdd->createEdge(element + i, 1, vars[i]);
    }

    // Fに各変数をAND結合したBDDを代入
    dd_edge F(bdd);
    F = vars[0];
    for (int i = 1; i < nVariables; i++)
    {
        F *= vars[i];
    }
    // F.show(meddlyout, 2);

    // Gに各変数をNOR結合したBDDを代入
    dd_edge G(bdd);
    dd_edge D(bdd);
    G = vars[0];
    for (int i = 1; i < nVariables; i++)
    {
        G += vars[i];
    }
    bdd->createEdge(true, D);
    G =  D - G;
    // G.show(meddlyout, 2);

    int loops = 1;
    std::chrono::_V2::system_clock::rep msec = 0;

    // HにF+Gをしたものを代入
    dd_edge H(bdd);
    for (size_t i = 0; i < loops; i++)
    {
        auto start = chrono::system_clock::now();

        H = F + G;

        auto end = chrono::system_clock::now();
        auto dur = end - start;
        msec += chrono::duration_cast<chrono::nanoseconds>(dur).count();
    }

    // H.show(meddlyout, 2);
    // bdd->showInfo(meddlyout);

    msec /= loops;
    cout << msec << " nano sec \n";
}
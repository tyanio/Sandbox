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

    dd_edge A(bdd);
    dd_edge B(bdd);
    dd_edge C(bdd);

    dd_edge *vars = new dd_edge[nVariables];
    FILE_output meddlyout(stdout);
    for (int i = 0; i < nVariables; i++)
    {
        vars[i] = A;
        bdd->createEdge(element + i, 1, vars[i]);
        // vars[i].show(meddlyout, 2);
    }

    bdd->createEdge(true, C);

    auto start = chrono::system_clock::now();

    for (int i = 0; i < nVariables; i++)
    {
        C *= vars[i];
    }

    auto end = chrono::system_clock::now();

    // C.show(meddlyout, 2);
    // bdd->showInfo(meddlyout);

    auto dur = end - start;
    auto msec = chrono::duration_cast<chrono::nanoseconds>(dur).count();
    cout << msec << " nano sec \n";
}
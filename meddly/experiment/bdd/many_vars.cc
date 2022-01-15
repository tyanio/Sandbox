#include <stdio.h>
#include <chrono>
#include "meddly.h"

using namespace std;
using namespace MEDDLY;

typedef long element_type;

int main()
{
    int nVariables = 10000;
    int variableBound = 2;
    int nElements = 1;

    auto start = chrono::system_clock::now();

    // create the elements
    int **element = (int **)malloc(nElements * sizeof(int *));
    element_type *terms = (element_type *)malloc(nElements * sizeof(element_type));
    for (int i = 0; i < nElements; ++i)
    {
        element[i] = (int *)malloc((nVariables + 1) * sizeof(int));
        element[i][0] = 0;
        for (int j = 1; j <= nVariables; ++j)
        {
            if (i == j)
            {
                element[i][j] = 1;
            }
            // assert(element[i][j] >= 0 && element[i][j] < variableBound);
        }
        terms[i] = 1;
    }

    // int nVariables = 10000;
    // int variableBound = 2;
    // int nElements = 1;

    // auto start = chrono::system_clock::now();

    // // create the elements
    // int **element = (int **)malloc(nElements * sizeof(int *));
    // element_type *terms = (element_type *)malloc(nElements * sizeof(element_type));
    // for (int i = 0; i < nElements; ++i)
    // {
    //     element[i] = (int *)malloc((nVariables + 1) * sizeof(int));
    //     element[i][0] = 0;
    //     for (int j = 1; j <= nVariables; ++j)
    //     {
    //         element[i][j] = 1;
    //         assert(element[i][j] >= 0 && element[i][j] < variableBound);
    //     }
    //     terms[i] = 1;
    // }

    initialize();

    // initialize the variable bounds array to provide to the domain
    int *bounds = (int *)malloc(nVariables * sizeof(int));
    assert(bounds != 0);
    for (int i = 0; i < nVariables; ++i)
    {
        bounds[i] = variableBound;
    }

    // Create a domain
    domain *d = createDomainBottomUp(bounds, nVariables);
    assert(d != 0);

    // Create a BDD forest in this domain
    forest::policies p(false);
    p.setPessimistic();
    forest *bdd = d->createForest(false, forest::BOOLEAN, forest::MULTI_TERMINAL, p);
    assert(bdd != 0);

    dd_edge A(bdd);

    bdd->createEdge(element, nElements, A);
    auto end = chrono::system_clock::now();

    FILE_output meddlyout(stdout);
    bdd->showInfo(meddlyout);

    auto dur = end - start;
    auto msec = chrono::duration_cast<chrono::microseconds>(dur).count();
    cout << msec << "micro sec \n";

    return 0;
}
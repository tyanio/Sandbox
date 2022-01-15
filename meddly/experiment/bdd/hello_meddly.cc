#include <iostream>
#include <string.h>
#include "meddly.h"
#include "meddly_expert.h"

using namespace MEDDLY;

typedef long element_type;

int main(int argc, char *argv[])
{
    int nVariables = 2;
    int variableBound = 2;
    int nElements = 1;
    int nTerms = 0;

    int bounds[nVariables] = {2, 2};

    // create the elements randomly
    int **element = (int **)malloc(nElements * sizeof(int *));
    element_type *terms =
        (element_type *)malloc(nElements * sizeof(element_type));

    for (int i = 0; i < nElements; ++i)
    {
        element[i] = (int *)malloc((nVariables + 1) * sizeof(int));
        element[i][0] = 0;
        for (int j = nVariables; j > 0; --j)
        {
            element[i][j] = 1;
            assert(element[i][j] >= 0 && element[i][j] < variableBound);
        }
    }

    initialize();

    domain *d = createDomainBottomUp(bounds, nVariables);
    assert(d != 0);

    forest::policies p(false);
    p.setPessimistic();

    forest *bdd = d->createForest(false, forest::BOOLEAN, forest::MULTI_TERMINAL, p);

    dd_edge A(bdd);

    bdd->createEdge(element, nElements, A);

    FILE_output meddlyout(stdout);
    A.show(meddlyout, 2);

    expert_forest *f = (expert_forest *)A.getForest();

    auto un = unpacked_node::newFull(f, 2, 2);
}
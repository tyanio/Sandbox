#include <iostream>
#include <fstream>
#include <chrono>
#include <string.h>
#include "meddly.h"

using namespace std;
using namespace MEDDLY;

typedef long element_type;

int main(int argc, char *argv[])
{
    int nVariables = 100000;
    int variableBound = 5;
    int nElements = nVariables;

    // initialize the variable bounds array to provide to the domain
    int *bounds = (int *)malloc(nVariables * sizeof(int));
    assert(bounds != 0);
    for (int i = 0; i < nVariables; ++i)
    {
        bounds[i] = variableBound;
    }

    // create the elements
    // elementのiは要素の何番目かを指していて、jはその要素の変数のレベルを指しています。
    // 下の場合、i番目のelementはi+1のレベルの変数のとき5番目の枝を選びそれ以外はDontcare、つまりi+1番目のレベル以外は省略されている変数ノードを作っていることになります。
    int **element = (int **)malloc(nElements * sizeof(int *));
    for (int i = 0; i < nElements; ++i)
    {
        element[i] = (int *)malloc((nVariables + 1) * sizeof(int));
        element[i][0] = 0;
        for (int j = 1; j <= nVariables; ++j)
        {
            if (i + 1 == j)
            {
                element[i][j] = 4;
            }
            else
            {
                element[i][j] = DONT_CARE;
            }
        }
    }

    // for (int i = 0; i < nElements; ++i)
    // {
    //     printf("Element %d: [%d", i, element[i][0]);
    //     for (int j = 1; j <= nVariables; ++j)
    //     {
    //         printf(" %d", element[i][j]);
    //     }
    //     printf(": %ld]\n", 1);
    // }

    initialize();

    domain *d = createDomainBottomUp(bounds, nVariables);
    assert(d != 0);

    forest::policies p(false);
    // p.setPessimistic();

    forest *bdd = d->createForest(false, forest::BOOLEAN, forest::MULTI_TERMINAL, p);

    dd_edge A(bdd);
    dd_edge B(bdd);

    dd_edge *vars = new dd_edge[nVariables];
    FILE_output meddlyout(stdout);
    for (int i = 0; i < nVariables; i++)
    {
        vars[i] = A;
        bdd->createEdge(element + i, 1, vars[i]);
        // vars[i].show(meddlyout, 2);
    }

    bdd->createEdge(true, B);

    auto start = chrono::system_clock::now();

    // Apply演算のAndだけを図りたいのでここだけ時間を図っています。
    for (int i = 0; i < nVariables; i++)
    {
        B *= vars[i];
    }

    auto end = chrono::system_clock::now();

    // B.show(meddlyout, 2);
    // bdd->showInfo(meddlyout);

    auto dur = end - start;
    auto msec = chrono::duration_cast<chrono::nanoseconds>(dur).count();
    ofstream ofs("meddly_apply_10000_and_results.csv", ios::app);
    ofs << msec << "," << endl;
    cout << msec << " nano sec \n";
}
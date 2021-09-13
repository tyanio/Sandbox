#include <sys/types.h>
#include <sys/time.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "cudd.h"
#include <chrono>

using namespace std;

int main(int argc, char *argv[])
{
    DdManager *gbm;                                                /* Global BDD manager. */
    gbm = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0); /* Initialize a new BDD manager. */
    DdNode *bdd, *var, *tmp_neg, *tmp;
    bdd = Cudd_ReadOne(gbm); /*Returns the logic one constant of the manager*/
    Cudd_Ref(bdd);           /*Increases the reference count of a node*/

    auto start = chrono::system_clock::now();

    for (int j = 10000; j >= 0; j--)
    {
        var = Cudd_bddIthVar(gbm, j);     /*Create a new BDD variable*/
        tmp = Cudd_bddAnd(gbm, var, bdd); /*Perform AND Boolean operation*/
        Cudd_Ref(tmp);
        Cudd_RecursiveDeref(gbm, bdd);
        bdd = tmp;
    }

    auto end = chrono::system_clock::now();
    auto dur = end - start;
    Cudd_Quit(gbm);
    cout << "time: " << chrono::duration_cast<chrono::nanoseconds>(dur).count() << " nano secs." << endl;

    return 0;
}
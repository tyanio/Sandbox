#include <sys/types.h>
#include <sys/time.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "cudd.h"
#include <chrono>

using namespace std;

int main(int argc, char *argv[])
{
    auto nVariable = 10000;
    DdManager *gbm;                                                /* Global BDD manager. */
    gbm = Cudd_Init(0, 0, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0); /* Initialize a new BDD manager. */
    DdNode *bdd, *var, *tmp_neg, *tmp;
    bdd = Cudd_bddIthVar(gbm, nVariable);
    Cudd_Ref(bdd);           /*Increases the reference count of a node*/

    auto start = chrono::system_clock::now();

    for (int j = nVariable-1; j >= 0; j--)
    {
        var = Cudd_bddIthVar(gbm, j);    /*Create a new BDD variable*/
        tmp = Cudd_bddOr(gbm, var, bdd); /*Perform AND Boolean operation*/
        Cudd_Ref(tmp);
        Cudd_RecursiveDeref(gbm, bdd);
        bdd = tmp;
    }

    auto end = chrono::system_clock::now();
    auto dur = end - start;

    ofstream ofs("cudd_c_apply_10000_or_results.csv", ios::app);
    ofs << chrono::duration_cast<chrono::nanoseconds>(dur).count() << "," << endl;
    cout << "time: " << chrono::duration_cast<chrono::nanoseconds>(dur).count() << " nano secs." << endl;

    // Cudd_PrintDebug(gbm, bdd, nVariable, 4);
    Cudd_Quit(gbm);

    return 0;
}
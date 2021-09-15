#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include "cuddObj.hh"

using namespace std;

void random_vars(int, BDD &, Cudd &, int);

int main()
{
    const int nVariables = 10000;
    auto msec = 0;

    Cudd cudd;
    for (int i = 0; i < nVariables; i++)
    {
        cudd.bddVar();
    }
    auto start = chrono::system_clock::now();

    BDD f = cudd.bddVar(0);

    for (int i = 1; i < nVariables; i++)
    {
        f = f + cudd.bddVar(i);
    }

    auto end = chrono::system_clock::now();
    auto dur = end - start;

    // Cudd_PrintDebug(cudd.getManager(), f.getNode(), nVariables, 3);

    ofstream ofs("cudd_c++_apply_10000_or_results.csv", ios::app);
    ofs << chrono::duration_cast<chrono::nanoseconds>(dur).count() << "," << endl;
    cout << chrono::duration_cast<chrono::nanoseconds>(dur).count() << "nano secs" << endl;
}
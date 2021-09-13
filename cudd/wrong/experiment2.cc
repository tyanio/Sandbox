#include <stdio.h>
#include <iostream>
#include <chrono>
#include "cuddObj.hh"

using namespace std;

void random_vars(int, BDD &, Cudd &, int);

int main()
{
    const int nVariables = 10000;
    const int loops = 5;
    auto msec = 0;

    Cudd cudd;
    for (int i = 0; i < nVariables; i++)
    {
        cudd.bddVar();
    }

    BDD f = cudd.bddVar(0);
    for (int i = 1; i < nVariables; i++)
    {
        f = f * cudd.bddVar(i);
    }

    // Cudd_PrintDebug(cudd.getManager(), f.getNode(), nVariables, 3);

    for (int i = 0; i < loops; i++)
    {
        auto start = chrono::system_clock::now();
        f = cudd.bddVar(0);
        for (int i = 1; i < nVariables; i++)
        {
            f = f * cudd.bddVar(i);
        }
        auto end = chrono::system_clock::now();
        auto dur = end - start;
        msec += chrono::duration_cast<chrono::microseconds>(dur).count();
        // Cudd_PrintDebug(cudd.getManager(), f.getNode(), nVariables, 3);
    }

    // Cudd_PrintDebug(cudd.getManager(), f.getNode(), nVariables, 3);

    msec /= loops;
    cout << "average: " << msec << " micro sec \n";
}
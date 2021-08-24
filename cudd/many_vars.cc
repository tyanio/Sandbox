#include <stdio.h>
#include <iostream>
#include <chrono>
#include "cuddObj.hh"

using namespace std;

int main()
{
    int loops = 2;
    auto msec = 0;

    for (int i = 0; i < loops; i++)
    {
        Cudd cudd;
        BDD f = cudd.bddVar();
        int nVariables = 10000;

        auto start = chrono::system_clock::now();

        for (int i = 0; i < nVariables; i++)
        {
            f = f * cudd.bddVar();
        }

        auto end = chrono::system_clock::now();
        auto dur = end - start;
        msec += chrono::duration_cast<chrono::microseconds>(dur).count();
    }

    msec /= loops;
    cout << msec << "micro sec \n";

    // Cudd_PrintDebug(cudd.getManager(), f.getNode(), 1000, 3);
}
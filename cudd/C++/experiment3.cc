#include <stdio.h>
#include <iostream>
#include <chrono>
#include "cuddObj.hh"

using namespace std;

void random_vars(int, BDD &, Cudd &, int);

int main()
{
    const int nVariables = 10000;
    auto msec = 0;

    // 変数を用意する
    Cudd cudd;
    for (int i = 0; i < nVariables; i++)
    {
        cudd.bddVar();
    }

    // 各変数をAND演算でつなげたBDDをfに格納
    BDD f = cudd.bddVar(0);
    for (int i = 1; i < nVariables; i++)
    {
        // f = f * cudd.bddVar(i);
        f = f.And(cudd.bddVar(i));
    }
    // Cudd_PrintDebug(cudd.getManager(), f.getNode(), nVariables, 3);

    // 各変数をNOR演算でつなげたBDDをgに格納
    BDD g = cudd.bddVar(0);
    for (int i = 1; i < nVariables; i++)
    {
        g = g.Nor(cudd.bddVar(i));
    }
    // Cudd_PrintDebug(cudd.getManager(), g.getNode(), nVariables, 3);

    // fとgをORでつなげた際の時間を計測
    auto start = chrono::system_clock::now();

    BDD h = f + g;

    auto end = chrono::system_clock::now();
    auto dur = end - start;
    msec += chrono::duration_cast<chrono::microseconds>(dur).count();
    // Cudd_PrintDebug(cudd.getManager(), h.getNode(), nVariables, 3);

    cout << "average: " << msec << " micro sec \n";
}
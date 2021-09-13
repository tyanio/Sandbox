#include <stdio.h>
#include <iostream>
#include <chrono>
#include "cuddObj.hh"

using namespace std;

void and_vars(int, BDD &, Cudd &, int);
void or_vars(int, BDD &, Cudd &, int);
void random_vars(int, BDD &, Cudd &, int);

int main()
{
    int loops = 5;
    auto msec = 0;

    Cudd cudd;
    BDD f = cudd.bddVar();
    BDD bdds[2] = {f, f};

    // for (int i = 0; i < 2; i++)
    // {
    //     int nVariables = 10000;
    //     and_vars(nVariables, bdds[i], cudd, i);
    // }

    int nVariables = 10000;
    random_vars(nVariables, bdds[0], cudd, 0);
    random_vars(nVariables, bdds[1], cudd, 1);

    for (int i = 0; i < loops; i++)
    {
        auto start = chrono::system_clock::now();

        BDD h = bdds[0] + !bdds[1];

        auto end = chrono::system_clock::now();
        auto dur = end - start;
        cout << chrono::duration_cast<chrono::microseconds>(dur).count() << endl;
        msec += chrono::duration_cast<chrono::microseconds>(dur).count();

        // Cudd_PrintDebug(cudd.getManager(), h.getNode(), 1000, 3);
    }

    msec /= loops;
    cout << msec << "micro sec \n";
}

void and_vars(int nVariables, BDD &f, Cudd &cudd, int loops)
{
    for (int i = 1; i < nVariables; i++)
    {
        if (loops == 0)
        {
            f = f * cudd.bddVar();
        }
        else
        {
            f = f * cudd.bddVar(i);
        }
    }
}

void or_vars(int nVariables, BDD &f, Cudd &cudd, int loops)
{
    for (int i = 1; i < nVariables; i++)
    {
        if (loops == 0)
        {
            f = f + cudd.bddVar();
        }
        else
        {
            f = f + cudd.bddVar(i);
        }
    }
}

void random_vars(int nVariables, BDD &f, Cudd &cudd, int loops)
{
    for (int i = 1; i < nVariables; i++)
    {
        auto x = rand();
        if (loops == 0)
        {
            switch (x % 4)
            {
            case 0:
                f = f * cudd.bddVar();
                break;
            case 1:
                f = f + cudd.bddVar();
                break;
            case 2:
                f = f * !(cudd.bddVar());
                break;
            case 3:
                f = f + !(cudd.bddVar());
                break;
            default:
                break;
            }
        }
        else
        {
            switch (x % 4)
            {
            case 0:
                f = f * cudd.bddVar(i);
                break;
            case 1:
                f = f + cudd.bddVar(i);
                break;
            case 2:
                f = f * !(cudd.bddVar(i));
                break;
            case 3:
                f = f + !(cudd.bddVar(i));
                break;
            default:
                break;
            }
        }
    }
}
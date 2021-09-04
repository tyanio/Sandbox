#include <stdio.h>
#include <iostream>
#include <chrono>
#include "cuddObj.hh"

using namespace std;

void random_vars(int, BDD &, Cudd &, int);

int main()
{
    const int nVariables = 10000;
    const int loops = 1;
    auto msec = 0;

    Cudd cudd;
    for (int i = 0; i < nVariables; i++)
    {
        cudd.bddVar();
    }

    for (int i = 0; i < loops; i++)
    {
        auto start = chrono::system_clock::now();

        BDD f = cudd.bddVar(0);

        for (int i = 1; i < nVariables; i++)
        {
            f = f * cudd.bddVar(i);
        }

        auto end = chrono::system_clock::now();

        // f.PrintCover();

        auto dur = end - start;
        // cout << chrono::duration_cast<chrono::microseconds>(dur).count() << endl;
        msec += chrono::duration_cast<chrono::microseconds>(dur).count();

        // Cudd_PrintDebug(cudd.getManager(), f.getNode(), nVariables, 3);
    }

    msec /= loops;
    cout << "average: " << msec << " micro sec \n";
}

// void random_vars(int nVariables, BDD &f, Cudd &cudd, int loops)
// {
//     for (int i = 1; i < nVariables; i++)
//     {
//         auto x = rand();
//         if (loops == 0)
//         {
//             switch (x % 4)
//             {
//             case 0:
//                 f = f * cudd.bddVar();
//                 break;
//             case 1:
//                 f = f + cudd.bddVar();
//                 break;
//             case 2:
//                 f = f * !(cudd.bddVar());
//                 break;
//             case 3:
//                 f = f + !(cudd.bddVar());
//                 break;
//             default:
//                 break;
//             }
//         }
//         else
//         {
//             switch (x % 4)
//             {
//             case 0:
//                 f = f * cudd.bddVar(i);
//                 break;
//             case 1:
//                 f = f + cudd.bddVar(i);
//                 break;
//             case 2:
//                 f = f * !(cudd.bddVar(i));
//                 break;
//             case 3:
//                 f = f + !(cudd.bddVar(i));
//                 break;
//             default:
//                 break;
//             }
//         }
//     }
// }
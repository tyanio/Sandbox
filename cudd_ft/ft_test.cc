#include <stdio.h>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>

#include "gtest/gtest.h"
#include "cuddObj.hh"

using namespace std;

vector<double> linrange(double x0, double x1, uint64_t n)
{
    vector<double> ans(n, 0.0);
    double x = x0;
    double d = (x1 - x0) / double(n - 1);
    for (int i = 0; i < n; i++)
    {
        ans[i] = x;
        x += d;
    }
    return ans;
}

std::vector<std::vector<std::string>> Ftmcs(Cudd m, BDD f, vector<BDD> b)
{
    vector<vector<string>> result;
    BDD r = f;
    while (r != m.bddZero())
    {
        
    }
    
}

struct minPath{
    int len;
    vector<vector<string>> set;
};

tuple<vector<vector<string>>, BDD> ftmcs(Cudd m, vector<BDD> vars, BDD f){
    vector<string> path(vars.size());
    vector<vector<string>> empty(0);
    struct minPath s = {
        vars.size(),
        empty
    };
    BDD bddres = m.bddZero();
    getMinPath();
}

void getMinPath(Cudd & m, BDD & f, vector<string> & path, struct minPath & s){
    if (s.len < path.size()){
        return;
    }

    if(f == m.bddOne()){
        if(s.len > path.size()){
            s.len = path.size();
            s.set = vector<vector<string>>({path});
        }
        else if(s.len == path.size()){
            s.set.push_back(path);
        }
    }
    else if(f != m.bddOne() && f != m.bddZero()){
        getMinPath(m, f.)
    }

}

TEST(MyTestCase, TestFT1)
{
    vector<int> labels{0, 1, 2, 3, 4, 5, 6, 7};
    vector<BDD> vars{labels.size()};

    Cudd mgr;

    for (int i = 0; i < labels.size(); i++)
    {
        vars[i] = mgr.bddVar();
    }

    BDD ft = vars[2] +
             (vars[4] * vars[0] * vars[7]) +
             (vars[3] * vars[5] * vars[2]) +
             (vars[1] * vars[7] * vars[3]) +
             (vars[5] * vars[7] * vars[3]) +
             (vars[1] * vars[2] * vars[6]);

    cout << Ftmcs(mgr, ft, vars);
}

TEST(MyTestCase, Test001)
{
    vector<double> ans{0.0, 0.25, 0.5, 0.75, 1.0};
    EXPECT_EQ(ans, linrange(0.0, 1.0, 5));
}

tuple<vector<int>, vector<vector<int>>> makeTestData()
{
    vector<vector<double>> data = {
        {0.2799439284864673, 0.019039179685146124},
        {0.17006659269016278, 0.26812585079180584},
        {0.37160535186424815, 0.28336464179809084},
        {0.39279646612146735, 0.2789501222723816},
        {0.44911286867346534, 0.2067605663915406},
        {0.505207192733002, 0.07778618522601977},
        {0.381127966318632, 0.36580119057192695},
        {0.14314120834324617, 0.5282542334011777},
        {0.2236688207291726, 0.5027191237033151},
        {0.5865981007905481, 0.05016684053503706},
        {0.2157117712338983, 0.5699545901561343},
        {0.6600618683347792, 0.006513992462842788},
        {0.6964756269215944, 0.031164261499776913},
        {0.5572474263734104, 0.5457354609512821},
        {0.38370575109517757, 0.6870518034076929},
        {0.14047278702240318, 0.8099471630562083},
        {0.6117903795750386, 0.6200985639530681},
        {0.8350140149860443, 0.26002375370524433},
        {0.621745085645081, 0.6249760808944675},
        {0.9223171788742697, 0.040441694559945285},
        {0.40157225733130186, 0.8622123559544623},
        {0.5654235033016655, 0.7840149804945578},
        {0.8605048496383341, 0.48642029259985065},
        {0.5627138851056968, 0.8499394786290626},
        {0.7124617313668333, 0.7347698978106127},
        {0.9656307414336753, 0.3647058735973785},
        {0.9944967296698335, 0.548297306757731},
        {0.5733819926662398, 0.9813641372820436},
        {0.9236020954856745, 0.7540471034450749},
        {0.8910887808888235, 0.8901974734237881},
    };
    vector<int> labels = {13, 19, 2, 14, 29, 23, 3, 26, 25, 7, 9, 27, 12, 30, 17, 24, 8, 4, 18, 5, 20, 21, 28, 1, 16, 10, 15, 6, 11, 22};
    vector<double> ddx = linrange(0, 1, 30);
    vector<double> ddy = linrange(0, 1, 30);
    vector<vector<int>> result;

    for (double x : ddx)
    {
        for (double y : ddy)
        {
            vector<int> v;
            for (int i = 0; i < data.size(); i++)
            {
                double tmpx = x - data[i][0];
                double tmpy = x - data[i][1];
                if (tmpx * tmpx + tmpy * tmpy < 0.3 * 0.3)
                {
                    v.push_back(labels[i]);
                }
            }
            result.push_back(v);
        }
    }

    return forward_as_tuple(labels, result);
}
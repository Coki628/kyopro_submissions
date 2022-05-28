/*
・きっちり自力AC！
・グラフ
・次数が多い方から貪欲に。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

class Solution {
public:
    long long maximumImportance(int N, vector<vector<int>>& roads) {
        ll M = roads.size();
        vvi nodes(N);
        rep(i, M) {
            ll u = roads[i][0], v = roads[i][1];
            nodes[u].eb(v);
            nodes[v].eb(u);
        }

        vector<ll> V;
        rep(i, N) {
            V.eb(nodes[i].size());
        }
        sort(ALL(V));
        ll res = 0;
        rep(i, N) {
            res += V[i] * (i+1);
        }
        return res;
    }
};

#ifdef __LOCAL
    int main() {
        // Solution sol;
        // auto res = sol.funcName();
        // print(res);
        return 0;
    }
#endif

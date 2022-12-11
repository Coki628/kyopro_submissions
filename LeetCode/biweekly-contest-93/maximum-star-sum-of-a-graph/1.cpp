/*
・きっちり自力AC。
・りとこQ2にしてはちょっと考察が要る感じの。
　利得が高い頂点から順に周辺見てまだK個未満なら足す。マイナスなら無視(1ペナ)。
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
    int maxStarSum(vector<int> &A, vector<vector<int>> &edges, int K) {
        int N = A.size();
        int M = edges.size();
        vvi nodes(N);
        rep(i, M) {
            int u = edges[i][0];
            int v = edges[i][1];
            nodes[u].eb(v);
            nodes[v].eb(u);
        }

        vector<pii> AI;
        rep(i, N) {
            AI.eb(A[i], i);
        }
        sort(AI.rbegin(), AI.rend());
        vector<int> C(N), sm = A;
        for (auto [a, u] : AI) {
            if (a <= 0)
                continue;
            for (auto v : nodes[u]) {
                if (C[v] < K) {
                    C[v]++;
                    sm[v] += a;
                }
            }
        }
        return max(sm);
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

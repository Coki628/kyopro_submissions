/*
参考：https://twitter.com/laycrs/status/1515359612567896066
・自力ならず。りとこの4問目は解けないと悔しいね…。
・グラフ、工夫して全探索
・真ん中の辺を固定して、両側をどうするか全探索する。
　ここまでは自分でもやろうと少しは検討したんだけど、
　両側に繋がる辺が多い時無理かと思ってやめてしまった。
　実際には、予めソートしてそれぞれ上位3つとかだけ見るようにすればよかった。
　確かにこれならごく小さい2重ループで済むね…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

class Solution {
public:
    int maximumScore(vector<int>& A, vector<vector<int>>& edges) {
        ll N = A.size();
        ll M = edges.size();
        vvpll nodes(N);
        rep(i, M) {
            int u = edges[i][0], v = edges[i][1];
            nodes[u].eb(A[v], v);
            nodes[v].eb(A[u], u);
        }
        rep(i, N) {
            sort(nodes[i].rbegin(), nodes[i].rend());
        }

        ll ans = -1;
        rep(i, M) {
            int u = edges[i][0], v = edges[i][1];
            ll a1 = A[u], a2 = A[v];
            rep(j, min((int)nodes[u].size(), 3)) {
                auto [a3, w] = nodes[u][j];
                if (w == u or w == v) continue;
                rep(k, min((int)nodes[v].size(), 3)) {
                    auto [a4, x] = nodes[v][k];
                    if (x == u or x == v or x == w) continue;
                    chmax(ans, a1+a2+a3+a4);
                }
            }
        }
        return ans;
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

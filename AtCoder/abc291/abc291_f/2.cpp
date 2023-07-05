/*
・今回は自力AC！方針、なんとなく思い出せたけど、練習として書いた。
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

#include "graph/bfs.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<string> S(N);
    cin >> S;
    vvi nodes(N), revs(N);
    rep(i, N) {
        rep(j, M) {
            if (S[i][j] == '1') {
                nodes[i].eb(i + j + 1);
                revs[i + j + 1].eb(i);
            }
        }
    }

    auto dist1 = bfs(nodes, {0});
    auto dist2 = bfs(revs, {(int)N - 1});
    vector<ll> ans;
    rep(k, 1, N - 1) {
        ll res = INF;
        rep(u, max(k - M, 0LL), k) {
            if (dist1[u] >= INF) continue;
            rep(j, M) {
                if (S[u][j] == '1') {
                    ll v = u + j + 1;
                    if (v <= k) continue;
                    if (dist2[v] >= INF) continue;
                    chmin(res, dist1[u] + dist2[v] + 1);
                }
            }
        }
        ans.pb(res < INF ? res : -1);
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}

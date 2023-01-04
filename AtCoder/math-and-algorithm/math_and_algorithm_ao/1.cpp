/*
・二部グラフ判定、DFS
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<ll> C(N, -1);
    auto dfs = [&](auto&& f, ll u, ll c) -> bool {
        if (C[u] != -1) {
            return C[u] == c;
        }
        C[u] = c;
        for (auto v : nodes[u]) {
            if (!f(f, v, 1-c)) {
                return false;
            }
        }
        return true;
    };

    rep(i, N) {
        if (C[i] == -1) {
            if (!dfs(dfs, i, 0)) {
                No();
                return;
            }
        }
    }
    Yes();
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

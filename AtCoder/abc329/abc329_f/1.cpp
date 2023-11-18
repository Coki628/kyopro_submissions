/*
・きっちり自力AC！
・マージテク
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<ll> C(N);
    cin >> C;
    vector<set<ll>> adj(N);
    rep(i, N) {
        adj[i].insert(C[i]);
    }
    rep(i, Q) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        if (adj[a].size() > adj[b].size()) {
            swap(adj[a], adj[b]);
        }
        for (auto v : adj[a]) {
            adj[b].insert(v);
        }
        adj[a].clear();
        ll res = adj[b].size();
        print(res);
    }
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

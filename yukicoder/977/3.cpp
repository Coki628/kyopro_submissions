/*
ライブラリ整備：Low Link
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "graph/LowLink.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    UnionFind uf(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        nodes[u].eb(v);
        nodes[v].eb(u);
        uf.merge(u, v);
    }

    if (uf.size() == 1) {
        print("Bob");
    } else if (uf.size() >= 3) {
        print("Alice");
    } else {
        LowLink lowlink(nodes);
        if (lowlink.has_bridge()) {
            print("Alice");
        } else {
            print("Bob");
        }
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

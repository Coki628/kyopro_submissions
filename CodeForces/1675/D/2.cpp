/*
参考：https://codeforces.com/contest/1675/submission/155941263
・さすがに冗長だったので簡潔にしたものを。
・木グラフ、DFS
・DFSで前からパス作ってくだけ。これだけでいい…。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto P = LIST(N);
    rep(i, N) P[i]--;

    vvi nodes(N);
    ll r = -1;
    rep(i, N) {
        if (P[i] != i) {
            nodes[i].eb(P[i]);
            nodes[P[i]].eb(i);
        } else {
            r = i;
        }
    }

    vvi ans;
    vector<int> cur;
    auto dfs = [&](auto&& f, int u, int prv) -> void {
        cur.eb(u);
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
        }
        if (cur.size()) {
            ans.eb(cur);
            cur.clear();
        }
    };
    dfs(dfs, r, -1);

    print(ans.size());
    rep(i, ans.size()) {
        print(ans[i].size());
        rep(u, ans[i].size()) ans[i][u]++;
        print(ans[i]);
    }
    print();
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}

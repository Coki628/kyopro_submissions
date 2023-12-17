/*
・きっちり自力AC！
・木DP
・問題設定を整理すると、根からの部分木のうち一番大きいものを残すが最善と分かる。
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
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    if (nodes[0].size() == 1) {
        print(1);
        return;
    }
    vector<ll> sz(N, 1), vec;
    auto dfs = [&](auto &&f, ll u, ll prv) -> void {
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            f(f, v, u);
            sz[u] += sz[v];
            if (u == 0) {
                vec.eb(sz[v]);
            }
        }
    };
    dfs(dfs, 0, -1);
    sort(ALL(vec));
    assert(vec.size() >= 2);
    ll ans = 0;
    rep(i, vec.size() - 1) {
        ans += vec[i];
    }
    ans++;
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

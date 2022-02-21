/*
・自力AC！
・木DP、オイラーツアー
・問題文の解釈がむずい。
　オイラーツアーっぽいやつで、次数が2以上だったとこでcnt++、
　入りで左端、出で右端を決める。
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
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<pii> ans(N);
    ll cur = 1;
    auto dfs = [&](auto&& f, ll u, ll prv) -> void {
        ans[u].first = cur;
        ll i = 0;
        for (auto v : nodes[u]) {
            if (v == prv) continue;
            i++;
            if (i >= 2) cur++;
            f(f, v, u);
        }
        ans[u].second = cur;
    };
    dfs(dfs, 0, -1);
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

/*
・きっちり自力AC！今日ここまで速かったのは良い感じ。
・DFSとBFS。
　T1は一直線グラフっぽくしたいし、T2はウニグラフっぽくしたい気持ちになると、
　そうするといいんじゃないかって気になる。
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

    vector<pll> ans1;
    vector<bool> visited1(N);
    auto dfs = [&](auto&& f, ll u) -> void {
        for (auto v : nodes[u]) {
            if (visited1[v]) continue;
            visited1[v] = true;
            ans1.eb(u+1, v+1);
            f(f, v);
        }
    };
    visited1[0] = true;
    dfs(dfs, 0);

    vector<pll> ans2;
    vector<bool> visited2(N);
    visited2[0] = true;
    queue<ll> que;
    que.push(0);
    while (que.size()) {
        auto u = que.front(); que.pop();
        for (auto v : nodes[u]) {
            if (visited2[v]) continue;
            visited2[v] = true;
            ans2.eb(u+1, v+1);
            que.push(v);
        }
    }

    print(ans1);
    print(ans2);
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

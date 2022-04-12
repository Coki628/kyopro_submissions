/*
・dojo set_d_6_5
・きっちり自力AC！
・全方位木DP、数え上げ
・葉から順に番号を降順に割り振っていって、頂点集合をマージする時に、
　並べ方を二項係数で適切に数え上げる。集合の頂点数が欲しいので部分木の頂点数も持つ。
　これで根が1になる通り数を求める木DPが作れるので、遷移を全方位に乗せる。
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

#include "graph/ReRooting.hpp"

void solve() {
    ll N;
    cin >> N;
    ModTools<mint> mt(N);
    struct Node {
        mint cnt;
        ll sz;
    };
    auto f1 = [&](Node a, Node b) -> Node {
        return { a.cnt*b.cnt*mt.nCr(a.sz+b.sz, b.sz), a.sz+b.sz };
    };
    auto f2 = [](Node a, int _) -> Node {
        return { a.cnt, a.sz+1 };
    };
    auto rr = get_rerooting(N, f1, f2, Node{1, 0}, 0);
    // vvi nodes(N);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        rr.add_edge(u, v, 0);
        // nodes[u].eb(v);
        // nodes[v].eb(u);
    }
    auto res = rr.build();
    for (auto a : res) print(a.cnt);
    // rep(i, N) {
    //     vector<mint> dp(N, 1);
    //     vector<ll> sz(N);
    //     auto dfs = [&](auto&& f, ll u, ll prv) -> void {
    //         for (auto v : nodes[u]) {
    //             if (v == prv) continue;
    //             f(f, v, u);
    //             sz[u] += sz[v] + 1;
    //             dp[u] *= dp[v] * mt.nCr(sz[u], sz[v]+1);
    //         }
    //     };
    //     dfs(dfs, i, -1);
    //     print(dp[i]);
    // }
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

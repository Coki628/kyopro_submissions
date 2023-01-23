/*
・自力AC！
・ダイクストラ、超頂点
・当時嘘解法ACしてそのままになってたので、ちゃんとした解法で通しておいた。
　ワープ移動中みたいなもう1つのグリッドを作る。
　想定解通りの超頂点の方針がすぐ立ったのでいい感じ。
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

#include "graph/_dijkstra.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    ll N = H * W;
    vector<vector<pair<int, int>>> nodes(N * 2);
    rep(h, H) {
        rep(w, W - 1) {
            ll c;
            cin >> c;
            ll i = gridtoid(h, w, W);
            ll j = gridtoid(h, w + 1, W);
            nodes[i].eb(j, c);
            nodes[j].eb(i, c);
        }
    }
    rep(h, H - 1) {
        rep(w, W) {
            ll c;
            cin >> c;
            ll i = gridtoid(h, w, W);
            ll j = gridtoid(h + 1, w, W);
            nodes[i].eb(j, c);
            nodes[j + N].eb(i + N, 1);
            // rep(h2, h, -1, -1) {
            //     i = gridtoid(h2, w, W);
            //     nodes[j].eb(i, (h - h2 + 2));
            // }
        }
    }
    rep(h, H) {
        rep(w, W) {
            ll i = gridtoid(h, w, W);
            nodes[i].eb(i + N, 1);
            nodes[i + N].eb(i, 0);
        }
    }

    auto res = dijkstra(nodes, 0);
    ll ans = res[N - 1];
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

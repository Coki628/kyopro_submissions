/*
・JOI埋め
・自力AC！
・ダイクストラ、辺の張り方を工夫
・スイッチのある部屋と始点終点だけを頂点とする。
　スイッチ部屋は切り替え2通りで別の頂点として扱い、コスト1で繋ぐ。
　同じ行列間の移動は隣り合う頂点とだけ、距離をコストにして繋ぐ。
　最初は縦移動からのスタートなので、始点はそっち側とだけ繋ぐ。
　サンプルが落ちるようになっていて優しい。
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
    ll M, N, K;
    cin >> M >> N >> K;
    vvpll X(N), Y(M);
    rep(i, K) {
        ll x, y;
        cin >> x >> y;
        x--; y--;
        X[y].eb(x, i);
        Y[x].eb(y, i);
    }

    vvpil nodes(K*2+2);
    ll s = K * 2;
    ll t = K * 2 + 1;
    rep(y, N) {
        sort(ALL(X[y]));
        rep(i, 1, X[y].size()) {
            auto [x1, xi1] = X[y][i-1];
            auto [x2, xi2] = X[y][i];
            nodes[xi1].eb(xi2, x2-x1);
            nodes[xi2].eb(xi1, x2-x1);
        }
    }
    rep(x, M) {
        sort(ALL(Y[x]));
        rep(i, 1, Y[x].size()) {
            auto [y1, yi1] = Y[x][i-1];
            auto [y2, yi2] = Y[x][i];
            nodes[K+yi1].eb(K+yi2, y2-y1);
            nodes[K+yi2].eb(K+yi1, y2-y1);
        }
    }
    rep(i, K) {
        nodes[i].eb(K+i, 1);
        nodes[K+i].eb(i, 1);
    }
    // if (X[0].size()) {
    //     auto [x, xi] = X[0][0];
    //     nodes[s].eb(xi, x);
    // }
    if (X[N-1].size()) {
        auto [x, xi] = X[N-1].back();
        nodes[xi].eb(t, M-x-1);
    }
    if (Y[0].size()) {
        auto [y, yi] = Y[0][0];
        nodes[s].eb(K+yi, y);
    }
    if (Y[M-1].size()) {
        auto [y, yi] = Y[M-1].back();
        nodes[K+yi].eb(t, N-y-1);
    }
    auto res = dijkstra(nodes, s, t);
    ll ans = res[t] < INF ? res[t] : -1;
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

/*
参考：https://twitter.com/milkcoffeen/status/1604769484778090505
・二部グラフ判定、UF
・2N頂点のUFで二部グラフ判定を簡潔に書ける。
　頂点を二部の両側に分けて作る感じで、辺を張る時はこれに公差させる感じで張る。
　すると、同じ頂点の二部が連結になっていないかチェックすることで、二部グラフ判定ができる。
・だいぶ前にこの2N頂点でUFするやつやったことあって、
　その時も思ったけどこのグラフ構築のやり方頭いいよねー。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vvi nodes(N);
    UnionFind uf(N * 2);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--;
        v--;
        uf.merge(u, N + v);
        uf.merge(v, N + u);
    }

    vector<ll> C(N);
    rep(i, N) {
        if (uf.same(i, i + N)) {
            print(0);
            return;
        }
        C[uf.find(i)]++;
    }
    ll ans = N * (N - 1) / 2 - M;
    rep(i, N) {
        ans -= C[i] * (C[i] - 1) / 2;
    }
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

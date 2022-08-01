/*
参考：https://twitter.com/mkawa2/status/1553739359454519297
・自力ならず。。こういうのはね、無理な時は無理だよ。
・グラフ、天才数え上げ
・よくよく考察すると、次数が偶数の頂点をどういじっても
　「異なる色で塗られた頂点を結ぶ辺の本数の偶奇」は変化しないことが分かる。(気付けねぇ…)
　これが分かると、じゃあ次数が奇数の頂点を偶数個選べばいいねとなり、
　これを固定して偶数個を全探索、赤く塗るK個のうち、次数が奇数のをx個、偶数のをK-x個選ぶ通り数、
　みたいにして求めることができる。
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
    ll N, M, K;
    cin >> N >> M >> K;
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    vector<ll> C(2);
    rep(i, N) {
        C[nodes[i].size()%2]++;
    }
    ModTools<mint> mt(N);
    mint ans = 0;
    rep(x, 0, N+1, 2) {
        ans += mt.nCr(C[1], x) * mt.nCr(C[0], K-x);
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

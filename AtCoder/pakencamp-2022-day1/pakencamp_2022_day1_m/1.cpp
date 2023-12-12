/*
参考：https://twitter.com/_rniya_/status/1640271268271517696
・ライブラリ整備：区間辺2-SAT
・どこかにverifyできる問題ないかなー、と探したらここに行き着いた。
　部分木に対する条件なので、HLD(オイラーツアー)しとけば区間になる。
　HLD→元頂点への戻し、復元のanswer()までしっかりverifyできて満足。
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

#include "graph/HeavyLightDecomposition.hpp"
#include "graph/RangeEdgedTwoSAT.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, 1, N) {
        ll p;
        cin >> p;
        p--;
        nodes[p].eb(i);
    }
    HeavyLightDecomposition hld(nodes);
    RangeEdgedTwoSAT ts(N);
    ll K;
    cin >> K;
    rep(i, K) {
        ll u, s;
        cin >> u >> s;
        u--;
        ts.a_is_f(hld[u], s);
    }
    vector<ll> A(N);
    cin >> A;
    A--;
    rep(u, N) {
        ll v = A[u];
        ll a = hld[u];
        ll l = hld.in[v];
        ll r = hld.out[v];
        // a=1かつ[l,r)=0がダメ
        ts.add_clause(a, false, l, r, true);
        // a=0かつ[l,r)=1がダメ
        ts.add_clause(a, true, l, r, false);
    }
    if (ts.satisfiable()) {
        string ans(N, '*');
        auto res = ts.answer();
        rep(i, N) {
            if (res[i]) {
                ans[hld.rev[i]] = '1';
            } else {
                ans[hld.rev[i]] = '0';
            }
        }
        print(ans);
    } else {
        print("IMPOSSIBLE");
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

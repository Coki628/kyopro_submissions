/*
参考：https://www.ioi-jp.org/camp/2013/2013-sp-tasks/2013-sp-day2-spy-review.pdf
・JOI埋め
・公式解の方針も確認しておいた。
・オイラーツアー、2次元いもす
・部分木はオイラーツアーで区間になるので、それを用いて2つの木の部分木を2次元いもすに落とし込む。
　通常数列A,Bについて両方の条件を満たす場所を見るような感じを、
　このオイラーツアーの列についてやる。(実装上はHLDの部分木クエリ使った。)
・HLDを木2本について使って平面上の問題にするのは初めてやったので学び合ったな。
　でもそもそも普通の数列でも、この2つの問題を2次元平面上にプロットするやつ、気付かないがちなんだよなー…。
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

#include "graph/HeavyLightDecomposition.hpp"
#include "segment/Imos2D.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvi nodes1(N), nodes2(N);
    ll r1 = -1, r2 = -1;
    rep(i, N) {
        ll p, q;
        cin >> p >> q;
        p-- ; q--;
        if (p == -1) {
            r1 = i;
        } else {
            nodes1[p].eb(i);
        }
        if (q == -1) {
            r2 = i;
        } else {
            nodes2[q].eb(i);
        }
    }

    HeavyLightDecomposition hld1(nodes1, r1), hld2(nodes2, r2);
    Imos2D<int> imos(N+1, N+1);
    rep(i, M) {
        ll r, s;
        cin >> r >> s;
        r--; s--;
        imos.add(hld1.in[r], hld2.in[s], hld1.out[r], hld2.out[s], 1);
    }
    imos.build();

    vector<ll> ans(N);
    rep(u, N) {
        ans[u] = imos.get(hld1.in[u], hld2.in[u]);
    }
    print(ans, '\n');
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

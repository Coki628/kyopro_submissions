/*
・ABC残埋め
・自力AC！やったね。
・クエリ系、BITにぶたん
・まず、最終的に求めたい値Xは決まっているので、他の要素はX未満/X超の2値としていい。
　これをソート処理の度に、X未満,X,X超みたいに配置替えする。
　連続した同じ値はランレングスみたいにまとめて持つ。
　これで1回のソートは定数個の並べ替えみたいになるので、
　後はクエリで指定された区間にあるX未満/X超の個数を適切に取り出したりできればいい。
　BITで値を持ってる。境界付近はちょっと面倒だけど要る分と要らない分に分けて、
　クエリ範囲内と範囲外に分けて置くとしてる。
　削除処理は結構強引に連続BITにぶたんみたいにして値を探してるけど、
　結局まとまった値が分裂するのは1クエリにつきせいぜい定数回なので、
　毎クエリ何10万回も探しに行くことはない(はず)。
・公式解説見たら、遅延セグ木の区間更新で一括削除と置き換えをやってるようだった。
　確かにその方がやりやすかったかも。
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
    ll N, Q, X;
    cin >> N >> Q >> X;
    X--;
    auto P = LIST(N);
    rep(i, N) P[i]--;

    ll xi = find(ALL(P), X) - P.begin();
    BIT<ll> low(N), hi(N);
    rep(i, N) {
        if (P[i] < X) {
            low.add(i, 1);
        }
        if (P[i] > X) {
            hi.add(i, 1);
        }
    }
    rep(_, Q) {
        ll op, l, r;
        cin >> op >> l >> r;
        l--;

        // 境界付近を調整
        ll s = low.bisearch_back(0, l, 1);
        if (s != -1) {
            ll rest = min(l - s, low[s]);
            ll need = low[s] - rest;
            low.add(s, -low[s]+rest);
            low.add(l, need);
        }
        s = low.bisearch_back(l, r-1, 1);
        if (s != -1) {
            ll need = min(r - s, low[s]);
            ll rest = low[s] - need;
            low.add(s, -low[s]+need);
            low.add(r, rest);
        }
        s = hi.bisearch_back(0, l, 1);
        if (s != -1) {
            ll rest = min(l - s, hi[s]);
            ll need = hi[s] - rest;
            hi.add(s, -hi[s]+rest);
            hi.add(l, need);
        }
        s = hi.bisearch_back(l, r-1, 1);
        if (s != -1) {
            ll need = min(r - s, hi[s]);
            ll rest = hi[s] - need;
            hi.add(s, -hi[s]+need);
            hi.add(r, rest);
        }

        bool hasx = l <= xi and xi < r;
        ll lowcnt = low.query(l, r);
        ll hicnt = hi.query(l, r);
        assert(r-l == lowcnt+hicnt+hasx);
        // [l,r)を一旦全削除
        while (1) {
            ll i = low.bisearch_fore(l, r-1, 1);
            if (i == -1) break;
            low.add(i, -low[i]);
        }
        while (1) {
            ll i = hi.bisearch_fore(l, r-1, 1);
            if (i == -1) break;
            hi.add(i, -hi[i]);
        }
        // 左端にまとめて置く
        if (op == 1) {
            ll i = l;
            ll j = l + lowcnt + hasx;
            low.add(i, lowcnt);
            hi.add(j, hicnt);
            if (hasx) {
                xi = j - 1;
            }
        } else {
            ll i = l;
            ll j = l + hicnt + hasx;
            hi.add(i, hicnt);
            low.add(j, lowcnt);
            if (hasx) {
                xi = j - 1;
            }
        }
    }
    ll ans = xi + 1;
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

/*
・これは自力MLE。
　まあこんな20万*20万のbitset通る訳ないとは思ったけどさ。。
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
    UnionFind uf(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        uf.merge(u, v);
    }

    ll K;
    cin >> K;
    vector<bitset<200007>> bs(N);
    rep(i, K) {
        ll x, y;
        cin >> x >> y;
        x--, y--;
        bs[uf.find(x)][i] = 1;
        bs[uf.find(y)][i] = 1;
    }
    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll p, q;
        cin >> p >> q;
        p--, q--;
        if (not uf.same(p, q) and (bs[uf.find(p)] & bs[uf.find(q)]).any()) {
            No();
        } else {
            Yes();
        }
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

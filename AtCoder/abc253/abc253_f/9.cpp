/*
ライブラリ整備：永続BIT
・盆栽を育てたい気分だったので作った。
・永続配列乗せのセグ木よりはずいぶんマシになったけど、それでも1.2秒で1.4GのMLE…。
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

#include "datastructure/PersistentArray.hpp"
#include "datastructure/PersistentBIT.hpp"

void solve() {
    ll H, W, Q;
    cin >> H >> W >> Q;

    PersistentBIT<ll> bit(W+1);
    vector<decltype(bit.dat)::Node*> history(Q);
    vector<pll> upd(H);
    rep(i, Q) {
        history[i] = bit.save();
        ll op;
        cin >> op;
        if (op == 1) {
            ll wl, wr, x;
            cin >> wl >> wr >> x;
            wl--;

            bit.add(wl, x);
            bit.add(wr, -x);
        } elif (op == 2) {
            ll h, x;
            cin >> h >> x;
            h--;

            upd[h] = {i, x};
        } else {
            ll h, w;
            cin >> h >> w;
            h--; w--;

            ll res = upd[h].second + bit.query(0, w+1);
            bit.load(history[upd[h].first]);
            res -= bit.query(0, w+1);
            bit.load(history[i]);
            print(res);
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

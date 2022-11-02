/*
ライブラリ整備：永続セグメント木
・永続配列を使った実装と使い方を合わせた。
　毎回の引数で何世代目かを渡すより、こっちのが直感的で分かりやすいと思ったから。
　速度とかメモリも悪くなったりはしてなさそう。
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

#include "datastructure/PersistentSegmentTree.hpp"

const auto f = [](ll a, ll b) { return a + b; };

void solve() {
    ll H, W, Q;
    cin >> H >> W >> Q;

    auto seg = get_persistent_segment_tree(f, 0LL);
    vector<decltype(seg)::Node*> history(Q+1);
    seg.build(vector<ll>(W+1, 0));
    vector<pll> upd(H);
    rep(i, Q) {
        history[i] = seg.save();
        ll op;
        cin >> op;
        if (op == 1) {
            ll wl, wr, x;
            cin >> wl >> wr >> x;
            wl--;

            seg.update(wl, seg.get(wl)+x);
            seg.update(wr, seg.get(wr)-x);
        } elif (op == 2) {
            ll h, x;
            cin >> h >> x;
            h--;

            upd[h] = {i, x};
        } else {
            ll h, w;
            cin >> h >> w;
            h--; w--;

            ll res = upd[h].second + seg.query(0, w+1);
            seg.load(history[upd[h].first]);
            res -= seg.query(0, w+1);
            seg.load(history[i]);
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

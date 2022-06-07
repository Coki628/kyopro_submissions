/*
参考：https://suisen-cp.github.io/cp-library-cpp/library/datastructure/segment_tree/persistent_lazy_segment_tree.hpp
　　　https://ei1333.github.io/library/structure/segment-tree/persistent-segment-tree.cpp
・ライブラリ整備：永続遅延セグメント木
・頑張って作った。suisenさんのロジックを、うしさんの永続セグ木に移植した。
・これだと20万のN,Qで0.7秒、875MBだった。速度はいいけどやっぱりメモリがきついね。。
・今回は1点加算なので、Monoidからサイズを除いたら、ちょっと良くなって762MB。
　それでもsuisenさんの本家よりメモリ食ってるから、まあ詰めが甘いんだろうけど…。
・あとdecltype使ったら長い型名書かなくてよくなって良かった。
・メモリ食う原因を見つけたので修正。事前メモリ確保してるのにnewしてる箇所があるのがいけなかった。
　そこをちゃんと事前取得したpoolから取るようにしたら、0.49秒メモリ587MBまで改善。いい感じ。
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

#include "segment/PersistentLazySegmentTree.hpp"

// 1点加算・区間和取得
auto f = [](ll a, ll b) -> ll { return a + b; };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = 0;
const ll E = 0;

void solve() {
    ll H, W, Q;
    cin >> H >> W >> Q;

    auto seg = get_persistent_lazy_segment_tree(f, g, h, T, E);
    seg.init_pool(15000000);
    vector<decltype(seg)::Node*> history(Q+1);
    history[0] = seg.build(vector<ll>(W+1, 0));
    vector<pll> upd(H);
    rep(i, Q) {
        ll op;
        cin >> op;
        history[i+1] = history[i];
        if (op == 1) {
            ll wl, wr, x;
            cin >> wl >> wr >> x;
            wl--;

            history[i+1] = seg.update(history[i+1], wl, wr, x);
        } elif (op == 2) {
            ll h, x;
            cin >> h >> x;
            h--;

            upd[h] = {i, x};
        } else {
            ll h, w;
            cin >> h >> w;
            h--; w--;

            ll res = upd[h].second + seg.get(history[i+1], w) - seg.get(history[upd[h].first], w);
            print(res);
        }
        // seg.print(history[i+1], W+1);
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

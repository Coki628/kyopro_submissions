/*
参考：https://ei1333.github.io/library/structure/segment-tree/persistent-segment-tree.cpp
・ライブラリ整備：永続セグメント木
・TLで話題になってたので履修。これだと先読みなしで解けて、考察半分くらいで済む感じ。
　最後に更新があった時刻と値を、h毎に覚えておいて、
　クエリが来たらその更新の値 + 最新の加算分 - その更新時点での加算分 とやればOK。
　区間加算1点取得なので、遅延なしでもいもすっぽくやれば大丈夫。
・ライブラリの使い方としては、状態の記録・保持・参照がポインタでO(1)なので、
　各クエリ時点での状態全部が、クエリ数分の配列を用意すれば取っておける。
　この配列の値を適切に更新・参照すればいい。
・速度はまあ速くはなくて、20万のN,Qで0.35秒くらい。
　functionのラムダ化とか非再帰かとか、育てる伸び代はありそう。
・とりあえずオレオレメソッドは生やした。
　でもhistory配列の宣言とか要るからautoでラムダって訳にいかなくて、
　非再帰もどうやるか謎っぽかったから、結局ほぼ中身はいじれてない。
・追記。decltype使ったら宣言ちゃんと書かなくてよくなったので、
　書くのも楽だしfunctionなくしてラムダにできたので、良い感じ。
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

#include "segment/PersistentSegmentTree.hpp"

const auto f = [](ll a, ll b) { return a + b; };

void solve() {
    ll H, W, Q;
    cin >> H >> W >> Q;

    auto seg = get_persistent_segment_tree(f, 0LL);
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

            history[i+1] = seg.update(history[i+1], wl, seg.get(history[i+1], wl)+x);
            history[i+1] = seg.update(history[i+1], wr, seg.get(history[i+1], wr)-x);
        } elif (op == 2) {
            ll h, x;
            cin >> h >> x;
            h--;

            upd[h] = {i, x};
        } else {
            ll h, w;
            cin >> h >> w;
            h--; w--;

            ll res = upd[h].second + seg.query(history[i+1], 0, w+1) - seg.query(history[upd[h].first], 0, w+1);
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

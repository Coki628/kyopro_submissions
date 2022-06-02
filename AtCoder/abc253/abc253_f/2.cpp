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

template< typename Monoid >
struct PersistentSegmentTree {
    using F = function< Monoid(Monoid, Monoid) >;

    struct Node {
        Monoid data;
        Node *l, *r;

        Node(const Monoid &data) : data(data), l(nullptr), r(nullptr) {}
    };

    int sz;
    const F f;
    const Monoid M1;

    PersistentSegmentTree(const F f, const Monoid &M1) : f(f), M1(M1) {}

    Node *build(const vector< Monoid > &v) {
        sz = (int) v.size();
        return build(0, (int) v.size(), v);
    }

    Node *merge(Node *l, Node *r) {
        auto t = new Node(f(l->data, r->data));
        t->l = l;
        t->r = r;
        return t;
    }

    Node *build(int l, int r, const vector< Monoid > &v) {
        if(l + 1 >= r) return new Node(v[l]);
        return merge(build(l, (l + r) >> 1, v), build((l + r) >> 1, r, v));
    }

    Node *update(int a, const Monoid &x, Node *k, int l, int r) {
        if(r <= a || a + 1 <= l) {
            return k;
        } else if(a <= l && r <= a + 1) {
            return new Node(x);
        } else {
            return merge(update(a, x, k->l, l, (l + r) >> 1), update(a, x, k->r, (l + r) >> 1, r));
        }
    }

    Node *update(Node *t, int k, const Monoid &x) {
        return update(k, x, t, 0, sz);
    }

    Monoid query(int a, int b, Node *k, int l, int r) {
        if(r <= a || b <= l) {
            return M1;
        } else if(a <= l && r <= b) {
            return k->data;
        } else {
            return f(query(a, b, k->l, l, (l + r) >> 1),
                     query(a, b, k->r, (l + r) >> 1, r));
        }
    }

    Monoid query(Node *t, int a, int b) {
        return query(a, b, t, 0, sz);
    }
};

const auto f = [](ll a, ll b) { return a + b; };

void solve() {
    ll H, W, Q;
    cin >> H >> W >> Q;

    vector<PersistentSegmentTree<ll>::Node*> history(Q+1);
    PersistentSegmentTree<ll> seg(f, 0LL);
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

            history[i+1] = seg.update(history[i+1], wl, seg.query(history[i+1], wl, wl+1)+x);
            history[i+1] = seg.update(history[i+1], wr, seg.query(history[i+1], wr, wr+1)-x);
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

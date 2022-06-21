/*
参考：https://nyaannyaan.github.io/library/segment-tree/segment-tree-beats-abstract.hpp
　　　https://smijake3.hatenablog.com/entry/2019/04/28/021457
・ライブラリ整備：抽象化Beats
・Nyaanさんのを。とりあえずchmin,chmaxのNodeを作ってみた。
・ついでにやっとBeatsのお気持ちを理解してきた。
　max,2nd max,maxの個数,を持つことで、更新する値xが2nd max超max未満だった時に
　chminで変化する量が分かるから、この時に限って更新する。
　そうでなければ子ノードを見に行く、ってやるのね。
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

#include "segment/AbstructBeats.hpp"

struct Node {
    using T = ll;
    using F = pll;
    T sm = 0, sz = 1, g1 = 0, l1 = 0;
    T g2 = -INF, gc = 1, l2 = INF, lc = 1, add = 0;
    Node() {}
    Node(T n) : sm(n), g1(n), l1(n) {}

    void update(Node& l, Node& r) {
        sm = l.sm + r.sm;
        sz = l.sz + r.sz;

        if (l.l1 == r.l1) {
            l1 = l.l1;
            l2 = min(l.l2, r.l2);
            lc = l.lc + r.lc;
        } else {
            bool f = l.l1 < r.l1;
            l1 = f ? l.l1 : r.l1;
            lc = f ? l.lc : r.lc;
            l2 = min(f ? r.l1 : l.l1, f ? l.l2 : r.l2);
        }

        if (l.g1 == r.g1) {
            g1 = l.g1;
            g2 = max(l.g2, r.g2);
            gc = l.gc + r.gc;
        } else {
            bool f = l.g1 > r.g1;
            g1 = f ? l.g1 : r.g1;
            gc = f ? l.gc : r.gc;
            g2 = max(f ? r.g1 : l.g1, f ? l.g2 : r.g2);
        }
    }

    void push_add(T x) {
        sm += x * sz;
        g1 += x;
        l1 += x;
        if (g2 != -INF) g2 += x;
        if (l2 != INF) l2 += x;
        add += x;
    }

    void push_min(T x) {
        sm += (x - g1) * gc;
        if (l1 == g1) l1 = x;
        if (l2 == g1) l2 = x;
        g1 = x;
    }

    void push_max(T x) {
        sm += (x - l1) * lc;
        if (g1 == l1) g1 = x;
        if (g2 == l1) g2 = x;
        l1 = x;
    }

    void push(Node& l, Node& r) {
        if (add != 0) {
            l.push_add(add);
            r.push_add(add);
            add = 0;
        }

        // 親のmax < 子のmaxなら子のmaxを更新(chmin)
        if (g1 < l.g1) l.push_min(g1);
        if (g1 < r.g1) r.push_min(g1);

        if (l1 > l.l1) l.push_max(l1);
        if (l1 > r.l1) r.push_max(l1);
    }

    bool apply(F p) {
        auto [cmd, x] = p;
        if (cmd == 1) {
            // 2nd max以下なら変化量が分からないので更新しない
            if (x <= g2) {
                return false;
            // 2nd max < x < max なら変化量が分かるのでg1を更新する
            } elif (g2 < x and x < g1) {
                push_min(x);
            }
        } elif (cmd == 2) {
            if (l2 <= x) {
                return false;
            } elif (l1 < x and x < l2) {
                push_max(x);
            }
        } elif (cmd == 3) {
            push_add(x);
        }
        return true;
    }
};

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    AbstructBeats<Node, ll, pll> beats(A);
    rep(_, Q) {
        ll op, l, r;
        cin >> op >> l >> r;
        if (op <= 2) {
            ll x;
            cin >> x;
            beats.apply(l, r, {op+1, x});
        } else {
            ll res = 0;
            beats.query(l, r, [&](Node& a) { res += a.sm; });
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

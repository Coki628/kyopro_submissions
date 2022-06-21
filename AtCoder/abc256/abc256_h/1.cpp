/*
参考：https://atcoder.jp/contests/abc256/editorial
・ライブラリ整備：抽象化Beats
・区間chfloor・区間更新・区間和取得、Beats
・ちょうど最近やっていた抽象化Beatsが使えそうだったので履修。
・区間にfloor除算を適用させるための条件として、区間内の値が全て同値であるかどうかを持つ。
・N,Q<=50万とかなり大きいのに、AC0.29秒とすごく速かった。
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
    T sm = 0, sz = 1, val = 0;
    bool same = true;
    Node() {}
    Node(T n) : sm(n), val(n) {}

    void update(Node& l, Node& r) {
        sm = l.sm + r.sm;
        sz = l.sz + r.sz;
        val = l.val;
        same = l.same and r.same and l.val == r.val;
    }

    void push_divide(T x) {
        val /= x;
        sm = val * sz;
    }

    void push_update(T x) {
        sm = x * sz;
        val = x;
        same = true;
    }

    void push(Node& l, Node& r) {
        if (same) {
            l.push_update(val);
            r.push_update(val);
        }
    }

    bool apply(F p) {
        auto [cmd, x] = p;
        if (cmd == 1) {
            if (same) {
                push_divide(x);
            } else {
                return false;
            }
        } elif (cmd == 2) {
            push_update(x);
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
        ll op;
        cin >> op;
        if (op <= 2) {
            ll l, r, x;
            cin >> l >> r >> x;
            l--;
            beats.apply(l, r, {op, x});
        } else {
            ll l, r;
            cin >> l >> r;
            l--;
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

/*
・ライブラリ整備：抽象化Beats
・区間chgcd・区間更新・区間和取得・区間最大値取得、Beats
・abc256_hとやってることはかなり似ていたので、やってみた。
　この「区間に含まれる値が1種類なら更新できる」っていうのは結構使えるのかも。
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
    T sm = 0, sz = 1, mx = -INF, lcm = 1;
    bool same = true;
    Node() {}
    Node(T n) : sm(n), mx(n), lcm(n) {}

    void update(Node& l, Node& r) {
        sm = l.sm + r.sm;
        sz = l.sz + r.sz;
        mx = max(l.mx, r.mx);

        lcm = mul_overflow(l.lcm/gcd(l.lcm, r.lcm), r.lcm) ? INF : ::lcm(l.lcm, r.lcm);
        same = l.same and r.same and l.mx == r.mx;
    }

    void push_gcd(T x) {
        mx = gcd(mx, x);
        sm = mx * sz;
    }

    void push_update(T x) {
        sm = x * sz;
        mx = x;
        same = true;
    }

    void push(Node& l, Node& r) {
        if (same) {
            l.push_update(mx);
            r.push_update(mx);
        }
    }

    bool apply(F p) {
        auto [cmd, x] = p;
        if (cmd == 1) {
            push_update(x);
        } elif (cmd == 2) {
            if (same) {
                push_gcd(x);
            } elif (lcm == INF or x % lcm != 0) {
                return false;
            }
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
        } elif (op == 3) {
            ll l, r;
            cin >> l >> r;
            l--;
            ll res = -INF;
            beats.query(l, r, [&](Node& a) { chmax(res, a.mx); });
            print(res);
        } elif (op == 4) {
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

/*
参考：https://null-mn.hatenablog.com/entry/2021/08/22/064325
・ライブラリ整備：区間等差数列更新
・更新もこっちの使いやすい方でやってみておいた。問題なくAC。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "segment/LazySegmentTreeArithmetric.hpp"

// 区間等差数列更新・最小値取得
// 参考：https://null-mn.hatenablog.com/entry/2021/08/22/064325
struct Node {
    ll val, left, right;
    operator ll() const { return val; }
};
struct Func {
    ll a, b;
    bool operator==(const Func &f) const {
        return a == f.a and b == f.b;
    }
};
auto f = [](const Node &a, const Node &b) -> Node { 
    return { min(a.val, b.val), min(a.left, b.left), max(a.right, b.right) };
};
auto g = [](const Node &a, const Func &func) -> Node {
    if (func.a == INF) {
        return a;
    } elif (func.a >= 0) {
        return { func.a*a.left+func.b, a.left, a.right };
    } else {
        return { func.a*(a.right-1)+func.b, a.left, a.right };
    }
};
auto h = [](const Func &f1, const Func &f2) -> Func {
    return f2;
};
const Node T = {INF, INF, -INF};
const Func E = {INF, INF};

void solve() {
    ll H, W;
    cin >> H >> W;

    auto seg = get_lazy_segment_tree_arithmetric(W, f, g, h, T, E);
    rep(i, W) {
        seg.set(i, {0, i, i+1});
    }
    seg.build();

    rep(h, 1, H+1) {
        ll l, r;
        cin >> l >> r;
        l--;
        ll i = seg.find_last(l, [](const Node &a) { return a < INF; });
        if (i != -1) {
            // 区間[l,r)を、位置iを初項seg[i]とした公差1の等差数列に更新
            seg.update(i, r, {1, seg[i]});
        } else {
            seg.update(l, r, {0, INF});
        }
        // seg.print(W);
        ll res = seg.query(0, W);
        res = res < INF ? res+h : -1;
        print(res);
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

/*
参考：https://twitter.com/shu8Cream/status/1513030968340205574
　　　https://null-mn.hatenablog.com/entry/2021/08/22/064325
・ライブラリ整備：区間等差数列加算
・めっちゃ汎用的なやつあった！すごい。やっぱTLの情報は大事。
・加算する重みは変えられるし、むしろ初期化時に重み付けしないから、
　後から任意の1次関数を加算していける。
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

// 区間等差数列加算・区間和取得
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
    return { a.val+b.val, min(a.left, b.left), max(a.right, b.right) };
};
auto g = [](const Node &a, const Func &func) -> Node {
    return { a.val+(func.a*(a.left+a.right-1)+func.b*2)*(a.right-a.left)/2, a.left, a.right }; 
};
auto h = [](const Func &f1, const Func &f2) -> Func {
    return { f1.a+f2.a, f1.b+f2.b };
};
const Node T = {0, INF, -INF};
const Func E = {0, 0};

void solve() {
    ll N, K;
    cin >> N >> K;
    auto B = LIST(N);

    auto seg = get_lazy_segment_tree_arithmetric(N, f, g, h, T, E);
    rep(i, N) {
        // 初期化{val, left, right}
        seg.set(i, {B[i], i, i+1});
    }
    seg.build();

    ll ans = 0;
    rep(i, N-K, -1, -1) {
        ll j = i+K-1;
        ll rest = seg[j];
        if (rest > 0) {
            ll need = ceil(rest, K);
            ans += need;
            // 区間[l,r)に{a,b}=関数ax+bを加算
            seg.update(i, i+K, { -need, -need });
            // seg.print(N);
        }
    }
    // 初項にできない位置は一番必要な回数が多くなる場所に合わせてまとめてやる
    ll mx = 0;
    rep(j, K-2, -1, -1) {
        ll rest = seg[j];
        if (rest > 0) {
            ll need = ceil(rest, j+1);
            chmax(mx, need);
        }
    }
    ans += mx;
    print(ans);
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

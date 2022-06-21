/*
参考：https://twitter.com/stoq_/status/1538156563999133696
・自力ならず…。
・区間等差数列加算・区間和取得
・等差数列加算のセグ木は考えたんだけど、等差数列加算だと1次関数だから、
　まだ1次足りなくて無理じゃないかと思ってしまったんだけど、
　取得の時さらに区間和にすればもう1次増やせるから、1点取得の2次関数なら取れるね…。
　これ気付けたら良かったなぁ。。
・20万クエリで0.95秒となんか遅めだったので少し考える。
　/2のmod除算のlogが気になったので前計算してみると、0.62秒になって納得。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "segment/LazySegmentTreeArithmetric.hpp"

// 区間等差数列加算・区間和取得
// 初期化：{初期値, 左端i, 右端i+1}
// 更新　：区間[l,r)に{a,b}=関数ax+bを加算
mint inv2 = (mint)1 / 2;
struct Node {
    mint val;
    ll left, right;
    operator mint() const { return val; }
};
struct Func {
    mint a, b;
    bool operator==(const Func &f) const {
        return a == f.a and b == f.b;
    }
};
auto f = [](const Node &a, const Node &b) -> Node { 
    return { a.val+b.val, min(a.left, b.left), max(a.right, b.right) };
};
auto g = [](const Node &a, const Func &func) -> Node {
    return {
        a.val+(func.a*(a.left+a.right-1)+func.b*2)*(a.right-a.left)*inv2,
        a.left, a.right
    };
};
auto h = [](const Func &f1, const Func &f2) -> Func {
    return { f1.a+f2.a, f1.b+f2.b };
};
const Node T = {0, INF, -INF};
const Func E = {0, 0};

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    auto seg = get_lazy_segment_tree_arithmetric(N, f, g, h, T, E);
    rep(i, N) {
        seg.set(i, {0, i, i+1});
    }
    seg.build();
    rep(i, N) {
        seg.update(i, N, {A[i], A[i]});
    }
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x, v;
            cin >> x >> v;
            x--;
            seg.update(x, N, {-A[x], -A[x]});
            A[x] = v;
            seg.update(x, N, {A[x], A[x]});
        } else {
            ll x;
            cin >> x;
            x--;
            mint res = seg.query(0, x+1);
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

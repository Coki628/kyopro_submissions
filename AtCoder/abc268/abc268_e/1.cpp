/*
・自力ならず。悔しい。
・円環、区間等差数列加算
・大まかな方針は立てたものの、時間内に詰め切れる気がせず、
　他を見てたりしたので全然間に合わず。
　時間外でじっくりやったけど、結局手持ちの区間等差数列加算セグ木にminが乗らないということが、
　ランダムテスト回したり色々やるまで気付けなかったので終わってる。
・基本的にはCでやった起点の話をベースに、適切に等差数列加算できればいいんだけど、
　円環なこともあり、添字がやばくなる。本番中は詰め切れなかったけど、
　整理すると、コスト0の場所dを起点に、／＼d／＼みたいな形のどっかで長さNの区間になる。
　さらに山のてっぺんはNが奇数だと区間長2になる。
　これを踏まえて、丁寧に6箇所全部見るのをN個やればいい。(ソース内コメントも参照)
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

#include "segment/LazySegmentTreeArithmetric.hpp"

// 区間等差数列加算・区間和取得
// 初期化：{初期値, 左端i, 右端i+1}
// 更新　：区間[l,r)に{a,b}=関数ax+bを加算
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
    // assert((func.a*(a.left+a.right-1)+func.b*2)*(a.right-a.left)%2 == 0);
    return {
        a.val+(func.a*(a.left+a.right-1)+func.b*2)*(a.right-a.left)/2,
        a.left, a.right
    };
};
auto h = [](const Func &f1, const Func &f2) -> Func {
    return { f1.a+f2.a, f1.b+f2.b };
};
const Node T = {0, INF, -INF};
const Func E = {0, 0};

void solve() {
    ll N;
    cin >> N;
    auto P = LIST(N);

    auto seg = get_lazy_segment_tree_arithmetric(N, f, g, h, T, E);
    rep(i, N) {
        seg.set(i, {0, i, i+1});
    }
    seg.build();
    rep(i, N) {
        ll d = modulo(P[i]-i, N);
        ll l = d;
        ll r = min(l+N/2, N);
        // dより右の／
        seg.update(l, r, {1, 0});
        l = r;
        if (l < N and N%2 == 1) {
            // 奇数でてっぺんが2つある所
            seg.update(l, l+1, {1, N/2});
            l++;
        }
        if (l < N) {
            r = min(l+N/2, N);
            // dより右の＼
            seg.update(l, r, {-1, N/2});
        }
        r = d;
        l = max(r-N/2, 0LL);
        ll len = r - l;
        // dより左の＼
        seg.update(l, r, {-1, len});
        r = l;
        if (r > 0 and N%2 == 1) {
            // 奇数でてっぺんが2つある所
            seg.update(r-1, r, {1, N/2});
            r--;
        }
        if (r > 0) {
            l = max(r-N/2, 0LL);
            len = r - l;
            // dより左の／
            seg.update(l, r, {1, N/2-len});
        }
        // seg.print(N);
    }
    ll ans = INF;
    rep(i, N) {
        chmin(ans, (ll)seg[i]);
    }
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

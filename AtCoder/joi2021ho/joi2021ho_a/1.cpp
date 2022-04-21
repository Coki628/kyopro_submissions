/*
・なんとか自力AC！
・てっぺんになる場所を決めて全探索する。するとそこより右と左で分けて考えたい。
　狭義単調増加/減少にしたいんだけど、分かりづらいのでindex(かその逆)を足して、
　ようは平らっぽくできるかで考えてみる。(結局これ要らなかったんだけど。)
　ある位置で必要になるコストを考えると、これは自分より右/左側である限り同じだとなる。
　左右についてその位置を取り込む時に必要なコストを前計算。
　これを累積すればいいんだけど、左右について見て大きい方の累積和だけでいい。
　てっぺんに近い側が余分に大きくなって損はないので、
　両側について必要な分だけ同時に、取り込んだ区間を伸ばしていくと考えると、
　大きい方だけあれば十分なのが分かる。
・これは最初に通したやつで、遅延セグ木で頑張ってる。
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "segment/LazySegmentTree.hpp"

// 区間加算・区間最大値取得
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = -INF;
const ll E = 0;

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    auto seg = get_lazy_segment_tree(A, f, g, h, T, E);
    rep(i, N) {
        seg.update(i, i);
    }
    vector<ll> costl(N), costr(N);
    rep(i, 1, N) {
        seg.update(i, N, -1);
        seg.update(0, i, 1);
        costl[i] = max(seg[i-1]-seg[i], 0LL);
    }
    rep(i, N-2, -1, -1) {
        seg.update(i+1, N, 1);
        seg.update(0, i+1, -1);
        costr[i] = max(seg[i+1]-seg[i], 0LL);
    }
    Accumulate<ll> accl(costl), accr(costr);

    ll ans = INF;
    rep(i, N) {
        chmin(ans, max(accl.query(0, i+1), accr.query(i, N)));
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

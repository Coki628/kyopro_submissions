/*
・きっちり自力AC！
・縦横独立、式変形、セグ木
　まず縦横どちらかでもmod kで合わないならNO。
　移動は、めいっぱい上がって横移動して下がる、みたいなのが最善。
　横移動でぶつからないかはセグ木とかで区間最大取る。
　縦移動で上がどこまでいけるかにぶたんしちゃったけど、
　これ絶対割り算1回とかでいけるやつ。ぱっと出ないの良くないよなー。
・↑やった。にぶたんしてたやつを式変形してxを求める形にする。
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

void solve() {
    ll H, W;
    cin >> H >> W;
    auto A = LIST(W);
    ll Q;
    cin >> Q;

    auto seg = get_segment_tree(A, [](ll a, ll b) { return max(a, b); }, -INF);
    rep(_, Q) {
        ll sh, sw, th, tw, k;
        cin >> sh >> sw >> th >> tw >> k;
        sw--; tw--;
        // modが合わない
        if (sh%k != th%k or sw%k != tw%k) {
            NO();
            continue;
        }
        ll x = (H-sh) / k;
        // ll x = bisearch_max(0, INF, [&](ll m) {
        //     if (mul_overflow(k, m)) return false;
        //     return sh+k*m <= H;
        // });
        ll mxh = sh + k*x;
        if (sw > tw) swap(sw, tw);
        // 横移動でぶつかる
        if (mxh <= seg.query(sw, tw+1)) {
            NO();
            continue;
        }
        YES();
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

/*
・速攻自力AC。
・WM、range_freq
・区間に出現するある要素の個数なので、WMでrange_freqすると一撃。
　なんだけど、もっとちゃんと考察する解法を導くのも大事なんだろうなぁとは思う。
　ちなみに公式方針は、値毎にindexを隣接リストで持ってクエリでにぶたん、だった。
　言われたらああなるほどだけど、自分ですぐ思いつくかと言われると、
　ちょっと時間かかっただろうなぁとは思う。
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

#include "segment/WaveletMatrix.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    WaveletMatrix<ll, 20> wm(A);
    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll l, r, x;
        cin >> l >> r >> x;
        l--;
        ll res = wm.range_freq(l, r, x, x+1);
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

/*
・きっちり自力AC！
・にぶたん、区間加算BIT
・貪欲にできるだけ前に進めたい。「今日と同じだけ取れる日付の最大」をにぶたんした。
　取れる個数は全部でN個だからこのにぶたんは最大でN回しか行われないはずで、
　中のチェックをlogくらいでやれればいける。(データ構造で殴打)
・20万のNでにぶたんとBITにぶたんでlog3つ乗ってもAC0.50秒。やっぱりBITは速い。
・と思ったらこれハックされて落ちてた…。
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

#include "segment/BIT2.hpp"

void solve() {
    ll N, x;
    cin >> N >> x;
    auto A = LIST(N);

    sort(ALL(A));
    BIT2<ll> bit(N+1);
    rep(i, N) {
        bit.add(i, A[i]);
    }
    bit.add(N, INF);
    ll cur = bit.bisearch_fore(0, N, x+1);
    ll ans = 0;
    while (cur > 0) {
        ll res = bisearch_max(0, x+1, [&](ll m) {
            bit.add(0, N, m);
            ll nxt = bit.bisearch_fore(0, N, x+1);
            bit.add(0, N, -m);
            return cur == nxt;
        }) + 1;
        ans += cur * res;
        bit.add(0, N, res);
        cur = bit.bisearch_fore(0, N, x+1);
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}

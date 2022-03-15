/*
・dojo set_d_5_3
・さくっと自力AC！
・Beatsでぶん殴り。。
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

#include "segment/SegmentTreeBeats.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;

    ll cur = 0, ans = 0;
    SegmentTreeBeats seg(vector<ll>(N, 0));
    rep(i, M) {
        ll t, l, r;
        cin >> t >> l >> r;
        l--;

        seg.add(0, N, t-cur);
        ans += seg.query_sum(l, r);
        seg.update(l, r, 0);
        cur = t;
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

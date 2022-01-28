/*
・Beats、区間chmin
・一応、自分でやろうとしたDP方針でも通しておいた。
　遷移元のA[i]によってどう遷移するかが変わるので貰うDPにできなくて、
　最小化で配るので、区間chminがあればうまくいく。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

#include "segment/SegmentTreeBeats.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    reverse(ALL(A));
    SegmentTreeBeats dp(vector<ll>(N+1, INF));
    dp.update(0, 0);
    rep(i, N) {
        if (A[i] == A[0]) {
            dp.chmin(i+1, dp[i]);
        } else {
            dp.chmin(i+1, min(i+i, N)+1, dp[i]+1);
        }
    }
    ll ans = dp[N];
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

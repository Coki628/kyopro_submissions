/*
参考：https://twitter.com/US_kyopro/status/1601792850886242304
・WMでK番目までの和
・WMは少し考えたけど、和が取れないといけないから無理じゃね？
　って思ってたんだけど、それができるようだ。
　US_cubeさんの実装を参考に自分のWMにも同じ機能を組み込んでみた。
　これがあるなら確かに貼るだけだな…。
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

#include "datastructure/WaveletMatrix.hpp"

void solve() {
    ll N, M, K;
    cin >> N >> M >> K;
    vector<ll> A(N);
    cin >> A;

    WaveletMatrix<ll> wm(A);
    vector<ll> ans(N - M + 1);
    rep(l, N - M + 1) {
        ll r = l + M;
        ans[l] = wm.kth_smallest_sum(l, r, K);
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

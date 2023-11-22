/*
・少し悩んで飛ばして、終了後自力AC。これは間に合わせたかった…。
・配列の復元、隣接max
・グチャグチャになって時間内に詰め切れなかったが、
　結局、両端は必ず使いつつ、隣接でmin取るだけで通った。
　G1でかなり消耗させられた後とはいえ、ここは通したかったな。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> B(N - 1);
    cin >> B;

    vector<ll> A(N);
    A[0] = B[0];
    rep(i, 1, N - 1) {
        A[i] = min(B[i - 1], B[i]);
    }
    A[N - 1] = B[N - 2];
    print(A);
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

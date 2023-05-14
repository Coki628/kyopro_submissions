/*
・zero sum ranges系、累積からindexを引く、長さK以上は数えない
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    rep(i, N) {
        A[i] %= K;
    }
    auto acc = A;
    acc.insert(acc.begin(), 0);
    rep(i, N) {
        acc[i + 1] = (acc[i + 1] + acc[i]) % K;
    }
    rep(i, N + 1) {
        acc[i] = modulo(acc[i] - i, K);
    }
    WaveletMatrix<ll> wm(acc);
    ll ans = 0;
    rep(i, N) {
        ans += wm.range_freq(i + 1, min(i + K, N + 1), acc[i], acc[i] + 1);
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

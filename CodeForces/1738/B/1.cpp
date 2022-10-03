/*
・なんとか自力AC！
・考慮することが多い。NかKが1なら即OK、
　一意になる後ろの方の項がソート済じゃなければNG、
　残りは決まってる先頭項と同じ値を手前の項数分足した値が、
　辻褄を合わせるのに足りるならOKだし足りなければNG。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    rep(i, N-K, N) {
        cin >> A[i];
    }

    if (N == 1 or K == 1) {
        Yes();
        return;
    }
    vector<ll> B(N, -INF);
    rep(i, N-K+1, N) {
        B[i] = A[i] - A[i-1];
    }
    if (B != sorted(B)) {
        No();
        return;
    }
    rep(i, N-K, -1, -1) {
        B[i] = B[i+1];
    }
    ll sm = sum(subarray(B, 0, N-K+1));
    if (sm >= A[N-K]) {
        Yes();
    } else {
        No();
    }
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

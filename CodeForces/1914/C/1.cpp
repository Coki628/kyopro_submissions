/*
・きっちり自力AC！
・新規クリアを進める → 一番いい所で連打、が最善なので、
　新規クリアをどこまでやるか全探索。
　Aの累積和とBの累積maxを持っておけばすぐに求まる。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N), B(N);
    cin >> A >> B;

    ll ans = -INF, bmx = 0, sm = 0;
    rep(i, N) {
        if (K - i <= 0) break;
        chmax(bmx, B[i]);
        sm += A[i];
        chmax(ans, sm + bmx * (K - i - 1));
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

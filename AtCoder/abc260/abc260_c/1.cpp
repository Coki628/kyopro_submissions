/*
・きっちり自力AC！
・制約の妙な小ささに？？ってなったけど、後ろからDPみたいにする。
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
    ll N, X, Y;
    cin >> N >> X >> Y;
    
    vector<ll> R(N+1), B(N+1);
    R[N] = 1;
    rep(i, N, 1, -1) {
        R[i-1] += R[i];
        B[i] += R[i] * X;
        R[i-1] += B[i];
        B[i-1] += B[i] * Y;
    }
    print(B[1]);
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

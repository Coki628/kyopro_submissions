/*
・きっちり自力AC！
・三角形の面積、比
・重なってる所を引きながら、順番に足していけばいい。
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
    double N, D, H;
    cin >> N >> D >> H;
    vector<ll> A(N);
    cin >> A;

    double ans = 0;
    rep(i, N - 1) {
        double duph = max((A[i] + H) - A[i + 1], (double)0);
        double dupw = D * (duph / H);
        ans += (H * D / 2) - (duph * dupw / 2);
    }
    ans += H * D / 2;
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

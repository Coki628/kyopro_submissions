/*
・きっちり自力AC！
・それぞれの列でどっちを先に置いていくかは自由に決められるので、
　両方のLISをそのまま全部使える。
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

#include "common/LIS.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);
    auto B = LIST(M);

    auto resa = LIS(A, true);
    auto resb = LIS(B, true);
    ll ans = resa.size()+resb.size();
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

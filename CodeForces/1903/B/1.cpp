/*
・自力AC！
・少なくとも必要なものとして各行列をANDで集める。
　これで合うかどうか確認。(証明AC。。。)
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
    auto mat = listnd(N, N, 0LL);
    rep(i, N) {
        cin >> mat[i];
    }

    vector<ll> A(N, (1LL << 30) - 1);
    rep(i, N) {
        rep(j, N) {
            if (i == j) continue;
            A[i] &= mat[i][j];
            A[j] &= mat[i][j];
        }
    }

    rep(i, N) {
        rep(j, N) {
            if (i == j) continue;
            if ((A[i] | A[j]) != mat[i][j]) {
                NO();
                return;
            }
        }
    }
    YES();
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

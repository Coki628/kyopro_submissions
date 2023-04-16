/*
・グリッド回転
・rot90、移植しておいてよかったね。
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

#include "grid/rot90.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = listnd(N, N, 0);
    cin >> A;
    auto B = listnd(N, N, 0);
    cin >> B;

    rep(_, 4) {
        A = rot90(A);
        bool ok = true;
        rep(i, N) {
            rep(j, N) {
                if (A[i][j] and not B[i][j]) {
                    ok = false;
                    break;
                }
            }
            if (not ok) break;
        }
        if (ok) {
            Yes();
            return;
        }
    }
    No();
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

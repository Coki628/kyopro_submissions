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
    ll N;
    cin >> N;
    vector<string> mat(N);
    rep(i, N) {
        cin >> mat[i];
    }

    rep(i, N) {
        rep(j, i+1, N) {
            if (mat[i][j] == 'W') {
                if (mat[j][i] != 'L') {
                    print("incorrect");
                    return;
                }
            }
            if (mat[i][j] == 'L') {
                if (mat[j][i] != 'W') {
                    print("incorrect");
                    return;
                }
            }
            if (mat[i][j] == 'D') {
                if (mat[j][i] != 'D') {
                    print("incorrect");
                    return;
                }
            }
        }
    }
    print("correct");
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

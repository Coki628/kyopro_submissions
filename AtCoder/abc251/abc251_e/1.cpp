/*
・きっちり自力AC！
・円環のDP
・円環なので最初と最後だけちょっと別処理するDP。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    auto A = LIST(N);

    auto dp1 = list2d(N+1, 2, INF);
    dp1[0][0] = 0;
    rep(i, N) {
        rep(j, 2) {
            rep(k, 2) {
                if (j == 0 and k == 0) continue;
                chmin(dp1[i+1][k], dp1[i][j]+(k == 1 ? A[i] : 0));
            }
        }
    }
    auto dp2 = list2d(N+1, 2, INF);
    dp2[0][1] = 0;
    rep(i, N) {
        rep(j, 2) {
            rep(k, 2) {
                if (j == 0 and k == 0) continue;
                chmin(dp2[i+1][k], dp2[i][j]+(k == 1 ? A[i] : 0));
            }
        }
    }
    ll ans = min(dp1[N][0], dp2[N][1]);
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

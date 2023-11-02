/*
・なんとか自力AC。手こずった。
・値をペアで持つDP
・一見、銀貨の状態まで持てないので詰みそうに思えるが、
　いかなる時でも金貨を優先していいので、
　こういうのは値の方にペアで持たせると対応できる。(気付くのに時間かかった。。)
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
    ll N, X;
    cin >> N >> X;
    vector<ll> A(N), B(N), C(N);
    rep(i, N) {
        cin >> A[i] >> B[i] >> C[i];
    }

    auto dp = listnd(N + 1, X + 1, mkp(-INF, INF));
    dp[0][0] = {0, 0};
    rep(i, N) {
        rep(j, X + 1) {
            auto [c, a] = dp[i][j];
            if (dp[i + 1][j].first < c) {
                dp[i + 1][j] = {c, a};
            } else if (
                dp[i + 1][j].first == c and
                dp[i + 1][j].second > a
            ) {
                dp[i + 1][j] = {c, a};
            }
            if (j + B[i] <= X) {
                if (dp[i + 1][j + B[i]].first < c + C[i]) {
                    dp[i + 1][j + B[i]] = {c + C[i], a + A[i]};
                } else if (
                    dp[i + 1][j + B[i]].first == c + C[i] and
                    dp[i + 1][j + B[i]].second > a + A[i]
                ) {
                    dp[i + 1][j + B[i]] = {c + C[i], a + A[i]};
                }
            }
        }
    }
    array<ll, 3> ans = {-INF, -INF, -INF};
    rep(j, X + 1) {
        auto [c, a] = dp[N][j];
        a = 1000000000 - a;
        ll b = X - j;
        if (ans[0] < c) {
            ans = {c, a, b};
        } else if (ans[0] == c and ans[1] < a) {
            ans = {c, a, b};
        } else if (ans[0] == c and ans[1] == a and ans[2] < b) {
            ans = {c, a, b};
        }
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

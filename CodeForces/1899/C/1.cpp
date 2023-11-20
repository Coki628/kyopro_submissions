/*
・きっちり自力AC！
・連続部分列、区間和の最大値、区間状態DP
・連続部分列の状態を全部見れるいつものDPに、
　今回必要になる、隣接要素の偶奇が同じなら不可って条件を加えればOK。
　でもDiv.3のCだし、このDPは想定解じゃない気はする。
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
    vector<ll> A(N);
    cin >> A;

    auto dp = listnd(N + 1, 3, -INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, 3) {
            rep(jj, j, 3) {
                if (j == 0 and jj == 2) continue;
                if (j == 1 and jj == 1 and i > 0 and modulo(A[i], 2LL) == modulo(A[i - 1], 2LL)) {
                    continue;
                }
                chmax(dp[i + 1][jj], dp[i][j] + (jj == 1 ? A[i] : 0));
            }
        }
    }
    ll ans = max(dp[N][1], dp[N][2]);
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

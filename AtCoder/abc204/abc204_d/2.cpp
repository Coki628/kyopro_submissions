/*
・E8さん本
・きっちり自力AC！
・部分和DP応用
・制約が貪欲やんなって言ってる。見た目はすごく貪欲したくなるけど。
　そういう目で見ると、片方の値持って合計から引くDPが見えてくる。
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
#include "template.hpp"

const ll MX = 100007;
bool dp[107][MX];

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    dp[0][0] = true;
    ll total = sum(A);
    rep(i, N) {
        rep(j, MX) {
            if (!dp[i][j]) continue;
            dp[i+1][j] = true;
            dp[i+1][j+A[i]] = true;
        }
    }

    ll ans = INF;
    rep(j, MX) {
        if (dp[N][j]) {
            chmin(ans, max(j, total-j));
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

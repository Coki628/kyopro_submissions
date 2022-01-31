/*
・これもTLE想定。
・dp[i][j] := Aをi番目まで見て、Bで最後に使ったのがjの時の最大値
　みたいなDP。遷移にもNかかるので計算量はN^3かかってしまう。
　でもこれ見て考えてたら、前の値を引き継ぐからinplace DPにできないかな？
　っていう発想に持っていけたので、書いてみて正解だった。
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

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    auto dp = list2d(2, N+1, -INF);
    dp[0][0] = 0;
    rep(i, N) {
        rep(j, N+1) {
            chmax(dp[(i+1)%2][j], dp[i%2][j]);
            ll k = j;
            while (k < N and B[k]%A[i]) {
                k++;
            }
            if (k < N) {
                chmax(dp[(i+1)%2][k+1], dp[i%2][j]+1);
            }
        }
        // dp[i%2].assign(N+1, -INF);
    }
    ll ans = max(dp[N%2]);
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

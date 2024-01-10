/*
・きっちり自力AC！
・隣接スワップ、符号のフリップ、直前の状態を持ってDP
・なんか賢い貪欲が絶対ありそうな臭いがプンプンしたが、
　確度高めのDPが見えたのでそっちでやった。
　1つ前をスワップしたかの状態を持っておけば、
　今の位置をスワップする/しないでその位置の符号が定まる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

    auto dp = listnd(N, 2, -INF);
    dp[0][0] = 0;
    rep(i, N - 1) {
        rep(j, 2) {
            rep(k, 2) {
                ll res = j ^ k;
                if (res) {
                    chmax(dp[i + 1][k], dp[i][j] - A[i]);
                } else {
                    chmax(dp[i + 1][k], dp[i][j] + A[i]);
                }
            }
        }
    }
    ll ans = max(dp[N - 1][0] + A[N - 1], dp[N - 1][1] - A[N - 1]);
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

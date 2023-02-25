/*
・別解。これはこれで賢い。でもこういうの見えるようにしたいー。
・3以上の状態をまとめる、区間状態DP
・0,1,2,3以上の4値と、区間前,区間中,区間後の3値を状態に持つと、
　題意の区間を全て数え上げられる。区間長1の分は最後に引けばいい。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    ll dp[N + 1][3][4] = {};
    dp[0][0][1] = 1;
    rep(i, N) {
        rep(j, 3) {
            rep(k, 4) {
                ll nxk = j == 1 ? min(k * A[i], 3LL) : k;
                dp[i + 1][j][nxk] += dp[i][j][k];
                if (j < 2) {
                    nxk = j + 1 == 1 ? min(k * A[i], 3LL) : k;
                    dp[i + 1][j + 1][nxk] += dp[i][j][k];
                }
            }
        }
    }
    vector<ll> ans(3);
    rep(j, 1, 3) {
        rep(k, 3) {
            ans[k] += dp[N][j][k];
        }
    }
    // 区間長1は今回対象外なので取り除く
    rep(i, N) {
        ans[A[i]]--;
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

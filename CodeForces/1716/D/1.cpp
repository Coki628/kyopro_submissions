/*
参考：https://twitter.com/titia_til/status/1555232682614804480
・自力ならず。。むずかった。
・MOD累積和でDP、枝刈り
・MOD毎に累積和すると、1回分の全体の遷移はO(N)でできる。
　これが普通にやるとN回あるので無理だけど、
　実際は取りうる値の最小値がNを超えた先は見なくていいので、
　これは初項K公差1の等差数列の和みたいになるので、
　だいたい項数^2くらいになり、項数は√Nくらいに収まる。
　ここでDPを打ち切れば、全体でO((√N)*N)になり間に合う。
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
    ll N, K;
    cin >> N >> K;

    vector<mint> dp(N+1), ans(N+1);
    dp[0] = 1;
    ll mn = 0;
    rep(x, N) {
        ll k = K + x;
        mn += k;
        // 取りうる最小値がNを超えたら打ち切る
        if (mn > N) break;
        vector<mint> nxt(N+1);
        rep(i, N) {
            if (i+k > N) break;
            nxt[i+k] += nxt[i] + dp[i];
        }
        dp = nxt;
        rep(i, 1, N+1) {
            ans[i] += dp[i];
        }
    }
    ans.erase(ans.begin());
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

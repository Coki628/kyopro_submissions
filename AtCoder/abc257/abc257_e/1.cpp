/*
・これは自力WA。。
・DP復元
・ダメなケースが分からないんだけど、通らない…。
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
    auto cost = LIST(9);
    cost.insert(cost.begin(), INF);

    auto dp = list2d(N+1, 10, mkp(INF, -1));
    dp[0][0] = {0, -1};
    rep(i, N) {
        rep(j, 10) {
            rep(k, 1, 10) {
                if (
                    dp[i+1][k].first > dp[i][j].first+cost[k] or
                    dp[i+1][k].first == dp[i][j].first+cost[k] and dp[i+1][k].second < j
                ) {
                    dp[i+1][k] = {dp[i][j].first+cost[k], j};
                }
            }
        }
    }
    ll si = -1, sj = -1;
    rep(i, N, -1, -1) {
        rep(j, 9, -1, -1) {
            if (dp[i][j].first <= N) {
                si = i;
                sj = j;
                break;
            }
        }
        if (si != -1 and sj != -1) break;
    }
    string ans;
    ans += tochar(sj);
    while (si > 0) {
        ll nxj = dp[si][sj].second;
        assert(nxj != -1);
        ans += tochar(nxj);
        sj = nxj;
        si--;
    }
    if (ans != "0") {
        ans.pop_back();
    }
    assert(ans == sorted(ans, true));
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

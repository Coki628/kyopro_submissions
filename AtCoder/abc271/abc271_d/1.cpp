/*
・きっちり自力AC！
・DP復元
・慣れてればまあ、やるべきことをやるだけ。
・なんか答えの文字列を陽にDP配列に持たせても通るらしい…。
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
    ll N, S;
    cin >> N >> S;
    vector<ll> A(N), B(N);
    rep(i, N) {
        cin >> A[i] >> B[i];
    }

    auto dp = listnd(N+1, S+1, mkp(0, -1));
    dp[0][0] = {1, -1};
    rep(i, N) {
        rep(j, S+1) {
            if (!dp[i][j].first) continue;
            if (j+A[i] <= S and !dp[i+1][j+A[i]].first) {
                dp[i+1][j+A[i]] = {1, j};
            }
            if (j+B[i] <= S and !dp[i+1][j+B[i]].first) {
                dp[i+1][j+B[i]] = {1, j};
            }
        }
    }

    ll s = S;
    auto cur = dp[N][s];
    if (!cur.first) {
        No();
    } else {
        Yes();
        string ans;
        rep(i, N-1, -1, -1) {
            ll prvs = cur.second;
            if (s - prvs == A[i]) {
                ans += 'H';
            } elif (s - prvs == B[i]) {
                ans += 'T';
            } else {
                assert(0);
            }
            cur = dp[i][prvs];
            s = prvs;
        }
        reverse(ALL(ans));
        print(ans);
    }
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

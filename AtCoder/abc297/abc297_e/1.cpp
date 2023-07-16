/*
・自力ならず。。
・決め打ちにぶたんの内側でDPみたいなことしてたらTLEが取れない。。
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

#include "common/HashSet.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    K++;
    sort(ALL(A));
    ll res = bisearch_min(-1, INF, [&](ll x) {
        vector<HashSet<ll>> dp(2);
        dp[0].insert(0);
        rep(i, N) {
            for (auto k : dp[i % 2]) {
                ll j = 0;
                while (k + A[i] * j <= x) {
                    dp[(i + 1) % 2].insert(k + A[i] * j);
                    j++;
                    if (dp[(i + 1) % 2].size() >= K) {
                        return true;
                    }
                }
            }
        }
        return dp[N % 2].size() >= K;
    });
    print(res);
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

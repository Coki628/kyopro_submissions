/*
・2乗の区間DP
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
    vector<ll> P(N), A(N);
    rep(i, N) {
        cin >> P[i] >> A[i];
    }
    P--;

    auto memo = listnd(N, N + 1, -1LL);
    auto rec = [&](auto &&f, ll l, ll r) -> ll {
        if (l >= r) {
            return 0;
        }
        if (memo[l][r] != -1) {
            return memo[l][r];
        }
        ll res = -INF;
        chmax(res, f(f, l + 1, r) + (l <= P[l] and P[l] < r ? A[l] : 0));
        chmax(res, f(f, l, r - 1) + (l <= P[r - 1] and P[r - 1] < r ? A[r - 1] : 0));
        return memo[l][r] = res;
    };
    ll ans = rec(rec, 0, N);
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

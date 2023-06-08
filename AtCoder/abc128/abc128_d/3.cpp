/*
・こういう2乗の区間DPでうまくいかない理由がよく分かってない。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    // dp[i][j][l][r] := 取得操作i回、破棄をj回、位置(l,r)まで取った時の最大値
    auto memo = listnd(K + 1, K + 1, N + 1, N + 1, -1LL);
    auto rec = [&](auto&& f, ll k, ll x, ll l, ll r) -> ll {
        ll len = r - l;
        if (k + x > K) {
            return -INF;
        }
        if (k + x == K or len == 0) {
            return 0;
        }
        if (memo[k][x][l][r] != -1) {
            return memo[k][x][l][r];
        }
        ll res = -INF;
        chmax(res, f(f, k + 1, x, l + 1, r) + A[l]);
        chmax(res, f(f, k + 1, x, l, r - 1)) + A[r - 1];
        chmax(res, f(f, k + 1, x + 1, l + 1, r));
        chmax(res, f(f, k + 1, x + 1, l, r - 1));
        memo[k][x][l][r] = res;
        return res;
    };
    ll ans = rec(rec, 0, 0, 0, N);
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

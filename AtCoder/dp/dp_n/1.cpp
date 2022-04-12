/*
・dojo set_d_6_7
・きっちり自力AC！
・区間DP
・そうと分かっていれば、できる。
　今回は半開区間で持ったら添字バグらないですんなりできた。
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

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    Accumulate<ll> acc(A);
    auto memo = list2d(N+1, N+1, INF);
    auto rec = [&](auto&& f, ll l, ll r) -> ll {
        if (memo[l][r] < INF) {
            return memo[l][r];
        }
        ll len = r - l;
        if (len <= 0) {
            return INF;
        } elif (len == 1) {
            return 0;
        }
        ll res = INF;
        rep(m, l+1, r) {
            chmin(res, f(f, l, m)+f(f, m, r)+acc.query(l, r));
        }
        memo[l][r] = res;
        return res;
    };
    ll res = rec(rec, 0, N);
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

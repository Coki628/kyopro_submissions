/*
・なんとか自力AC。。本日の戦犯。1時間以上デバッグしてたと思う…。
・何番目のブロックにあるかは愚直に数えて間に合った。添字が全然合わなくてつらかった。
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

// void solve(ll N) {
void solve() {
    ll N;
    cin >> N;

    ll sm = 1, add = 1;
    while (sm < N) {
        add += 2;
        sm += add;
    }
    ll x = ceil(add, 2LL);
    ll M = add;
    ll i = M - (sm - N) - 1;
    if (i > M / 2) {
        print(i - (x - 2));
    } else {
        print(x - i);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // rep(i, 1, 20) {
    //     solve(i);
    // }
    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}

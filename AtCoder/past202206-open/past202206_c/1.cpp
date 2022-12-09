/*
・10^9超えるまで掛けてbreak N=1は場合分け。
　WAが出たのでオーバーフロー疑ったりしたけど、
　結局N=1の場合分けミスってただけ…。
　場合分けしてるのに全○じゃなくて全×にしてた。。
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
    ll N, M;
    cin >> N >> M;

    string ans(M, 'x');
    ll cur = N;
    if (N > 1) {
        rep(i, M) {
            if (cur <= 1000000000) {
                ans[i] = 'o';
            } else {
                break;
            }
            // if (mul_overflow(cur, N)) {
            //     break;
            // }
            cur *= N;
        }
    } else {
        ans = string(M, 'o');
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

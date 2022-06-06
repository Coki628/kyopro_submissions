/*
参考：https://twitter.com/u2dayo/status/1533088605748756480
・自力ならず。。
・素因数分解、式変形
・うにさんの説明が入ってきた。(公式解説も同じこと言ってると思うんだけどむずい)
・大事な所はソース内コメントで説明しておいた。
　こういう式変形、ほんと苦手だよなぁ…。
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

    ll ans = 0;
    rep(i, 1, N+1) {
        // 素因数が奇数の部分aは他方でも必ず必要になるので、ここをまず求める
        // i = a * b^2
        ll a = 1;
        for (auto [k, v] : factorize(i)) {
            if (v%2 == 1) {
                a *= k;
            }
        }
        // 少なくともaの部分はjに含まねばならず、それ以外は2乗で表せれば何でもいいので、c^2の部分を1から全探索
        // j = a * c^2
        rep(c, 1, N+1) {
            ll j = a * c * c;
            if (j > N) break;
            ans++;
        }
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

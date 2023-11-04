/*
・自力AC！
・上位桁から貪欲
・まず10^9がいけるかは先に判定しておく。
　これで後は9桁以下の任意の整数が使えるようになるのでやりやすい。
　上位の桁の数字が大きい方が確実に強いので、
　上位桁から貪欲に、大きい数字を割り当てられるか判定していく。
　最初桁DPのつもりで書いてたけど、詰めていくと、
　状態が1個しかないので、ただの貪欲になった。
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
    ll a, b, x;
    cin >> a >> b >> x;

    if (a * 1e9 + b <= x) {
        print((int)1e9);
        return;
    }

    ll N = 9, D = 10;
    ll sm = 0;
    string ans;
    rep(i, N) {
        ll mul = pow(10, N - i - 1);
        bool ok = false;
        rep(d, D - 1, -1, -1) {
            if (sm + a * d * mul + b * d <= x) {
                sm +=  + a * d * mul + b * d;
                ans += '0' + d;
                ok = true;
                break;
            }
        }
        assert(ok);
    }
    while (ans[0] == '0') {
        ans.erase(ans.begin());
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

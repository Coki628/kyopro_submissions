/*
・一応、本番中テンパって棄却した方針も通しておく。
　落ち着いて考えたら、繰り上がりが連続しても別に影響なかった。。
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
    ll x, K;
    cin >> x >> K;

    string s = tostr(x);
    reverse(ALL(s));
    s += "000000000000000";
    rep(i, K) {
        if (s[i] >= '5') {
            s[i+1]++;
        }
        s[i] = '0';
    }
    while (s.back() == '0') {
        s.pop_back();
    }
    if (s.empty()) {
        s += '0';
    }
    reverse(ALL(s));
    print(s);
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

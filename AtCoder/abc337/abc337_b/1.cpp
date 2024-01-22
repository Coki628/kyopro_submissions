/*
・最後の判定パートはみんなどうやると楽か結構悩んだみたいで、
　ソート済と比較、が一番簡潔だし賢いなぁと思った。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    string S;
    cin >> S;

    string res;
    for (auto [k, cnt] : RLE(S)) {
        res += k;
    }
    vector<string> ok = {
        "A", "B", "C",
        "AB", "AC", "BC", "ABC"
    };
    YesNo(count(ALL(ok), res));
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

/*
・きっちり自力AC！
・立方数、回文判定
・Nは大きいけど立方数は3乗なので実質10^6くらいで済む。
　オーバーフロー警戒したけど、公式解説見た限り、やんなくても大丈夫だったぽい。
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

#include "string/is_palindrome.hpp"

void solve() {
    ll N;
    cin >> N;

    ll cur = 1, ans = -1;
    while (not mul_overflow(cur, cur) and not mul_overflow(cur * cur, cur) and cur * cur * cur <= N) {
        ll k = cur * cur * cur;
        auto s = tostr(k);
        if (is_palindrome(s)) {
            ans = k;
        }
        cur++;
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

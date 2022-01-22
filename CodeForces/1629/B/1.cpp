/*
・きっちり自力AC！
・GCD
・基本的にGCD=2を目指すのが最善。
　L == R とかを場合分けした後、Lの偶奇によって2の倍数の数が1つ変わるので、
　区間長割る2を切り捨てか切り上げして、K以下ならOK。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    ll l, r, K;
    cin >> l >> r >> K;

    if (l == 1 and r == 1) {
        NO();
        return;
    } elif (l == r) {
        YES();
        return;
    }

    ll len = r-l+1;
    if (l%2 == 1) {
        if (ceil(len, 2LL) <= K) YES();
        else NO();
    } else {
        if (len/2 <= K) YES();
        else NO();
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}

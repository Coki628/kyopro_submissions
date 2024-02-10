/*
・きっちり自力AC！
・バブルソート、重み付き転倒数、BIT2本で個数と総和
・題意より、隣接スワップに1じゃないコストがかかるバブルソートみたいな感じ。
　これは転倒数のBITに1じゃなくて相応の重みを詰めるといい。
　ただし入れ替える時に相手側だけじゃなく自分側の重みも考慮しないといけないので、
　これは入れ替える個数*自分の重みなので、
　結局必要なのは、BIT2本で個数と総和持つお馴染みのやつになる。
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
    ll N;
    cin >> N;
    auto P = LIST(N);

    BIT<ll> bitsm(N + 1), bitcnt(N + 1);
    ll res = 0;
    for (auto a : P) {
        res += bitsm.query(a + 1, N + 1) + bitcnt.query(a + 1, N + 1) * a;
        bitsm.add(a, a);
        bitcnt.add(a, 1);
    }
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

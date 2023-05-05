/*
・自力ならず。これはひどい…。
・インタラクティブ、二分探索
・本番中は、単調性なくてダメじゃん、って詰まってしまったけど、
　実際はどこでもいいから隣り合う場所が見つかればいいので、
　にぶたんで左右端を狭めていけば最終的に隣り合う所にぶつかる。
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

// インタラクティブ用
ll ask(ll i) {
    ll res;
    cout << "? " << i + 1 << endl;
    cin >> res;
    return res;
}

void answer(ll i) {
    cout << "! " << i + 1 << endl;
}

void solve() {
    ll N;
    cin >> N;

    ll res = bisearch_max(0, N, [&](ll x) {
        return ask(x) == 0;
    });
    answer(res);
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

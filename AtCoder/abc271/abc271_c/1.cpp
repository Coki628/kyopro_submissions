/*
・きっちり自力AC！
・二分探索
・決め打ちにぶたん。これもCにしては攻めた感じ？と思ったら貪欲いけるのか。
　貪欲方針頭良すぎ。一生思いつかん。
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
    auto A = LIST(N);

    auto C = Counter(A);
    ll res = bisearch_max(0, 1000000001, [&](ll x) {
        ll sold = 0, need = x;
        for (auto [k, v] : C) {
            if (k > x) {
                sold += v;
            } else {
                sold += v - 1;
                need--;
            }
        }
        return need <= sold/2;
    });
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

/*
・きっちり自力AC！
・決め打ちにぶたん
・にぶたんした。前の1と後ろの0をx回スワップして昇順になるかみたいな。
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

    ll K = count(ALL(A), 1);
    ll res = bisearch_min(-1, K+1, [&](ll x) {
        auto cur = A;
        ll i = 0, j = N-1;
        rep(_, x) {
            while (cur[i] == 0) {
                i++;
            }
            while (cur[j] == 1) {
                j--;
            }
            if (i > j) break;
            swap(cur[i], cur[j]);
        }
        return cur == sorted(cur);
    });
    print(res);
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

/*
・きっちり自力AC！
・mod 3で場合分け。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;

    string ans;
    ll cnt = 0;
    if (N%3 == 1) {
        ll cur = 1;
        while (cnt+cur <= N) {
            ans += tochar(cur);
            cnt += cur;
            cur = 3 - cur;
        }
    } else {
        ll cur = 2;
        while (cnt+cur <= N) {
            ans += tochar(cur);
            cnt += cur;
            cur = 3 - cur;
        }
    }
    print(ans);
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

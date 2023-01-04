/*
・なんとか自力AC…。
・奇数でいける場合のパターンを見抜くのにINF年かかった。
　泣きながら手元でガチャガチャ実験すると、うまく調節できる方法が見つかった。
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

    if (N == 3) {
        NO();
        return;
    }

    if (N % 2 == 1) {
        YES();
        vector<ll> ans(N);
        rep(i, N) {
            if (i % 2 == 0) {
                ans[i] = -((N - 2) / 2);
            } else {
                ans[i] = ceil(N - 2, 2LL);
            }
        }
        print(ans);
    } else {
        YES();
        vector<ll> ans(N);
        rep(i, N) {
            if (i % 2 == 0) {
                ans[i] = 1;
            } else {
                ans[i] = -1;
            }
        }
        print(ans);
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

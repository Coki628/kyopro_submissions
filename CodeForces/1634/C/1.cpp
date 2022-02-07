/*
・自力AC！
・列1は即OK、行奇数は即NG、それ以外は1,3..と2,4..で入れてくとOK。(未証明お祈りAC)
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
    ll H, W;
    cin >> H >> W;
    ll N = H*W;

    if (W == 1) {
        YES();
        rep(i, 1, N+1) {
            print(i);
        }
        return;
    }
    if (H%2 == 1) {
        NO();
        return;
    }
    YES();
    ll cur = 1;
    rep(i, H) {
        vector<ll> row(W);
        rep(j, W) {
            row[j] = cur;
            cur += 2;
            if (cur > N) {
                cur = 2;
            }
        }
        print(row);
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

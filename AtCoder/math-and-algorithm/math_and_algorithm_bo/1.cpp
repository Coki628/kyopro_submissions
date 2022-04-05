/*
・きっちり自力AC。
・式変形
・式変形でループ1個外せるやつ。
　でもこの問題の主旨は、前後が関係ないから定数倍減らせるよってやつだった。
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
    ll N, x, y;
    cin >> N >> x >> y;

    rep(a, 1, N+1) {
        rep(b, 1, N+1) {
            rep(c, 1, N+1) {
                ll d = x - a - b - c;
                if (d > N) continue;
                if (d <= 0) break;
                if (a*b*c*d == y) {
                    Yes();
                    return;
                }
            }
        }
    }
    No();
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

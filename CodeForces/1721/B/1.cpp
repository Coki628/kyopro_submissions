/*
・きっちり自力AC！
・通れなくなる2辺塞がれてないか4通り(上下、左右、上左、下右)チェック。
　OKならいつでも最短距離。
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
    ll N, M, sx, sy, d;
    cin >> N >> M >> sx >> sy >> d;

    ll lx = sx - d;
    ll rx = sx + d;
    ll ly = sy - d;
    ll ry = sy + d;
    if (
        lx <= 1 and rx >= N or
        ly <= 1 and ry >= M or
        lx <= 1 and ly <= 1 or
        rx >= N and ry >= M
    ) {
        print(-1);
        return;
    }
    ll ans = N + M - 2;
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

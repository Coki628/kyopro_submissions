/*
・きっちり自力AC！
・場合分け。絶対無理なやつは別処理。
　短い側は普通に進めて、長い側はちょっと回り道になる。
　-1したら歩数と一致してやりやすくなったと思う。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;

    if (N > M) swap(N, M);
    if (N == 1 and M > 2) {
        print(-1);
        return;
    }
    N--; M--;
    ll ans = N * 2;
    if ((M-N)%2 == 0) {
        ans += (M-N) * 2;
    } else {
        ans += (M-N) * 2 - 1;
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

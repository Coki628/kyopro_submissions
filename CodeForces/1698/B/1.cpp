/*
・自力AC。
・K=1なら最大限作れるし、それ以外なら何も変えれない。(隣まで動いて差分を縮められない)
　K=1のケースをceil(N, 2)-1じゃなくてfloor(N, 2)にしててWA。。
　後から見に来てよくよく考えたら気付けたからまだよかったけど…。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    if (K == 1) {
        ll ans = ceil(N, 2LL) - 1;
        print(ans);
        return;
    }

    ll ans = 0;
    rep(i, 1, N-1) {
        if (A[i] > A[i-1]+A[i+1]) ans++;
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

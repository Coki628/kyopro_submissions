/*
・きっちり自力AC！
・1つでも奇数があればそれで他全部奇数にするが最善。
　よって奇数が1つでもあるかで場合分け。あればN-奇数の個数。
　なければ、1つ奇数にしてから同じことするので、素因数2の最小+N-1。
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

    vector<ll> B(N);
    rep(i, N) {
        while (A[i]%2 == 0) {
            B[i]++;
            A[i] /= 2;
        }
    }
    ll oddcnt = count(ALL(B), 0);
    if (oddcnt > 0) {
        ll ans = N - oddcnt;
        print(ans);
    } else {
        ll ans = min(B) + N - 1;
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

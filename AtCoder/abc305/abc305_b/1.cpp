/*
・ABCから数値への変換とか大小スワップとか、
　後々よく使うようになるテクの組み合わせではあるんだけど、
　それにしても最近のA,B難化してないかね。
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
    vector<ll> A = {3, 1, 4, 1, 5, 9};
    char p, q;
    cin >> p >> q;
    p -= 'A';
    q -= 'A';

    if (p > q) swap(p, q);
    ll ans = 0;
    rep(i, p, q) {
        ans += A[i];
    }
    print(ans);
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

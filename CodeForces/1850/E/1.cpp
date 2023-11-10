/*
・きっちり自力AC！
・決め打ちにぶたん、オーバーフロー対策
・雑にINFを上限にするとオーバーフローしそう。
　doubleにしたらサンプルでもうroundしてもズレたので、
　EPS入れるも状況は改善せず。ldにしたら無事AC。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ld> A(N);
    cin >> A;

    ll res = bisearch_min(0, INF, [&](ld x) {
        ld sm = 0;
        rep(i, N) {
            sm += pow(A[i] + x * 2, 2);
        }
        return round(sm) >= K;
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

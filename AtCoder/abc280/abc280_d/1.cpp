/*
・自力AC！
・素因数分解
・割と悩んだ。素因数毎に見て、必要な個数になるまで追加して、
　その時点でのNをchmax。素因数→篩っぽいループ→割り算して個数数える、
　の3重ループでもそれぞれ少ないので間に合う。
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
    ll K;
    cin >> K;

    ll ans = 1;
    for (auto [k, v] : factorize(K)) {
        ll p = 1, n = k;
        while (p < v) {
            n += k;
            ll cur = n, cnt = 0;
            while (cur % k == 0) {
                cur /= k;
                cnt++;
            }
            p += cnt;
        }
        chmax(ans, n);
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

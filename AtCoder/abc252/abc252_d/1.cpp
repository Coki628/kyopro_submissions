/*
・きっちり自力AC！
・ソートしていい、真ん中固定
・順序はバラしていい。真ん中で使う値aを固定して全探索。a未満の個数*aの個数*a超の個数。
・なんか解法が大きく分けて3つあったぽくて、この真ん中固定と、
　DPと、数学と、全然方針違って面白いなーって思った。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll M = max(A) + 1;
    auto C = Counter(A, M);
    Accumulate<ll> acc(C);
    ll ans = 0;
    UNIQUE(A);
    for (auto a : A) {
        ans += acc.query(0, a) * acc.query(a, a+1) * acc.query(a+1, M);
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

/*
参考：https://codeforces.com/blog/entry/58712
・XOR基底
・2^30の解法。XOR基底を管理すれば、各値を作れるかどうかを陽に持たなくても、
　1回につきO(最大ビット数)くらいでチェックできる。
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

#include "numbers/XorBasis.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);
    vvpll qs(N);
    rep(i, Q) {
        ll l, x;
        cin >> l >> x;
        l--;
        qs[l].eb(x, i);
    }

    XorBasis<ll, 30> basis;
    mint val = 1;
    vector<mint> ans(Q);
    rep(i, N) {
        if (basis.exists(A[i])) {
            val *= 2;
        } else {
            basis.add(A[i]);
        }
        for (auto [x, j] : qs[i]) {
            ans[j] = basis.exists(x) ? val : 0;
        }
    }
    for (auto a : ans) print(a);
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

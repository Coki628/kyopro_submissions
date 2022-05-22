/*
・きっちり自力AC！
・順列、Functional Graph、UF
・順列の任意位置スワップはFunctional Graphってことで、UFでつなぐ。
　連結が2以上になった場所は操作が必要なので、全部ANDする。
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

    UnionFind uf(N);
    rep(i, N) {
        uf.merge(i, A[i]);
    }
    ll msk = (1LL<<30) - 1;
    vector<ll> B(N, msk);
    rep(i, N) {
        if (uf.size(i) > 1) {
            B[uf.find(i)] &= A[i];
        }
    }
    ll ans = msk;
    rep(i, N) {
        ans &= B[i];
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

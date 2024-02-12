/*
・きっちり自力AC！
・区間加算・一点取得、周期
・要は区間加算ができれば良くて、後は周期で余りとか添字気を付ける。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "datastructure/BIT2.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);
    auto B = LIST(M);

    BIT2<ll> bit(N);
    rep(i, N) {
        bit.add(i, A[i]);
    }
    rep(i, M) {
        ll cur = bit[B[i]];
        bit.update(B[i], 0);
        auto [d, m] = divmod(cur, N);
        bit.add(0, N, d);
        ll len = N - B[i] - 1;
        ll len2 = B[i] + 1;
        if (m <= len) {
            bit.add(B[i] + 1, B[i] + 1 + m, 1);
        } else {
            bit.add(B[i] + 1, N, 1);
            m -= len;
            bit.add(0, m, 1);
        }
    }
    vector<ll> ans(N);
    rep(i, N) {
        ans[i] = bit[i];
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

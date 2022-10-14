/*
・きっちり自力AC！
・累積和、累積max、二分探索
・累積和と累積max取ってにぶたん。こういうのやっぱ安心するわー。
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
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);
    auto qs = LIST(Q);

    auto acc = A;
    auto accmx = A;
    rep(i, N-1) {
        acc[i+1] += acc[i];
        chmax(accmx[i+1], accmx[i]);
    }
    acc.insert(acc.begin(), 0);
    accmx.insert(accmx.begin(), 0);

    vector<ll> ans(Q);
    rep(i, Q) {
        ll j = bisearch_max(0, N+1, [&](ll x) {
            return qs[i] >= accmx[x];
        });
        ans[i] = acc[j];
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

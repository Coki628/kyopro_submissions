/*
・きっちり自力AC！
・最小はlower_boundやれば分かる。
　最大は、その要素左に1つずらせないか(無理な時true)を0/1で持って累積和しておくと、
　累積和にぶたんでそこから右に動かせる最大位置が分かる。
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
    auto B = LIST(N);

    // acc[i] := 位置iを左に1つずらせないか
    Accumulate<ll> acc(N);
    rep(i, 1, N) {
        if (A[i] > B[i-1]) {
            acc.set(i, 1);
        }
    }
    acc.build();

    vector<ll> ans1(N), ans2(N);
    rep(i, N) {
        ll j = bisect_left(B, A[i]);
        ans1[i] = B[j] - A[i];
        ll k = bisearch_max(i, N, [&](ll r) {
            return acc.query(i+1, r+1) == 0;
        });
        ans2[i] = B[k] - A[i];
    }
    print(ans1);
    print(ans2);
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

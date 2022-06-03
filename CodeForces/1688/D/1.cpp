/*
・きっちり自力AC！
・場合分け、累積和、等差数列の和
・考えると、元々のAの値と増加分は影響し合わないので独立に考えると見やすい。
　K<=Nなら長さKの区間を全探索で区間和+等差数列の和で最大を取る。
　K>Nならsum(A)は全部取れるとして、増加分がどうなるか考えると、
　どう歩いても最終的に最後の場所はK-1個取れてるし、
　その1歩前はK-2個取れてるみたいになるので、初項K-1,公差-1,項数Nの等差数列の和。
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

#include "numbers/arithmetic_sequence_sum.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    Accumulate<ll> acc(A);
    ll ans = 0;
    if (K <= N) {
        rep(i, N-K+1) {
            ll j = i + K;
            chmax(ans, acc.query(i, j) + arithmetic_sequence_sum(0LL, 1LL, K));
        }
        print(ans);
    } else {
        ans += sum(A) + arithmetic_sequence_sum(K-1, -1LL, N);
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

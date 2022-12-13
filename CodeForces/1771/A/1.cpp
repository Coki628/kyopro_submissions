/*
・きっちり自力AC！
・min(A)とmax(A)の個数が必要。min(A)=max(A)だけ場合分け。
　地味に順序逆のペアがOKだったり。でも2ペナはもったいない…。
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
    vector<ll> A(N);
    cin >> A;

    ll mn = min(A);
    ll mx = max(A);
    ll mncnt = count(ALL(A), mn);
    ll mxcnt = count(ALL(A), mx);
    if (mn == mx) {
        print(N * (N - 1));
    } else {
        print(mncnt * mxcnt * 2);
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
    while (T--)
        solve();

    return 0;
}

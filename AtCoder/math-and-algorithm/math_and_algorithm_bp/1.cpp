/*
・きっちり自力AC！
・括弧列、累積和
・括弧列は+-1する累積和に帰着できるやつ。
　多分スタックで愚直シミュとかでもできるんだけど、
　テーマが言い換えだったから多分こっちかなと思ってこれで。
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

void solve() {
    ll N;
    cin >> N;
    string S;
    cin >> S;

    vector<ll> A(N);
    rep(i, N) {
        if (S[i] == '(') {
            A[i] = 1;
        } else {
            A[i] = -1;
        }
    }
    Accumulate<ll> acc(A);

    if (min(acc.dat) >= 0 and acc.query(0, N) == 0) {
        Yes();
    } else {
        No();
    }
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

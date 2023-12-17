/*
・ある意味本日の戦犯かも。A~Eで相対的に多分一番もたついたと思う。
　公式解説にはちゃんと簡潔に済ます方法も書いてあった。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    vector<char> S(2), T(2);
    cin >> S >> T;

    vector<ll> A(2), B(2);
    rep(i, 2) {
        A[i] = S[i] - 'A';
        B[i] = T[i] - 'A';
    }
    bool type1 = (A[0] + 1) % 5 == A[1] or (A[1] + 1) % 5 == A[0];
    bool type2 = (B[0] + 1) % 5 == B[1] or (B[1] + 1) % 5 == B[0];
    YesNo(type1 == type2);
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

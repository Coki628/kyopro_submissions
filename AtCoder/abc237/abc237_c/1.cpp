/*
・なんとか自力AC！
・本日最大の難所。すげー悩んだ。後ろのa全部消したり前も消したり、色々WAを生やした。
　正解は、手前のaが少なかったら後ろと同じ数まで増やす、だった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

#include "string/is_palindrome.hpp"

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    ll al = 0, ar = 0;
    rep(i, N) {
        if (S[i] == 'a') {
            al++;
        } else {
            break;
        }
    }
    rep(i, N-1, -1, -1) {
        if (S[i] == 'a') {
            ar++;
        } else {
            break;
        }
    }

    if (al < ar) {
        S = string(ar-al, 'a')+S;
    }
    if (is_palindrome(S)) Yes();
    else No();
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

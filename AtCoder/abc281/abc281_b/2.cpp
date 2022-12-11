/*
・charじゃなくてstring用のisdigit作ったのでverify。
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

#include "string/isdigit.hpp"

void solve() {
    string S;
    cin >> S;

    if (S.size() != 8) {
        No();
        return;
    }
    char a = S[0];
    char b = S.back();
    string s = S.substr(1, 6);
    if (not isupper(a) or not isupper(b) or not isdigit(s)) {
        No();
        return;
    }
    ll num = toint(s);
    if (100000 <= num and num <= 999999) {
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

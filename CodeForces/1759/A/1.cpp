/*
・きっちり自力AC！
・最初の文字がY,e,s,他で場合分けした。
　あとはSと正解の文字列で両方index進めて行けばOK。
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
    string S;
    cin >> S;

    string T = "Yes";
    ll i = -1;
    if (S[0] == 'Y') {
        i = 0;
    } elif (S[0] == 'e') {
        i = 1;
    } elif (S[0] == 's') {
        i = 2;
    } else {
        NO();
        return;
    }
    rep(j, S.size()) {
        if (S[j] != T[i%3]) {
            NO();
            return;
        }
        i++;
    }
    YES();
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

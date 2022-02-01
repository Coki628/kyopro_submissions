/*
・きっちり自力AC！
・N<=2は0、後は少数派ほぼ全部消せる。(同数の時だけ-1)
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

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    if (N <= 2) {
        print(0);
        return;
    }
    ll cnta = count(ALL(S), '0');
    ll cntb = N-cnta;
    if (cnta > cntb) swap(cnta, cntb);
    if (cnta == cntb) {
        print(cnta-1);
    } else {
        print(cnta);
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

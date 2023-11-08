/*
・きっちり自力AC！
・2つに分けてソートして元に戻すやつ。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    vector<ll> A1, A2;
    rep(i, N) {
        if (A[i] % 2 == 0) {
            A1.eb(A[i]);
        } else {
            A2.eb(A[i]);
        }
    }
    sort(ALL(A1));
    sort(ALL(A2));
    vector<ll> ans;
    ll j = 0, k = 0;
    rep(i, N) {
        if (A[i] % 2 == 0) {
            ans.eb(A1[j]);
            j++;
        } else {
            ans.eb(A2[k]);
            k++;
        }
    }
    if (ans == sorted(A)) {
        YES();
    } else {
        NO();
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

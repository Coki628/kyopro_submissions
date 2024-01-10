/*
・きっちり自力AC！
・mapで個数管理しながら、indexを1つずつずらしていく。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    string S;
    cin >> S;

    map<char, ll> C1, C2;
    C1[S[0]]++;
    ll cnt1 = 1, cnt2 = 0;
    rep(i, 1, N) {
        C2[S[i]]++;
        if (C2[S[i]] == 1) cnt2++;
    }
    ll ans = cnt1 + cnt2;
    rep(i, 1, N - 1) {
        C1[S[i]]++;
        if (C1[S[i]] == 1) cnt1++;
        C2[S[i]]--;
        if (C2[S[i]] == 0) cnt2--;
        chmax(ans, cnt1 + cnt2);
    }
    print(ans);
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

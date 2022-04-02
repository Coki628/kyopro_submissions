/*
・x,yそれぞれ1つしかない方、なんだけどなんか簡潔に書けなかった。
　TL見てたけど、xorすればいいのめっちゃ賢い。
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
    map<ll, ll> C1, C2;
    ll x1, y1, x2, y2, x3, y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    C1[x1]++;
    C1[x2]++;
    C1[x3]++;
    C2[y1]++;
    C2[y2]++;
    C2[y3]++;
    pll ans;
    for (auto [k, v] : C1) {
        if (v == 1) {
            ans.first = k;
            break;
        }
    }
    for (auto [k, v] : C2) {
        if (v == 1) {
            ans.second = k;
            break;
        }
    }
    print(ans);
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

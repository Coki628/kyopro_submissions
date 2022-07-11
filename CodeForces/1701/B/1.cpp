/*
・きっちり自力AC！
・d=2がいい。N以下で2倍になるやつ優先で使ってく(といいんじゃないかと信じる)。
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

    vector<ll> ans;
    ll d = 2;
    set<ll> se;
    rep(i, 1, N+1) {
        se.insert(i);
    }
    rep(i, 1, N+1) {
        if (se.count(i)) {
            ll j = i;
            while (j <= N) {
                if (se.count(j)) {
                    se.erase(j);
                    ans.eb(j);
                    j *= d;
                } else {
                    break;
                }
            }
        }
    }
    print(d);
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

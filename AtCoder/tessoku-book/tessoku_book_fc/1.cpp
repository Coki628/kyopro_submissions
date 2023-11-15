/*
・きっちり自力AC！
・全列挙できるので、やる。
　再帰と迷ったけど2値なのでビット全探索にした。
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

    vector<string> vec;
    ll M = 10;
    rep(bit, 1LL << M) {
        string cur;
        rep(i, M) {
            if (bit >> i & 1) {
                cur += '4';
            } else {
                cur += '7';
            }
        }
        vec.pb(cur);
    }
    sort(ALL(vec));
    N--;
    print(vec[N]);
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

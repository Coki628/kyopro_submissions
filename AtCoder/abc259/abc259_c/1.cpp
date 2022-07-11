/*
・きっちり自力AC！
・ランレングス圧縮
・S,T両方ランレングスにかけて比べる。
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
    string S, T;
    cin >> S >> T;

    auto rle1 = RLE(S);
    auto rle2 = RLE(T);
    if (rle1.size() != rle2.size()) {
        No();
        return;
    }
    ll M = rle1.size();
    rep(i, M) {
        if (rle1[i].first != rle2[i].first) {
            No();
            return;
        }
        if (rle1[i].second > rle2[i].second) {
            No();
            return;
        }
        if (rle1[i].second < rle2[i].second and rle1[i].second == 1) {
            No();
            return;
        }
    }
    Yes();
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

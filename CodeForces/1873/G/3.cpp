/*
・終了後、頭を切り替えて方針転換。
　ランレングスして、Aのまとまりが来たら、
　左右どっちか(なるべく手前)のBと組ませる貪欲。
　これも状況変わらず無慈悲なWA。ここで自力諦めた。
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
    string S;
    cin >> S;
    ll N = S.size();

    auto rle = RLE(S);
    ll ans = 0;
    rep(i, rle.size()) {
        auto [c, cnt] = rle[i];
        if (c == 'A') {
            if (i > 0 and rle[i - 1].second > 0) {
                ans += cnt;
            } else if (i + 1 < N and rle[i + 1].second > 0) {
                ans += cnt;
                rle[i + 1].second--;
            }
        }
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

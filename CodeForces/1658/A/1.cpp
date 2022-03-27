/*
・きっちり自力AC！
・ランレングス圧縮
・ランレングスして、男子の間に2人ずつ、女子が1人で端じゃなければ1人足す。
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
    ll N;
    cin >> N;
    string S;
    cin >> S;

    auto rle = RLE(S);
    ll M = rle.size();
    ll ans = 0;
    rep(i, M) {
        auto [c, cnt] = rle[i];
        if (c == '0') {
            ans += (cnt-1) * 2;
        } else {
            if (i > 0 and i < M-1 and cnt == 1) {
                ans++;
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

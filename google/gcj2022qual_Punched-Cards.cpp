/*
・きっちり自力AC！
・縦横の偶奇で場合分け。最初4マスだけ最後に.打った。
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
    ll H, W;
    cin >> H >> W;

    H = H * 2 + 1;
    W = W * 2 + 1;
    vector<string> ans(H, string(W, '*'));
    rep(h, H) {
        rep(w, W) {
            if (h%2 == 0) {
                if (w%2 == 0) {
                    ans[h][w] = '+';
                } else {
                    ans[h][w] = '-';
                }
            } else {
                if (w%2 == 0) {
                    ans[h][w] = '|';
                } else {
                    ans[h][w] = '.';
                }
            }
        }
    }
    rep(h, 2) {
        rep(w, 2) {
            ans[h][w] = '.';
        }
    }

    rep(h, H) {
        print(ans[h]);
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
    rep(i, 1, T+1) {
        cout << "Case #" + tostr(i) + ":" << '\n';
        solve();
    }
    return 0;
}

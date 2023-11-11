/*
・きっちり自力AC！
・グリッド、斜め
・斜めも適切に集計する。h+w,h-wでやる。これ大分慣れたかもな。
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
    ll N = 3;
    vector<string> grid(N);
    cin >> grid;

    map<ll, map<char, ll>> mp1, mp2, mp3, mp4;
    rep(h, N) {
        rep(w, N) {
            if (grid[h][w] != '.') {
                mp1[h][grid[h][w]]++;
                mp2[w][grid[h][w]]++;
                mp3[h + w][grid[h][w]]++;
                mp4[h - w][grid[h][w]]++;
            }
        }
    }
    for (auto [k, v] : mp1) {
        for (auto [c, cnt] : v) {
            if (cnt == 3) {
                print(c);
                return;
            }
        }
    }
    for (auto [k, v] : mp2) {
        for (auto [c, cnt] : v) {
            if (cnt == 3) {
                print(c);
                return;
            }
        }
    }
    for (auto [k, v] : mp3) {
        for (auto [c, cnt] : v) {
            if (cnt == 3) {
                print(c);
                return;
            }
        }
    }
    for (auto [k, v] : mp4) {
        for (auto [c, cnt] : v) {
            if (cnt == 3) {
                print(c);
                return;
            }
        }
    }
    print("DRAW");
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

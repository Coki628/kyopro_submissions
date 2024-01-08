/*
・なんとか自力AC。このCに30分近くかかったのは良くない…。
・グリッド、実装、渦巻き
・渦巻きやるのをどう実装するかで完全に方針ミスったな。
　90度回転しながら4回上段埋めれば楽かと思ったら大して楽できなかった。
　結局添字ガチャガチャしてデバッグしてみたいになった。
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

#include "grid/rot90.hpp"

void solve() {
    ll N;
    cin >> N;
    auto grid = listnd(N, N, string());
    grid[N / 2][N / 2] = "T";

    ll cur = 1;
    ll len = N - 1;
    rep(d, N / 2) {
        rep(_, 4) {
            rep(w, len, d, -1) {
                grid[d][w] = tostr(cur);
                cur++;
            }
            grid = rot90(grid);
        }
        len--;
    }
    print(grid, "\n");
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

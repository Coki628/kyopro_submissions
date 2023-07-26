/*
・自力ならず。。
・累積和で貰うDP高速化
・本番中は謎のグリッドDPをこじらせて終了…。方針ミスった。
・まず、最終的に黒マスはまばらになることはなく、
　各列で下から○行目までは黒マス、みたいな形になる。
　これを各列の状態にして左の列からDPしていく。
　それで1列ずつ見ると、黒マスを増やす方の遷移には制限がなくて、
　減らす方は1つ減らすしかできない。
　遷移がまとまりそうなので貰うDPにする。今回下からh行目まで黒くするとすると、
　h+1行目まで黒かった列以下からは遷移できる。となる。
　実装上は累積和方向を横にしたいので90度回転させておく。
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
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    grid = rot90(grid);
    swap(H, W);

    vector<ll> R(H);
    rep(h, H) {
        rep(w, W) {
            if (grid[h][w] == '#') {
                R[h] = w + 1;
            }
        }
    }

    // dp[h][w] := h行目まで見て、左からw列目まで黒く塗った時の通り数
    auto dp = listnd(H + 1, W + 1, (mint)0);
    dp[0][0] = 1;
    rep(h, H) {
        Accumulate<mint> acc(dp[h]);
        rep(w, R[h], W + 1) {
            // w+1以下からは遷移できる
            dp[h + 1][w] = acc.query(0, min(w + 2, W + 1));
        }
    }
    mint ans = sum(dp[H]);
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

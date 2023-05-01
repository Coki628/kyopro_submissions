/*
・とりあえずちゃんと自力AC。
・グリッドDP、下駄履かす
・青diffなので裏があるかもと思って一応書いてみたけどちゃんと通せた。
　値をsetで持ったらさすがにダメで、下駄履かせて生配列で持ったら無事AC。
・過去にやった時とほぼ解法同じだけどなんか遅かったので検討すると、
　DP配列のintをboolにしたらマシになった。
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
    ll H, W;
    cin >> H >> W;
    auto A = listnd(H, W, 0);
    cin >> A;
    auto B = listnd(H, W, 0);
    cin >> B;

    int base = 80 * (H + W) + 7;
    bool dp[H][W][base * 2] = {};
    dp[0][0][base + A[0][0] - B[0][0]] = 1;
    dp[0][0][base + B[0][0] - A[0][0]] = 1;
    rep(h, H) {
        rep(w, W) {
            rep(x, base * 2) {
                if (dp[h][w][x]) {
                    if (h + 1 < H) {
                        dp[h + 1][w][x + A[h + 1][w] - B[h + 1][w]] = 1;
                        dp[h + 1][w][x + B[h + 1][w] - A[h + 1][w]] = 1;
                    }
                    if (w + 1 < W) {
                        dp[h][w + 1][x + A[h][w + 1] - B[h][w + 1]] = 1;
                        dp[h][w + 1][x + B[h][w + 1] - A[h][w + 1]] = 1;
                    }
                }
            }
        }
    }
    ll ans = INF;
    rep(x, base * 2) {
        if (dp[H - 1][W - 1][x]) {
            chmin(ans, abs(base - x));
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

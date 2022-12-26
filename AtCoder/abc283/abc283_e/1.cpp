/*
・自力AC！
・h行目で、直前フリップしたか、2つ前フリップしたか、みたいにDP。
　最初と最後だけ別処理すれば、これで3行ずつ見て遷移できる。
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
    auto mat = listnd(H, W, 0);
    cin >> mat;

    auto dp = listnd(H, 2, 2, INF);
    rep(p1, 2) {
        rep(p2, 2) {
            bool ok = true;
            rep(w, W) {
                ll l = w == 0 ? -1 : (mat[0][w - 1] ^ p1);
                ll r = w == W - 1 ? -1 : (mat[0][w + 1] ^ p1);
                ll d = mat[1][w] ^ p2;
                ll cur = mat[0][w] ^ p1;
                if (cur != l and cur != r and cur != d) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                dp[1][p1][p2] = p1 + p2;
            }
        }
    }
    rep(h, 1, H - 1) {
        rep(p1, 2) {
            rep(p2, 2) {
                rep(p3, 2) {
                    bool ok = true;
                    rep(w, W) {
                        ll u = mat[h - 1][w] ^ p1;
                        ll l = w == 0 ? -1 : (mat[h][w - 1] ^ p2);
                        ll r = w == W - 1 ? -1 : (mat[h][w + 1] ^ p2);
                        ll d = mat[h + 1][w] ^ p3;
                        ll cur = mat[h][w] ^ p2;
                        if (cur != u and cur != l and cur != r and cur != d) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) {
                        chmin(dp[h + 1][p2][p3], dp[h][p1][p2] + p3);
                    }
                }
            }
        }
    }

    ll ans = INF;
    rep(p1, 2) {
        rep(p2, 2) {
            bool ok = true;
            rep(w, W) {
                ll u = mat[H - 2][w] ^ p1;
                ll l = w == 0 ? -1 : (mat[H - 1][w - 1] ^ p2);
                ll r = w == W - 1 ? -1 : (mat[H - 1][w + 1] ^ p2);
                ll cur = mat[H - 1][w] ^ p2;
                if (cur != u and cur != l and cur != r) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                chmin(ans, dp[H - 1][p1][p2]);
            }
        }
    }
    if (ans == INF) ans = -1;
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

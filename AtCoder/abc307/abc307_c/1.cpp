/*
・自力AC！
・グリッド、実装
・先に#がない領域は潰しておく。これでめちゃ端っこ同士みたいなやつを考えなくてよくなる。
　その上で、グリッドXを固定してA,Bの開始位置を全探索。
　両方うまくはまってかつ、Xに必要な場所を全部塗り潰せたかどうかもチェックする。
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
    vector<ll> H(3), W(3);
    vv<string> grid(3);
    rep(i, 3) {
        cin >> H[i] >> W[i];
        grid[i].resize(H[i]);
        cin >> grid[i];
    }

    rep(i, 3) {
        ll mnh = INF, mxh = -INF, mnw = INF, mxw = -INF;
        rep(h, H[i]) {
            rep(w, W[i]) {
                if (grid[i][h][w] == '#') {
                    chmin(mnh, h);
                    chmax(mxh, h);
                    chmin(mnw, w);
                    chmax(mxw, w);
                }
            }
        }
        H[i] = mxh - mnh + 1;
        W[i] = mxw - mnw + 1;
        vector<string> nxt(H[i]);
        rep(h, mnh, mxh + 1) {
            rep(w, mnw, mxw + 1) {
                nxt[h - mnh] += grid[i][h][w];
            }
        }
        grid[i] = nxt;
    }

    auto check = [&](ll i, ll sh, ll sw, vvi &ok) {
        rep(h, H[i]) {
            if (sh + h >= H[2]) {
                return false;
            }
            rep(w, W[i]) {
                if (sw + w >= W[2]) {
                    return false;
                }
                if (grid[2][sh + h][sw + w] == '#') {
                    if (grid[i][h][w] == '#') {
                        ok[sh + h][sw + w] = 1;
                    }
                } else {
                    if (grid[i][h][w] == '#') {
                        return false;
                    }
                }
            }
        }
        return true;
    };

    rep(h1, H[2]) {
        rep(w1, W[2]) {
            rep(h2, H[2]) {
                rep(w2, W[2]) {
                    auto ok = listnd(H[2], W[2], 0);
                    if (check(0, h1, w1, ok) and check(1, h2, w2, ok)) {
                        bool okok = true;
                        rep(h3, H[2]) {
                            rep(w3, W[2]) {
                                if (grid[2][h3][w3] == '#' and not ok[h3][w3]) {
                                    okok = false;
                                    break;
                                }
                            }
                            if (not okok) break;
                        }
                        if (okok) {
                            Yes();
                            return;
                        }
                    }
                }
            }
        }
    }
    No();
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

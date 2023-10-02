/*
・自力AC！
・実装、グリッド
・回転と開始位置で9重ループした。
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
    ll N = 4;
    auto grids = listnd(3, N, string(N, '.'));
    rep(p, 3) {
        cin >> grids[p];
    }

    auto check = [&](array<ll, 3> dh, array<ll, 3> dw) {
        auto res = listnd(N, N, 0);
        rep(p, 3) {
            rep(h, N) {
                rep(w, N) {
                    if (grids[p][h][w] == '#') {
                        // #がはみ出る
                        if (h + dh[p] >= N or w + dw[p] >= N) {
                            return false;
                        }
                        res[h + dh[p]][w + dw[p]]++;
                    }
                }
            }
        }
        rep(h, N) {
            rep(w, N) {
                // ない or 2つ以上重なった
                if (res[h][w] != 1) {
                    return false;
                }
            }
        }
        return true;
    };

    rep(_, 4) {
        rep(__, 4) {
            rep(___, 4) {
                // 左上に寄せる
                rep(p, 3) {
                    ll mnrow = INF, mncol = INF;
                    rep(h, N) {
                        rep(w, N) {
                            if (grids[p][h][w] == '#') {
                                chmin(mnrow, h);
                                chmin(mncol, w);
                            }
                        }
                    }
                    vector<string> tmp(N, string(N, '.'));
                    rep(h, N) {
                        rep(w, N) {
                            if (grids[p][h][w] == '#') {
                                tmp[h - mnrow][w - mncol] = '#';
                            }
                        }
                    }
                    grids[p] = tmp;
                }
                rep(h0, N) {
                    rep(w0, N) {
                        rep(h1, N) {
                            rep(w1, N) {
                                rep(h2, N) {
                                    rep(w2, N) {
                                        if (check({h0, h1, h2}, {w0, w1, w2})) {
                                            Yes();
                                            return;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                grids[2] = rot90(grids[2]);
            }
            grids[1] = rot90(grids[1]);
        }
        grids[0] = rot90(grids[0]);
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

/*
・順列全探索
・判定パートが斜めとかあって(Cにしては)結構つらめ。
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
    ll H = 3, W = 3, N = 9;
    auto grid = listnd(H, W, 0);
    rep(i, H) {
        rep(j, W) {
            cin >> grid[i][j];
        }
    }

    vector<ll> vec(N);
    iota(ALL(vec), 0);
    ll ok = 0, total = 0;
    for (auto perm : permutations(vec)) {
        auto visited = listnd(H, W, 0);
        bool okok = true;
        rep(i, N) {
            auto [h, w] = idtogrid(perm[i], W);
            // 縦
            vector<ll> C(10);
            rep(ch, H) {
                if (visited[ch][w]) {
                    C[grid[ch][w]]++;
                }
            }
            if (max(C) == 2) {
                okok = false;
            }
            // 横
            C.assign(10, 0);
            rep(cw, W) {
                if (visited[h][cw]) {
                    C[grid[h][cw]]++;
                }
            }
            if (max(C) == 2) {
                okok = false;
            }
            // 斜め1
            C.assign(10, 0);
            ll hw = h + w;
            rep(ch, H) {
                rep(cw, W) {
                    if (visited[ch][cw] and ch + cw == hw) {
                        C[grid[ch][cw]]++;
                    }
                }
            }
            if (max(C) == 2) {
                okok = false;
            }
            // 斜め2
            C.assign(10, 0);
            hw = h - w;
            rep(ch, H) {
                rep(cw, W) {
                    if (visited[ch][cw] and ch - cw == hw) {
                        C[grid[ch][cw]]++;
                    }
                }
            }
            if (max(C) == 2) {
                okok = false;
            }
            visited[h][w] = 1;
        }
        if (okok) {
            ok++;
        }
        total++;
    }
    ld ans = ok / (ld)total;
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

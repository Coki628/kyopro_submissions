/*
・自力AC！けどちょっとハズレ方針引いた感。
・だる実装。中心と伸ばす長さ決めて全探索した。重複を避けるため大きい方から。
・別解でUF使ってるの賢い。制約で各バツ印が離れてるのが保証されてるから、それでもいいのか。
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

// 斜め移動用(右下→右上→左上→左下みたいに対角線に進む)
const vector<pii> dir_diagonals = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    ll N = min(H, W);
    vector<ll> ans(N);
    auto used = listnd(H, W, 0);
    rep(n, N, 0, -1) {
        rep(h, H) {
            rep(w, W) {
                if (grid[h][w] != '#' or used[h][w]) continue;
                bool ok = true;
                for (auto [dh, dw] : dir_diagonals) {
                    ll ch = h, cw = w;
                    rep(_, n) {
                        ch += dh, cw += dw;
                        if (ch < 0 or cw < 0 or ch >= H or cw >= W) {
                            ok = false;
                            break;
                        }
                        if (grid[ch][cw] != '#') {
                            ok = false;
                            break;
                        }
                    }
                    if (not ok) break;
                }
                if (ok) {
                    ans[n - 1]++;
                    used[h][w] = 1;
                }
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
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}

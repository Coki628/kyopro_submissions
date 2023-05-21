/*
・公式解説の実装を参考に。
　内側で8方向ループで向き決めて5回回すときれいに作れる。
　この内側で方向ループ回すパターン忘れがちなんだよね…。
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

#include "grid/constants/dir8.hpp"

void solve() {
    ll H, W;
    cin >> H >> W;
    vector<string> grid(H);
    cin >> grid;

    rep(h, H) {
        rep(w, W) {
            for (auto [dh, dw] : dir8) {
                ll ch = h, cw = w;
                vector<pll> res;
                rep(_, 5) {
                    res.eb(ch, cw);
                    ch += dh;
                    cw += dw;
                }
                if (ch < -1 or cw < -1 or ch > H or cw > W) {
                    continue;
                }
                string S;
                for (auto [i, j] : res) {
                    S += grid[i][j];
                }
                if (S == "snuke") {
                    res++;
                    print(res, '\n');
                    return;
                }
            }
        }
    }
    assert(0);
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

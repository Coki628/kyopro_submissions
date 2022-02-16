/*
・dojo set_e_3_3
・きっちり自力AC！これは結構考察早かった。
・余事象に注目
・1つの操作が影響を与えるのは最大で周囲9マスだけなので、
　C[{i, j}] := (i, j)を中心とした9マスで黒く塗られた数
　みたいのを変化のあったマスだけマップで持っておけば0以外は分かるし、
　0なのは9マス領域の全通りから変化のあったマス数を引けば分かる。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll H, W, N;
    cin >> H >> W >> N;

    map<pll, ll> C;
    rep(i, N) {
        ll h, w;
        cin >> h >> w;
        h--; w--;
        ll sh = max(h-1, 1LL);
        ll sw = max(w-1, 1LL);
        ll th = min(h+1, H-2);
        ll tw = min(w+1, W-2);
        rep(ch, sh, th+1) {
            rep(cw, sw, tw+1) {
                C[{ch, cw}]++;
            }
        }
    }

    vector<ll> ans(10);
    for (auto [k, v] : C) {
        ans[v]++;
    }
    ans[0] = (H-2)*(W-2)-C.size();
    for (auto a : ans) print(a);
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

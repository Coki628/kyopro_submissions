/*
・燃やす埋めるの確認
・先に市松を反転させてたけど、もっと汎用的に
　「選択肢のA,Bをひっくり返す」でいいらしいとのことなので検証。問題なくAC。
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

#include "atcoder/maxflow"
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    vector<string> grid(N);
    rep(i, N) cin >> grid[i];

    mf_graph<ll> mf(N*N+2);
    ll s = N*N;
    ll t = N*N+1;
    rep(h, N) {
        rep(w, N) {
            ll i = gridtoid(h, w, N);
            ll useb = 0, usew = 0;
            // 色が決まってる時はカットで選びたくない方をINFに
            if (grid[h][w] == 'B') {
                usew = INF;
            }
            if (grid[h][w] == 'W') {
                useb = INF;
            }
            // 市松の片方は条件を逆にする
            if ((h+w)%2 == 0) {
                swap(useb, usew);
            }
            // 始点・終点との辺
            mf.add_edge(s, i, useb);
            mf.add_edge(i, t, usew);

            // マス同士の辺
            if (h != N-1) {
                ll j = gridtoid(h+1, w, N);
                mf.add_edge(i, j, 1);
                mf.add_edge(j, i, 1);
            }
            if (w != N-1) {
                ll j = gridtoid(h, w+1, N);
                mf.add_edge(i, j, 1);
                mf.add_edge(j, i, 1);
            }
        }
    }
    // 最大利得から、最小カットを引く
    ll total = N*(N-1)*2;
    ll ans = total - mf.flow(s, t);
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

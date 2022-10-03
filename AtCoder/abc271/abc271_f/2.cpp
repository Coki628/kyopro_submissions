/*
参考：TLの情報
・自力ならず。。
・グリッドDP、XOR、半分全列挙
・これは気付かなかった。これ青パフォ下位ってみんな気付きすぎっしょ。。
　20*20=400でやけに小さめなグリッドだなぁとは思ったけど、
　じゃあ追加で状態持たせるとしたら何だろう、って方向でしか考えられなかった。
　20+20=40っていう移動回数に注目できたらよかった。
　制約40って言われると確かに半分全列挙が思いつきそう。
・全部グリッドDPしようとすると、40回くらい動くので
　(おそらく)最悪で2^30全部状態として取りうるくらいになって無理。
　ここでこの40回の移動をグリッドの半分までの20回とすると、
　取りうる状態が(おそらく)最悪で2^20くらいに抑えられる。
　これをグリッドの前後からやって、対角線で突き合わせればいい。
　片側からやって、そのマスを相殺すれば、0にするために逆側から欲しい値が定まるので、
　これをmapとかで管理して適切に探せればOK。
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
    ll N;
    cin >> N;
    auto grid = listnd(N, N, 0LL);
    rep(i, N) {
        rep(j, N) {
            cin >> grid[i][j];
        }
    }

    auto dp1 = listnd(N, N, HashMap<ll, ll>());
    dp1[0][0][grid[0][0]] = 1;
    rep(i, N) {
        rep(j, N) {
            if (i+j >= N-1) continue;
            for (auto [k, v] : dp1[i][j]) {
                if (i+1 < N) {
                    dp1[i+1][j][grid[i+1][j]^k] += v;
                }
                if (j+1 < N) {
                    dp1[i][j+1][grid[i][j+1]^k] += v;
                }
            }
        }
    }

    auto revgrid = listnd(N, N, 0LL);
    rep(i, N) {
        rep(j, N) {
            revgrid[i][j] = grid[N-j-1][N-i-1];
        }
    }
    auto dp2 = listnd(N, N, HashMap<ll, ll>());
    dp2[0][0][revgrid[0][0]] = 1;
    rep(i, N) {
        rep(j, N) {
            if (i+j >= N-1) continue;
            for (auto [k, v] : dp2[i][j]) {
                if (i+1 < N) {
                    dp2[i+1][j][revgrid[i+1][j]^k] += v;
                }
                if (j+1 < N) {
                    dp2[i][j+1][revgrid[i][j+1]^k] += v;
                }
            }
        }
    }

    ll ans = 0;
    rep(i, N) {
        ll j = N - i - 1;
        for (auto [k1, v1] : dp1[i][j]) {
            ll k2 = k1 ^ grid[i][j];
            if (dp2[i][j].count(k2)) {
                ll v2 = dp2[i][j][k2];
                ans += v1 * v2;
            }
            // for (auto [k2, v2] : dp2[i][j]) {
            //     if ((k1^k2^grid[i][j]) == 0) {
            //         ans += v1 * v2;
            //     }
            // }
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

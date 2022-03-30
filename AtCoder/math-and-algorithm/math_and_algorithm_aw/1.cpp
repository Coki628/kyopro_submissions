/*
・自力AC！
・スライドbitDP、行列累乗
・ほぼabc204_f(Hanjo 2)なんだけど、単体1マスに置けないので微妙に遷移が違う。
　ただ半畳置く方の遷移をなくすだけだとダメだった。
　というのも、そこには「既に置かれてるので何もしない」の遷移が含まれていたから。
　これは今回の条件でも遷移する。これを考慮したDPにすると通る。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "matrix/MatPow.hpp"

void solve() {
    ll W, H;
    cin >> W >> H;

    // ll N = H * W;
    // // dp[i][bit] := iマス目まで埋め終わって、先Wマスの埋まり方がbitの時の通り数
    // auto dp = list2d<mint>(N+1, 1LL<<W, 0);
    // dp[0][0] = 1;
    // rep(i, N) {
    //     auto [h, w] = divmod(i, W);
    //     rep(bit, 1LL<<W) {
    //         if (bit>>0 & 1) {
    //             // 既に置かれていたら、何もしないでここを埋めたものとして遷移
    //             dp[i+1][bit>>1] += dp[i][bit];
    //         } else {
    //             // 縦置き
    //             dp[i+1][(bit>>1)|(1LL<<(W-1))] += dp[i][bit];
    //             if (w != W-1 and !(bit>>1 & 1)) {
    //                 // 横置き
    //                 dp[i+1][(bit>>1)|(1LL<<0)] += dp[i][bit];
    //             }
    //         }
    //     }
    // }
    // mint ans = dp[N][0];
    // print(ans);

    ll N = 1LL<<W;
    auto mat = list2d<mint>(N, N, 0);
    rep(from, N) {
        auto dp = list3d<mint>(2, W, N, 0);
        dp[0][0][from] = 1;
        rep(h, 1) {
            rep(w, W) {
                rep(bit, 1LL<<W) {
                    if (bit>>0 & 1) {
                        // 既に置かれていたら、何もしないでここを埋めたものとして遷移
                        dp[h+(w == W-1)][(w+1)%W][bit>>1] += dp[h][w][bit];
                    } else {
                        // 縦置き
                        dp[h+(w == W-1)][(w+1)%W][(bit>>1)|(1LL<<(W-1))] += dp[h][w][bit];
                        if (w != W-1 and !(bit>>1 & 1)) {
                            // 横置き
                            dp[h+(w == W-1)][(w+1)%W][(bit>>1)|(1LL<<0)] += dp[h][w][bit];
                        }
                    }
                }
            }
        }
        rep(to, N) {
            mat[to][from] = dp[1][0][to];
        }
    }
    vector<mint> init(N);
    init[0] = 1;
    MatPow<mint> mp;
    auto res = mp.solve(mat, init, H);
    print(res[0]);
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

/*
参考：https://maspypy.com/%e5%a4%9a%e9%a0%85%e5%bc%8f%e3%83%bb%e5%bd%a2%e5%bc%8f%e7%9a%84%e3%81%b9%e3%81%8d%e7%b4%9a%e6%95%b0%ef%bc%88%ef%bc%92%ef%bc%89%e5%bc%8f%e5%a4%89%e5%bd%a2%e3%81%ab%e3%82%88%e3%82%8b%e8%a7%a3%e6%b3%95#toc15
・FPS演習、戻すDP
・FPS除算を使えば、あるDP結果から途中の特定の遷移分を除いた結果も一発で出せる。
　DPとしては戻すDPってやつで、聞いたことはあるけどやったことないテクだったけど、
　FPSの式として処理するとびっくりするくらいに殴れる。すごいね。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define MINT_TO_LL_CAST
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

#include "math/FormalPowerSeries.hpp"
#include "math/fps/pow_term2.hpp"

void solve() {
    ll N, M, Q;
    cin >> N >> M >> Q;
    auto A = LIST(N);

    // まずは普通に全体でやったDP結果を用意
    FPS<mint> dp(M+1);
    dp[0] = 1;
    rep(i, N) {
        dp *= SFPS<mint>{{0, 1}, {A[i]+1, -1}};
    }
    dp *= pow_term2_inv(N, M+1);

    // ans[i][j] := i番目の商品以外で、j個選ぶ通り数
    vector<FPS<mint>> ans(N, {dp});
    rep(i, N) {
        // i番目の遷移を除いた結果 = 全体 / i番目の遷移
        ans[i] /= SFPS<mint>{{0, 1}, {A[i]+1, -1}};
        ans[i] *= SFPS<mint>{{0, 1}, {1, -1}};
    }

    rep(_, Q) {
        ll k, x;
        cin >> k >> x;
        k--;

        // i番目の商品以外で、M-x個選べば全体でちょうどM個
        if (M-x < 0) {
            print(0);
        } else {
            print(ans[k][M-x]);
        }
    }
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

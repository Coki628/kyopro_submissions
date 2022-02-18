/*
・dojo set_d_4_6
・自力AC！やったね。
・FPS、戻すDP
・ついこの前やった知見を活用できた。FPSで解釈すると、
　DPの途中の遷移1回だけをなかったことにするのが、多項式除算1回でできる。
　今回の1つだけ使わないでどうかという条件はまさにこれがハマる。
・ちょっと気になったのは、今回はMOD取る数え上げではないので、
　たまに間違って0になってしまう場所が出てくるんじゃないかってこと。
　WAが出たらMOD2つで再提出するかーくらいで投げたけど普通に通った。
　この件はユーザー解説欄でnoshiさんが言及してくれていて、まあ何か大丈夫らしい。
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

#include "math/FormalPowerSeries.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    vector<FPS<mint>> fps(N, {K});
    FPS<mint> dp(K);
    dp[0] = 1;
    rep(i, N) {
        dp *= SFPS<mint>{{0, 1}, {A[i], 1}};
    }

    ll ans = 0;
    rep(i, N) {
        auto cur = dp / SFPS<mint>{{0, 1}, {A[i], 1}};
        bool need = false;
        rep(j, K) {
            if (cur[j] == 0) continue;
            if (j+A[i] >= K) {
                need = true;
                break;
            }
        }
        if (not need) ans++;
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

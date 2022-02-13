/*
参考：https://kaichou243.hatenablog.com/entry/2022/02/09/125124
　　　https://qiita.com/hotman78/items/f0e6d2265badd84d429a#8-%E9%83%A8%E5%88%86%E5%92%8C%E5%95%8F%E9%A1%8C
・FPS演習
・FPS、部分和DP
・部分和DPだと2乗だけどFPS使うと線形logに落とせる。
・本来のDP遷移を考えると多項式の乗算がN回必要になるが、
　これを式変形してlogの形にすると、総乗が総和になって、
　log(1+f(x))はいい感じに調和級数で計算できるので、合わせても線形logに収まる。
　とはいえ、集合Aが1,1,1,1..みたいのだと調和級数にならないので、
　予めCounterしておいて、値毎で個数分重み付けしてやる感じにする。
　ここまでlogの世界で計算しているので、expで元の値に戻す。
・でもこれ結構重くて、100万のNと50万のSで2秒ちょいかかる。(制約10秒)
　mod除算のlogをなくすために前計算とかしたんだけど、
　FPSのexpの中でも除算呼んでるっぽくて、多分そこも前計算しないと速くならない。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

#include "math/FormalPowerSeries.hpp"

void solve() {
    ll N, S;
    cin >> N >> S;
    auto A = LIST(N);

    // auto dp = list2d<mint>(N+1, S+1, 0);
    // dp[0][0] = 1;
    // rep(i, N) {
    //     rep(j, S+1) {
    //         dp[i+1][j] += dp[i][j];
    //         if (j+A[i] <= S) {
    //             dp[i+1][j+A[i]] += dp[i][j];
    //         }
    //     }
    // }
    // vector<mint> ans(dp[N].begin()+1, dp[N].end());
    // print(ans);

    FPS<mint> ans(S+1);
    ModTools<mint> mt(S);
    // これは1,1,1,1..みたいなやつでやばい
    // rep(i, N) {
    //     ll k = 1;
    //     while (A[i]*k <= S) {
    //         ans[A[i]*k] += (mint)(k&1 ? 1 : -1)*inv[k];
    //         k++;
    //     }
    // }
    auto C = Counter(A, S);
    rep(a, 1, S+1) {
        if (C[a] == 0) continue;
        ll k = 1;
        while (a*k <= S) {
            ans[a*k] += (mint)(k&1 ? 1 : -1)*mt.div(C[a], k);
            k++;
        }
    }
    ans = ans.exp(S+1);
    ans.erase(ans.begin());
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

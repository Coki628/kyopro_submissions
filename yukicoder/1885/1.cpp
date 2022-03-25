/*
参考：https://yukicoder.me/problems/no/1885/editorial
・順列、DP、グラフに帰着、経路
・めっちゃ賢い。絶対思いつかなかったな。
・変な順列のDPしか考えつかなかった。挿入DPみたいな絶対2乗かかるようなやつとか、
　20万あるから、BITか何かでinplace DPっぽくするとか。
・まあどれもハズレで、正解はグラフに帰着。頂点xから頂点yへの経路と考える。
　で、遷移は1,2歩しか動けないみたいな。でもここに色々条件がつく。
・まず、xより手前とyより後ろ。前後1,2歩しか動けず、2回訪問がダメであることを考慮すると、
　実は1通りしか回ってくる方法がない。これ気付かねー。。
　で、全部回ってきて、始点/終点がいっこずれるみたいになる。
・x-y間も考察が要る。本当は前後に動けるので、DP無理そうに思える。
　がしかしここでも実は前後1,2歩しか動けず、2回訪問がダメであることを考慮すると、
　そこより手前を全部埋めながらある位置に到達するには、
　1歩進むか3歩進むの2通りしか方法がない。これも気付かねー。。
・これらを全部詰めると、いわゆるカエルがジャンプするDPみたいなやつになる。
　順列の並べ方の数え上げで、このグラフに帰着(てか経路のDPか)の考察は、
　まじで気付かないね。こういうのもあるって頭の片隅に入れとかないと。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
#include "template.hpp"

void solve() {
    ll N, x, y;
    cin >> N >> x >> y;
    x--; y--;

    if (x > y) swap(x, y);
    // 手前を回ってくる分
    if (x > 0) x++;
    // 後ろを回ってくる分
    if (y < N-1) y--;
    if (x > y) {
        print(0);
        return;
    }

    // dp[i] := 位置i以前を全て訪問済で、位置iにいる通り数
    vector<mint> dp(N);
    dp[x] = 1;
    rep(i, x, y) {
        // 1歩進む
        dp[i+1] += dp[i];
        // 2歩進んで1歩戻って2歩進む
        if (i+3 <= y) {
            dp[i+3] += dp[i];
        }
    }
    mint ans = dp[y];
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

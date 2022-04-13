/*
参考：https://twitter.com/e869120/status/1414166071594999811/photo/
　　　https://github.com/E869120/kyopro_educational_90/blob/main/sol/090-04.cpp
・E8さん典型90問埋め
・部分点3やっと取った。むずくて保留にしてたやつ。
・難しい区間DP、最大長方形
・題意の条件は最大長方形を数え上げる感じに帰着する。
　で、普通の区間DPに加えて高さの情報も持って、高い方からDPする。
　最小値を固定して、徐々に下げていく感じなので、
　dp[l][r][k] := 区間[l,r)の最小値がk以上である通り数
　のようにする。
・遷移は「区間[l,r)の最小値がk+1以上である場合」と
　「位置mで一番右の最小値kを取る場合」のΣ[l,r)になる。
　前者はそのまま持ってくるだけだけど後者はもう少し嚙み砕いて説明する。
・mを決め打つので、[l,m)と[m+1,r)の値は自由に選べるとして掛け合わせる。
　この時最小値はどうなっているかと言うと、mで一番右の最小値kを取っているので、
　[l,m)ではk、[m+1,r)ではk+1とする。
・また、この遷移をやろうとすると、区間長1,2での値を決める時に、
　区間長0との掛け算が出てくる。本来区間長0なんて存在しない値なので
　通り数0にしたい所だが、遷移で掛け算する兼ね合いで、ここを1とした方が色々都合がいい。
・練習のため、途中まで書いてた非再帰版も仕上げて通しておいた。
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
    ll N, K;
    cin >> N >> K;

    assert(N <= 100 and K <= 100);

    // dp[l][r][k] := 区間[l,r)の最小値がk以上である通り数
    auto dp = list3d<mint>(N+1, N+1, K+2, 0);
    rep(i, N+1) {
        rep(k, K+2) {
            // 遷移で掛け合わすので区間長0を通り数1と定義する
            dp[i][i][k]++;
        }
    }
    rep(k, K, -1, -1) {
        rep(len, 1, N+1) {
            rep(l, N-len+1) {
                ll r = l + len;
                if (k*len > K) continue;
                // 区間[l,r)の最小値がk+1以上である場合の遷移
                dp[l][r][k] += dp[l][r][k+1];
                rep(m, l, r) {
                    // 位置mで一番右の最小値kを取る場合の遷移
                    dp[l][r][k] += dp[l][m][k] * dp[m+1][r][k+1];
                }
            }
        }
    }
    mint ans = dp[0][N][0];
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

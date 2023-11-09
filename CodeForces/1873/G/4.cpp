/*
参考：https://www.youtube.com/watch?v=S8viLQC8Dks
・自力ならず。こういう賢く貪欲しなきゃいけないやつ負けがち。。
・ランレングスしてDP
・TLはみんな賢い貪欲を展開していたけど、それを本番中自力で導くのはつらそうで、
　こたつがめさんの動画がDPで解いていたのでそっちを参考に仕上げた。
・結局、自分のWAが取れなかったのは、
　なるべく大きいAの塊を優先しなければいけない所を、手前から貪欲っぽく使っていたから。
　こういうのはだいたい賢い貪欲かDPに落とし込むだけど、今回はDPでもいけた。
　操作はB1個とAたくさんみたいにまとめられて、これを
　「AA....AAB」と「BAA....AA」の2つの遷移で表現する。
　ランレングスしてあればこれは添字1個進める感じで書けるからやりやすい。
　直前で操作したかを状態に持てば、その位置のAが操作済か、
　その位置のBが1つ減っているか、が分かるので、その位置で操作できるかが分かる。
　ここまで分かれば後はその位置で操作するかしないかでいつものDPだ。
・賢い貪欲が思いつかないのはしょうがないとして、
　このくらいをぱっとDPできるくらいの地力をしっかりつけていきたいなー。。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    auto rle = RLE(S);
    ll M = rle.size();
    auto dp = listnd(M + 1, 2, -INF);
    dp[0][0] = 0;
    rep(i, M) {
        auto [c, cnt] = rle[i];
        rep(j, 2) {
            chmax(dp[i + 1][0], dp[i][j]);
            if (i + 1 < M) {
                if (c == 'A' and j == 0) {
                    // AA....AAB
                    chmax(dp[i + 1][1], dp[i][j] + cnt);
                } else if (c == 'B' and cnt - j > 0) {
                    // BAA....AA
                    chmax(dp[i + 1][1], dp[i][j] + rle[i + 1].second);
                }
            }
        }
    }
    ll ans = dp[M][0];
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}

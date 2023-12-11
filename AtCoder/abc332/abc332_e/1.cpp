/*
・終了後自力AC、ならず。。
・bitDP、部分集合列挙
・(TLでヒント得ていたとはいえ)いいとこまで出来てたのに、
　最後の前計算高速化に気付けずTLEが取れなかった。
・分散を最小にとか難しいこと言ってるけど、定義よく見てその通りにやる。
　1つめの気付きとして、コスト計算に使う平均はグループの分け方に依らないので、
　先に用意しておく。これで最深部の個々のコスト出す時はすぐ出せる。
　ってここで気付くべきだったんだけど、個々の集合での和も前計算で用意しておく。
　これやらないで最深部にN<=15が余分に乗ったらTLE…。
・bitDPの部分集合列挙はよくあるけど、今回ちょっと違う点として、
　その時点の部分集合じゃなくて、その補集合でやってる。
　今まで終わった集合全部から貰うDPしてるのがいつもで、
　ここまででやってない集合全部に配るDPしてるのが今回って感じ。
　計算量は同じく3^Nに落とせてるはず。
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
    ll N, D;
    cin >> N >> D;
    vector<ll> W(N);
    cin >> W;

    // 前計算
    vector<ll> sm(1LL << N);
    rep(bit, 1LL << N) {
        rep(i, N) {
            if (bit >> i & 1) {
                sm[bit] += W[i];
            }
        }
    }
    ll allsm = sum(W);
    ld avg = allsm / (ld)D;
    ll msk = (1LL << N) - 1;
    auto dp = listnd(D + 1, 1LL << N, (ld)INF);
    dp[0][0] = 0;
    rep(i, D) {
        rep(bit, 1LL << N) {
            // 今含まれていない集合を全列挙
            ll S = msk ^ bit;
            ll T = S;
            while (T > 0) {
                // ll sm = 0;
                // rep(j, N) {
                //     if (T >> j & 1) {
                //         sm += W[j];
                //     }
                // }
                chmin(dp[i + 1][bit | T], dp[i][bit] + pow(sm[T] - avg, 2));
                T = (T - 1) & S;
            }
        }
    }
    ld ans = dp[D][msk] / D;
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

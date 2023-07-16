/*
参考：https://atcoder.jp/contests/abc310/editorial/6791
・自力ならず。。。悔しい。
・bitDP、確率DP
・11以降をまとめて状態減らすのはやったんだけど、ビットで管理する発想が出なくて、
　「i番目まで見て、作った値がj(11以降は同一視)」みたいなDPで全然合わなくて撃沈。
　A[i]通りの遷移はいいとして、この位置を使うor使わないに
　確率の係数をどう振り分けるか分からず。(多分この方針じゃ無理なんだと思う)
・正解は0～10が作れる状態かどうかをビットに持つ、だった。
　確かにこれだと使うor使わないで状態分けなくていいので、
　普通な感じの確率DPの遷移(A[i]で割りながら足す)に落とせる。
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
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    ll M = 10;
    auto dp = listnd(N + 1, 1LL << (M + 1), (mint)0);
    dp[0][1] = 1;
    rep(i, N) {
        rep(bit1, 1LL << (M + 1)) {
            rep(a, 1, min(A[i], M) + 1) {
                ll bit2 = bit1;
                rep(j, M + 1) {
                    if (bit1 >> j & 1 and j + a <= M) {
                        bit2 |= 1LL << (j + a);
                    }
                }
                // 今の集合+aで作れる集合へ遷移
                dp[i + 1][bit2] += dp[i][bit1] / A[i];
            }
            // a=11以降は集合に変化なし
            if (A[i] > M) {
                dp[i + 1][bit1] += dp[i][bit1] * (A[i] - M) / A[i];
            }
        }
    }
    mint ans = 0;
    rep(bit, 1LL << (M + 1)) {
        if (bit >> M & 1) {
            ans += dp[N][bit];
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

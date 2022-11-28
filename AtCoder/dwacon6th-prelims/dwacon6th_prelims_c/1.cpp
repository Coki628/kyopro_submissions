/*
参考：https://ei1333.hateblo.jp/entry/2021/07/30/144201
　　　https://betrue12.hateblo.jp/entry/2020/01/12/160124
　　　https://drken1215.hatenablog.com/entry/2020/01/12/011700
・期待値、積の和典型
・むずい。考え方的には、アルメリアさんの「注目するやつを決める通り数」を
　掛けるイメージが比較的しっくり来た気がする。
　この前のABCのやつ(abc277_g)も、DP遷移のロジックとしてはだいたいこれと同じだと思う。
　DP定義、遷移についてはソース内コメントも参照。
・一応注意点というか、これは題意から遷移時に割らなくていい問い方になってるので、
　将来的にこれを参考に類題をやる時はそこで混乱しないように気をつける。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(K);
    cin >> A;

    ModTools<mint> mt(max(N, K));
    mint dp[K+1][N+1] = {};
    // dp[i][j] := i日目まで見て、注目するクッキーをj人決めた時の、期待値にかかる重みのようなもの
    dp[0][0] = 1;
    rep(i, K) {
        rep(j, N+1) {
            // 注目するクッキーをk人に渡す遷移
            rep(k, A[i]+1) {
                if (j+k > N) break;
                // 残る注目するクッキーN-j個からk個選ぶ * それ以外のN-k人から渡すA[i]-k人選ぶ
                dp[i+1][j+k] += dp[i][j] * mt.nCr(N-j, k) * mt.nCr(N-k, A[i]-k);
            }
        }
    }
    mint ans = dp[K][N];
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

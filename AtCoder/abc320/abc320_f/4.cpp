/*
・気まぐれ埋め
・一応ほぼ自力AC？でもTLで流れてた本質の方針ちょっと覚えてたから…。
・往復するDP
・帰りの状態も行きと一緒に動かす。こうすることで、
　同じ町での給油が往復どちらかしかできないことを解決できる。
　なんだけど、帰りの遷移で何が正しいのか考えるのが大変。
　色々ガチャガチャやって、これ確かやって無理だったっけーって投げたやつが通った…。
　帰りの遷移で h2 + dist - F[i + 1] ってやつが0下回る時も0で止めればOKなのが
　なんか非自明に感じでしまって。なんかそれOKにしたらその右の遷移で0突き抜けたことになんない？って。
　でも今出来上がったやつ見てよく考えると、そんなことなさそう。
　この辺のふわっとしたやつをはっきりクリアに読み取るにはどうしたらいいんだろうな。
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
    ll N, H;
    cin >> N >> H;
    vector<ll> X(N);
    cin >> X;
    vector<ll> P(N), F(N);
    rep(i, 1, N) {
        cin >> P[i] >> F[i];
    }
    X.insert(X.begin(), 0);
    P.eb(0);
    F.eb(0);

    auto dp = listnd(N + 1, H + 1, H + 1, INF);
    rep(h2, H + 1) {
        dp[0][H][h2] = 0;
    }
    rep(i, N) {
        ll dist = X[i + 1] - X[i];
        rep(h1, H + 1) {
            rep(h2, H + 1) {
                if (h1 - dist >= 0 and h2 + dist <= H) {
                    // 給油しない
                    chmin(dp[i + 1][h1 - dist][h2 + dist], dp[i][h1][h2]);
                    // 行きに給油する
                    chmin(dp[i + 1][min(h1 - dist + F[i + 1], H)][h2 + dist], dp[i][h1][h2] + P[i + 1]);
                    // 帰りに給油する　
                    chmin(dp[i + 1][h1 - dist][max(h2 + dist - F[i + 1], 0LL)], dp[i][h1][h2] + P[i + 1]);
                }
            }
        }
    }
    ll ans = INF;
    rep(h1, H + 1) {
        rep(h2, h1 + 1) {
            chmin(ans, dp[N][h1][h2]);
        }
    }
    if (ans >= INF) ans = -1;
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

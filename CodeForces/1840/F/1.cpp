/*
・Div.3残埋め
・自力ならず。。案外いいとこまで行ってた…。
・グリッドDP、メモリ削減
・経過時間tは大きく設定されているが、実際に到達できる場合に費やす時間はそこまで長くなさそう。
　だいたいH+W程度だとして、これを以降Nとする。
　このNとグリッドのH*Wを両方添字で持っても1憶で何とかなるかも。
　って感じの判断で進めるもMLE。憶超えはMLが256Mだとboolでも持てないっぽい…。
　DP配列はメモリ削減テクで減らすとして、いつどこにビームが打たれてるかの配列も、
　そのまま持つと結局N*max(H,W)なので億超えする。
　しかしビームの最大回数が100なので、実際必要なtは多くない。これはmapに詰めた。
　MLEは何とかなったが、WAが出てしまう。Nを2～4倍程度まで大きくするも、変化なし。
　ここで自力はギブアップした。
・さて、何が足りなかったかと言うと、最大経過時間Nの見積もりで、
　ビームの回数Rを考慮してなかった。これだと、グリッドがめちゃ小さくて、
　ビームが100本フルで打たれる時に、グリッドの広さ分しか待てなくてWAになってしまう。
　単純にH+W+Rとすれば良かった。(実際には到達判定を遷移前部分でやってるので、さらに+1してある)
　結局ここを直すだけで自力で書いてたやつからACが出せたので悔しい…。
・TLを確認するとこれは想定ではないっぽくて、
　ビーム間は最短経路で出して、打たれる所だけちゃんとチェック、みたいにしてる模様。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
    ll H, W;
    cin >> H >> W;
    ll R;
    cin >> R;
    ll N = H + W + R + 1;
    map<int, vector<int>> hs, vs;
    rep(i, R) {
        ll t, d, p;
        cin >> t >> d >> p;
        if (t > N) continue;
        if (d == 1) {
            if (not hs.count(t)) {
                hs[t].assign(H + 1, 0);
            }
            hs[t][p] = 1;
        } else {
            if (not vs.count(t)) {
                vs[t].assign(W + 1, 0);
            }
            vs[t][p] = 1;
        }
    }

    auto dp = listnd(2, H + 1, W + 1, false);
    dp[0][0][0] = true;
    ll ans = INF;
    rep(t, N) {
        bool hashs = hs.count(t + 1);
        bool hasvs = vs.count(t + 1);
        rep(h, H + 1) {
            rep(w, W + 1) {
                if (not dp[t % 2][h][w]) continue;
                if ((not hashs or not hs[t + 1][h]) and (not hasvs or not vs[t + 1][w])) {
                    dp[(t + 1) % 2][h][w] = true;
                }
                if (h + 1 <= H and (not hashs or not hs[t + 1][h + 1]) and (not hasvs or not vs[t + 1][w])) {
                    dp[(t + 1) % 2][h + 1][w] = true;
                }
                if (w + 1 <= W and (not hashs or not hs[t + 1][h]) and (not hasvs or not vs[t + 1][w + 1])) {
                    dp[(t + 1) % 2][h][w + 1] = true;
                }
                if (h == H and w == W) {
                    chmin(ans, t);
                }
                dp[t % 2][h][w] = false;
            }
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
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}

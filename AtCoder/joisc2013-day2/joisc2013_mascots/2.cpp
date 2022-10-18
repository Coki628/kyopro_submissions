/*
参考：https://www.ioi-jp.org/camp/2013/2013-sp-tasks/2013-sp-day2-mascots-review.pdf
・JOI埋め
・自力ならず。悔しい。
・nCr数え上げ、グリッドDP
・最初に作られる長方形は一意で、そのうち埋まってないマスを埋める順序の通り数がDPの初期値になる。
　ここから上下左右に長方形を広げていくようにDPを進める。
　遷移の際にはその埋める行(列)のマスの数だけ順序があるので階乗が掛かる。
　ここまではできたんだけど、上下(左右)をまとめる方法が詰め切れなかった。
・上下から上を取る通り数でnCr(上下の回数, 上の回数)ってのは考えたんだけど、
　最後にまとめて1回やるだけでいいとは思わなかった。
　DP遷移の中で考慮して何か掛けないといけないと思ったんだけど、
　この計算、外側に出していいんだな…。全体に掛かると思えばそれも考えたと思うんだけど、
　上下の遷移と左右の遷移で別だから、混ぜちゃいけない気がしたんだよなぁ。。
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
    ll H, W, N;
    cin >> H >> W >> N;
    ll mnh = INF, mxh = -INF, mnw = INF, mxw = -INF;
    rep(i, N) {
        ll h, w;
        cin >> h >> w;
        h--; w--;
        chmin(mnh, h);
        chmax(mxh, h);
        chmin(mnw, w);
        chmax(mxw, w);
    }

    ModTools<mint> mt(H*W);
    ll hlen = mxh - mnh + 1;
    ll wlen = mxw - mnw + 1;
    ll hrest = H - hlen;
    ll wrest = W - wlen;
    auto dp = list2d(hrest+1, wrest+1, (mint)0);
    dp[0][0] = mt.fact(hlen*wlen-N);
    rep(h, hrest+1) {
        rep(w, wrest+1) {
            if (h < hrest) {
                dp[h+1][w] += dp[h][w] * mt.fact(W-(wrest-w));
            }
            if (w < wrest) {
                dp[h][w+1] += dp[h][w] * mt.fact(H-(hrest-h));
            }
        }
    }
    mint ans = dp[hrest][wrest] * mt.nCr(hrest, mnh) * mt.nCr(wrest, mnw);
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

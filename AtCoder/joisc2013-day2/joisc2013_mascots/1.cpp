/*
・JOI埋め
・これは部分点解法。とりあえず考察の大筋が外れてないことを確認。
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
    ll hl = mnh;
    ll hr = H - mxh - 1;
    ll wl = mnw;
    ll wr = W - mxw - 1;
    auto dp = list4d(hl+1, hr+1, wl+1, wr+1, (mint)0);
    dp[0][0][0][0] = mt.fact(hlen*wlen-N);
    rep(h1, hl+1) {
        rep(h2, hr+1) {
            rep(w1, wl+1) {
                rep(w2, wr+1) {
                    if (h1+1 <= hl) {
                        dp[h1+1][h2][w1][w2] += dp[h1][h2][w1][w2]*mt.fact(W-(wl-w1)-(wr-w2));
                    }
                    if (h2+1 <= hr) {
                        dp[h1][h2+1][w1][w2] += dp[h1][h2][w1][w2]*mt.fact(W-(wl-w1)-(wr-w2));
                    }
                    if (w1+1 <= wl) {
                        dp[h1][h2][w1+1][w2] += dp[h1][h2][w1][w2]*mt.fact(H-(hl-h1)-(hr-h2));
                    }
                    if (w2+1 <= wr) {
                        dp[h1][h2][w1][w2+1] += dp[h1][h2][w1][w2]*mt.fact(H-(hl-h1)-(hr-h2));
                    }
                }
            }
        }
    }
    mint ans = dp[hl][hr][wl][wr];
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

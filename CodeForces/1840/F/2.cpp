/*
・最初の方で書いてたやつ。Nの大きさだけいじったら通った…。
　億超え配列は無理かと思ったけど、1憶が1つで約100MBだったので、
　boolなら合計2億くらいまでは256MB制約でもいけるのかも。
　ちなみに速度はmap使ってない割には大差なかった。
　実際1万のうちmapが踏むのは100個程度だから影響が小さいのかもしれん。
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
    bool hs[N + 1][H + 1] = {};
    bool vs[N + 1][W + 1] = {};
    rep(i, R) {
        ll t, d, p;
        cin >> t >> d >> p;
        if (t > N) continue;
        if (d == 1) {
            hs[t][p] = 1;
        } else {
            vs[t][p] = 1;
        }
    }

    auto dp = listnd(2, H + 1, W + 1, false);
    dp[0][0][0] = true;
    ll ans = INF;
    rep(t, N) {
        rep(h, H + 1) {
            rep(w, W + 1) {
                if (not dp[t % 2][h][w]) continue;
                if (not hs[t + 1][h] and not vs[t + 1][w]) {
                    dp[(t + 1) % 2][h][w] = true;
                }
                if (h + 1 <= H and not hs[t + 1][h + 1] and not vs[t + 1][w]) {
                    dp[(t + 1) % 2][h + 1][w] = true;
                }
                if (w + 1 <= W and not hs[t + 1][h] and not vs[t + 1][w + 1]) {
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

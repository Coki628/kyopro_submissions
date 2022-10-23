/*
・きっちり自力AC！
・bitDP、TSP
・枝葉ついてるけどようはTSPする。
　持ってるブーストの数とかはNビット目以降で立ってる本数、とかで都度確認できる。
・制約2秒だし想定解っぽい割に0.56秒で結構遅かった。
　ので、少し考えて、ldをdoubleにしたらやっぱり結構速くなってAC0.26秒。
　2冪の前計算も試しにやってみたけど変化なし。
　考えてみたら2^5くらいしかやらないから、log(5)削ってもそれは変化ないね。。
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

#include "geometry/Point.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<Point<double>> P;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        P.eb(x, y);
    }
    rep(i, M) {
        ll p, q;
        cin >> p >> q;
        P.eb(p, q);
    }

    ll L = N + M;
    auto dp = listnd(L, 1<<L, (double)INF);
    rep(i, L) {
        double cost = P[i].abs({0, 0});
        dp[i][1<<i] = cost;
    }
    double ans = INF;
    rep(bit, 1<<L) {
        rep(i, L) {
            if (dp[i][bit] == INF) continue;
            if (!(bit>>i & 1)) continue;
            Point<double> cur = P[i];
            ll city = 0, boost = 0;
            rep(j, N) {
                if (bit>>j & 1) {
                    city++;
                }
            }
            rep(j, N, L) {
                if (bit>>j & 1) {
                    boost++;
                }
            }
            if (city == N) {
                chmin(ans, dp[i][bit]+cur.abs({0, 0})/pow(2, boost));
            }
            rep(j, L) {
                if (bit>>j & 1) continue;
                chmin(dp[j][bit|1<<j], dp[i][bit]+cur.abs(P[j])/pow(2, boost));
            }
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

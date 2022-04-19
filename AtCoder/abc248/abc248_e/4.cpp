/*
参考：https://atcoder.jp/contests/abc248/submissions/31024769
・これはうにさんのを参考に。こっちのが直感的と言うか、思いつきやすいかも。
・幾何、誤差対策、有理数
・さて、自力実装のやつはTLEするので、N^3を落としてN^2でやりきるようにする。
　直線毎に、その直線に使われた要素i,jを集合として陽に持っておく。
　かなり愚直っぽい持ち方だけど、Nが小さいので問題ない。
　これで全部済んだ後、直線毎に集合の要素数をチェックしてK以上か見ればOK。
・ちなみに2乗の方針にしたらllでもWAにならなくなったので、int128から戻しておいた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

#include "geometry/Point.hpp"
#include "geometry/get_a_and_b.hpp"
#include "numbers/Fraction.hpp"
using fraction = Fraction<ll>;

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<Point<fraction>> XY;
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
        XY.pb({x, y});
    }

    if (K == 1) {
        print("Infinity");
        return;
    }

    map<pair<fraction, fraction>, set<ll>> AB;
    map<fraction, ll> zeros;
    rep(i, N) {
        // a == INFな直線は別処理
        zeros[XY[i].x]++;
        rep(j, i+1, N) {
            if (XY[i].x == XY[j].x) {
                continue;
            }
            auto ab = get_a_and_b(XY[i], XY[j]);
            AB[ab].insert(i);
            AB[ab].insert(j);
        }
    }

    ll ans = 0;
    for (auto& [ab, se] : AB) {
        ll cnt = se.size();
        if (cnt >= K) {
            ans++;
        }
    }
    for (auto& [y, cnt] : zeros) {
        if (cnt >= K) {
            ans++;
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

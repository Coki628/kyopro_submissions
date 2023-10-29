/*
・焼きなまし
・なかなか答え合わなくて大変だった。おかげで自分の焼きなましコードのバグ修正ができた。
　やるかどうか判定をrand_range(0, 100)で見てたのがダメで、
　これを実数でもっと細かい刻みで見るようにしたらうまくいった。
・つまり今までやってた焼きなまし多分全部出来損ないだったな。
　道理でいつも山登りよりスコア良くならないと思ったよ…。
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

#include "geometry/Point.hpp"
#include "common/Timer.hpp"
#include "common/randrange.hpp"

const int TL = 800;
// 開始温度：一回の遷移で動きうるスコア幅の最大値程度
const ld T0 = 30;
// 終了温度：一回の遷移で動きうるスコア幅の最小値程度
const ld T1 = 2;

// 焼きなましに使う温度の計算
ld calc_temp(int elapsed) {
    ld t = elapsed / (ld)TL;
    assert(t < 1);
    return T0 + (T1 - T0) * t;
    // return pow(T0, (1 - t)) * pow(T1, t);
}

// 焼きなましを踏まえた採用確率の計算
ld calc_prob(ld diff, ld temp) {
    if (diff > 0) {
        return 1;
    }
    return exp(diff / temp);
}

// 0~1の一様ランダムな実数を返す
double rand_double() {
  return 1.0 * rand() / RAND_MAX;
}

void solve() {
    Timer timer;
    ll N;
    cin >> N;
    vector<Point<ld>> P(N);
    rep(i, N) {
        cin >> P[i].x >> P[i].y;
    }

    vector<ll> ans = {0}, visited(N);
    ll cur = 0;
    ld sm = 0;
    visited[0] = 1;
    rep(_, N - 1) {
        ll nxt = -1;
        ld mn = INF;
        rep(i, N) {
            if (visited[i]) continue;
            if (chmin(mn, P[cur].abs(P[i]))) {
                nxt = i;
            }
        }
        visited[nxt] = 1;
        ans.eb(nxt);
        cur = nxt;
        sm += mn;
    }
    ans.eb(0);
    sm += P[cur].abs(P[0]);
    ld curscore = sm;

    debug(sm);
    debug(curscore);

    auto calc = [&](vector<ll> &ans) {
        ld sm = 0;
        ll n = ans.size();
        rep(i, n - 1) {
            sm += P[ans[i]].abs(P[ans[i + 1]]);
        }
        return sm;
    };
    ll opcnt = 0, okcnt = 0;
    auto elapsed = timer.get_elapse();
    while (elapsed < TL) {
        // 温度
        ld temp = calc_temp(elapsed);
        ll l = randrange(1, N);
        ll r = randrange(2, N + 1);
        if (l > r) swap(l, r);
        reverse(ans.begin() + l, ans.begin() + r);
        auto nxscore = calc(ans);
        // 確率(0~1)
        ld prob = calc_prob(curscore - nxscore, temp);
        if (rand_double() < prob) {
            curscore = nxscore;
            okcnt++;
        } else {
            reverse(ans.begin() + l, ans.begin() + r);
        }
        opcnt++;
        elapsed = timer.get_elapse();
    }
    debug(curscore);
    debug(opcnt);
    debug(okcnt);
    ans++;
    print(ans, '\n');
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

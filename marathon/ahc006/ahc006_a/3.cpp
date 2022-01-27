/*
参考：https://www.terry-u16.net/entry/ahc006-for-beginners
・なんか良い方針が生えず、最初から解説見ちゃった…。
・貪欲
・近い方から取る。それだけ。現在位置からの距離を毎回N箇所全部と取っても、
　Nが1000で回数が50回くらいなので全然問題ない。
・距離が遠すぎる場所を予め候補から外しておく。
・レストランと配達先をまとめて処理する。
・ここで124万点くらい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"

#include "common/input.hpp"
#include "common/print.hpp"
#include "common/randrange.hpp"
#include "common/Timer.hpp"
#include "string/zfill.hpp"

#include "common/sum.hpp"
#include "common/listnd.hpp"
#include "geometry/Point.hpp"

ld calc(ll t) {
    return round(1e8/(1000+t));
}

const ll DIST_MAX = 600;

void solve(int testcase=-1) {
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/"+zfill(tostr(testcase), 4)+".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/"+zfill(tostr(testcase), 4)+".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print(-1);
            return;
        }
    #endif

    const int N = 1000;
    const int K = 50;
    Point<ll> s = {400, 400};
    vector<Point<ll>> AB(N), CD(N);
    rep(i, N) {
        cin >> AB[i].x >> AB[i].y >> CD[i].x >> CD[i].y;
    }

    auto cur = s;
    ll t = 0;
    vector<ll> route;
    vector<ll> xy = {s.x, s.y};
    vector<int> removed(N);

    // 閾値より大きい距離の注文を予め省いておく
    rep(i, N) {
        if (s.manhattan(AB[i])+s.manhattan(CD[i]) > DIST_MAX) {
            removed[i] = true;
        }
    }
    #ifdef __LOCAL
        debug(N-sum(removed));
    #endif

    // レストランと配達先をまとめて処理する
    auto used = list2d(2, N, false);
    ll abcnt = 0, cdcnt = 0;
    while (abcnt < K or cdcnt < K) {
        vector<array<ll, 3>> cands;
        rep(i, N) {
            if (removed[i]) continue;
            if (not used[0][i] and abcnt < K) {
                ll dist = cur.manhattan(AB[i]);
                cands.pb({dist, 0, i});
            }
            if (used[0][i] and not used[1][i]) {
                ll dist = cur.manhattan(CD[i]);
                cands.pb({dist, 1, i});
            }
        }
        sort(ALL(cands));
        auto [d, p, j] = cands[0];
        cur = p ? CD[j] : AB[j];
        if (p) {
            cdcnt++;
        } else {
            abcnt++;
            route.eb(j+1);
        }
        xy.eb(cur.x);
        xy.eb(cur.y);
        t += d;
        used[p][j] = true;
    }
    t += cur.manhattan(s);
    xy.eb(s.x);
    xy.eb(s.y);

    #ifdef __LOCAL
        debug(t);
        debug(calc(t));
    #endif
    cout << route.size() << ' ';
    print(route);
    cout << xy.size()/2 << ' ';
    print(xy);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        vector<ll> T = {
            0,
        };
        for (ll t : T) {
            solve(t);
        }
    #else
        solve();
    #endif

    return 0;
}

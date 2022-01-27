/*
参考：https://www.terry-u16.net/entry/ahc006-for-beginners
・なんか良い方針が生えず、最初から解説見ちゃった…。
・貪欲、最近傍法
・近い方から取る。それだけ。現在位置からの距離を毎回N箇所全部と取っても、
　Nが1000で回数が50回くらいなので全然問題ない。
・ここで112万点くらい。
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

ld calc(ll t) {
    return round(1e8/(1000+t));
}

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
    const ll sx = 400, sy = 400;
    vector<ll> A(N), B(N), C(N), D(N);
    rep(i, N) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }

    ll cx = sx, cy = sy;
    ll t = 0;
    vector<ll> route;
    vector<ll> xy = {cx, cy};
    vector<bool> used(N);
    rep(_, K) {
        vector<pll> cands;
        rep(i, N) {
            if (used[i]) continue;
            ll dist = abs(cx-A[i])+abs(cy-B[i]);
            cands.eb(dist, i);
        }
        sort(ALL(cands));
        ll j = cands[0].second;
        cx = A[j], cy = B[j];
        route.eb(j+1);
        xy.eb(cx);
        xy.eb(cy);
        t += cands[0].first;
        used[j] = true;
    }

    used.assign(N, false);
    rep(_, K) {
        vector<pll> cands;
        for (auto i : route) {
            i--;
            if (used[i]) continue;
            ll dist = abs(cx-C[i])+abs(cy-D[i]);
            cands.eb(dist, i);
        }
        sort(ALL(cands));
        ll j = cands[0].second;
        cx = C[j], cy = D[j];
        xy.eb(cx);
        xy.eb(cy);
        t += cands[0].first;
        used[j] = true;
    }
    t += abs(cx-sy)+abs(cy-sy);
    xy.eb(sx);
    xy.eb(sy);

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

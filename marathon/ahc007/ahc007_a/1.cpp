/*
・これは自力の方針。
・最初、それぞれの辺のコストを最大の3dで見積もっておいて、
　実際の値が分かったら更新して、毎回MSTを作る。
　必要な辺に今追加するやつが含まれてしまったら要る、そうでなければ要らない。
・これで68億くらい。
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
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"

#include "common/sorted.hpp"
#include "geometry/Point.hpp"
#include "graph/UnionFind.hpp"

ll dist(Point<ld> p1, Point<ld> p2) {
    return round(p1.abs(p2));
}

ld calc(ll a, ll b) {
    return round(1e8*b/a);
}

ld solve(int testcase=-1) {
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/"+zfill(tostr(testcase), 4)+".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/"+zfill(tostr(testcase), 4)+".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print(-1);
            exit(0);
        }
    #endif

    const int N = 400, M = 1995;
    vector<Point<ld>> points(N);
    rep(i, N) {
        cin >> points[i].x >> points[i].y;
    }
    vector<pll> edges;
    vector<ll> U(M), V(M);
    rep(i, M) {
        cin >> U[i] >> V[i];

        ll d = dist(points[U[i]], points[V[i]]);
        edges.pb({d*3, i});
    }

    vector<bool> need(M);
    ll a = 0;
    rep(i, M) {
        ll l;
        cin >> l;
        edges[i].first = l;
        auto cur = sorted(edges);
        UnionFind uf(N);
        for (auto [d, j] : cur) {
            if (not uf.same(U[j], V[j])) {
                uf.merge(U[j], V[j]);
                if (j == i) {
                    need[i] = true;
                    a += l;
                    break;
                }
            }
        }
        #ifdef __LOCAL
            ofs << (int)need[i] << endl;
        #else
            cout << (int)need[i] << endl;
        #endif
    }

    sort(ALL(edges));
    UnionFind uf(N);
    ll b = 0;
    for (auto [d, i] : edges) {
        if (not uf.same(U[i], V[i])) {
            uf.merge(U[i], V[i]);
            b += d;
        }
    }
    #ifdef __LOCAL
        debug(a);
        debug(b);
    #endif
    ld score = calc(a, b);
    return score;
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
        // 100件実施
        // vector<ll> T;
        // rep(i, 100) {
        //     T.eb(i);
        // }
        ld score = 0;
        for (ll t : T) {
            score += solve(t);
        }
        debug(score);
    #else
        solve();
    #endif

    return 0;
}

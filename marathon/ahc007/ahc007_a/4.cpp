/*
参考：https://www.terry-u16.net/entry/ahc007-explanation
・ここからterryさんの記事を参考に改善を進めていく。
・モンテカルロ法
・とりあえず下準備としての高速化。連結とか毎回最初から全部やってたので、
　そこまでの結果は持っておいてそれより先だけやるようにした。
　結構変わって、0.30秒→0.13秒。
・実際にモンテカルロ法を導入。やり方はterryさんが丁寧に書いてくれてる。
　ざっくり言うと、条件に合った辺集合をランダムなコストでS個作っておいて、
　辺追加の際に毎回そのSセットを使って、
　その辺を使った場合と使わなかった場合の最終結果を比較する。
　このSが大きいほど、結果が理論的な期待値に近づくので効果が上がる。
・Sは12回しか回せていないが、これでも141億点くらい出てる。
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

const int N = 400, M = 1995;
const int S = 12;
vector<ll> U(M), V(M);

ll dist(Point<ld> p1, Point<ld> p2) {
    return round(p1.abs(p2));
}

ld calc(ll a, ll b) {
    return round(1e8*b/a);
}

// 辺iを使った方がこの先で得(低コスト)かどうか
bool check(const vvpll& randedges, const UnionFind& uf, ll i, ll l) {
    // Sセットのランダム辺を切り出しとソートするcrandedges
    vvpll crandedges(S);
    ll c1 = 0, c2 = 0;
    rep(j, S) {
        // 今見ている次の辺以降を切り出す
        crandedges[j] = vector<pll>(randedges[j].begin()+i+1, randedges[j].end());
        sort(ALL(crandedges[j]));
        // 辺iを使う
        auto cuf = uf;
        cuf.merge(U[i], V[i]);
        // 今回の辺のコスト
        c1 += l;
        for (auto [d, k] : crandedges[j]) {
            if (not cuf.same(U[k], V[k])) {
                cuf.merge(U[k], V[k]);
                c1 += d;
                if (cuf.size() == 1) break;
            }
        }
        // 辺iを使わない
        cuf = uf;
        for (auto [d, k] : crandedges[j]) {
            if (not cuf.same(U[k], V[k])) {
                cuf.merge(U[k], V[k]);
                c2 += d;
                if (cuf.size() == 1) break;
            }
        }
        // 連結になっていなかったら即NG(絶対使う)判定
        if (cuf.size() > 1) {
            return true;
        }
    }
    // 辺iを使う方が得かどうか
    return c1 <= c2;
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

    vector<Point<ld>> points(N);
    rep(i, N) {
        cin >> points[i].x >> points[i].y;
    }
    vector<pll> edges;
    rep(i, M) {
        cin >> U[i] >> V[i];

        ll d = dist(points[U[i]], points[V[i]]);
        edges.pb({d*3, i});
    }

    // ランダムにコストを振ったM辺のセットをS個作成
    vvpll randedges(S);
    rep(i, S) {
        rep(j, M) {
            ll d = dist(points[U[j]], points[V[j]]);
            randedges[i].pb({randrange(d, d*3+1), j});
        }
    }

    vector<bool> need(M);
    UnionFind uf(N);
    ll a = 0;
    rep(i, M) {
        ll l;
        cin >> l;
        edges[i].first = l;
        if (not uf.same(U[i], V[i])) {
            if (check(randedges, uf, i, l)) {
                uf.merge(U[i], V[i]);
                need[i] = true;
                a += l;
            }
        }
        #ifdef __LOCAL
            ofs << (int)need[i] << endl;
        #else
            cout << (int)need[i] << endl;
        #endif
    }

    #ifdef __LOCAL
        sort(ALL(edges));
        uf = UnionFind(N);
        ll b = 0;
        for (auto [d, i] : edges) {
            if (not uf.same(U[i], V[i])) {
                uf.merge(U[i], V[i]);
                b += d;
            }
        }
        debug(a);
        debug(b);
        ld score = calc(a, b);
        return score;
    #else
        return 0;
    #endif
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

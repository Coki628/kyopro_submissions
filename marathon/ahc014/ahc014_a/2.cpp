/*
・ちょっと改修。2点選べばもう2点は定まるので、3点ではなく2点から求めるように。
　投げたら2834万点。ちょっと下がってるし。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
#include "common/listnd.hpp"
#include "common/chmin.hpp"
#include "common/chmax.hpp"
#include "common/randrange.hpp"
#include "common/Timer.hpp"
#include "grid/constants/dir8.hpp"
#include "string/zfill.hpp"

#include "geometry/Point.hpp"

ld solve(int testcase=-1) {
    Timer timer;
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/" + zfill(tostr(testcase), 4) + ".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/" + zfill(tostr(testcase), 4) + ".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print("error, please check if 'tools/out/' dir exists");
            exit(0);
        }
    #endif

    int N, M;
    cin >> N >> M;
    // int usedv[N][N] = {};
    // int usede[8][N][N] = {};
    auto usedv = listnd(N, N, 0);
    auto usede = listnd(8, N, N, 0);
    vector<Point<int>> P;
    rep(i, M) {
        int x, y;
        cin >> x >> y;
        P.eb(x, y);
        usedv[x][y] = 1;
    }
    const int TL = 4800;
    Point<int> NG = {-1, -1};
    Point<int> center = {(N-1)/2, (N-1)/2};
    auto get_cost = [&](Point<int> p) -> int {
        return (p.x-center.x)*(p.x-center.x) + (p.y-center.y)*(p.y-center.y) + 1;
    };
    ll S = 0;
    rep(x, N) {
        rep(y, N) {
            S += get_cost({x, y});
        }
    }

    auto calc = [&]() -> ld {
        ll sm = 0;
        for (auto& p : P) {
            sm += get_cost(p);
        }
        return round(1000000LL*N*N/(ld)M*sm/(ld)S);
    };
    // p1からp2へ向かう方向
    auto check_dir = [&](Point<int> p1, Point<int> p2) -> int {
        if (p1.x == p2.x) {
            if (p1.y < p2.y) {
                return 3;
            } elif (p1.y > p2.y) {
                return 2;
            }
        } elif (p1.y == p2.y) {
            if (p1.x < p2.x) {
                return 1;
            } elif (p1.x > p2.x) {
                return 0;
            }
        }
        // 45度回転
        Point<int> uv1 = {p1.x-p1.y, p1.x+p1.y};
        Point<int> uv2 = {p2.x-p2.y, p2.x+p2.y};
        if (uv1.x == uv2.x) {
            if (uv1.y < uv2.y) {
                return 7;
            } elif (uv1.y > uv2.y) {
                return 6;
            }
        } elif (uv1.y == uv2.y) {
            if (uv1.x < uv2.x) {
                return 5;
            } elif (uv1.x > uv2.x) {
                return 4;
            }
        }
        assert(0);
    };
    auto find_p1 = [&](
        Point<int> p2,
        Point<int> p4
    ) -> pair<Point<int>, Point<int>> {
        Point<int> p1 = NG, p3 = NG, uv1 = NG, uv3 = NG;
        // 45度回転
        Point<int> uv2 = {p2.x-p2.y, p2.x+p2.y};
        Point<int> uv4 = {p4.x-p4.y, p4.x+p4.y};

        p1 = {p2.x, p4.y};
        p3 = {p4.x, p2.y};
        uv1 = {uv2.x, uv4.y};
        uv3 = {uv4.x, uv2.y};
        bool ok = false;
        if (
            // 直線上はダメ
            p2.x != p4.x and
            p2.y != p4.y and
            // どちらか片方だけ埋まってればOK
            (usedv[p1.x][p1.y] ^ usedv[p3.x][p3.y])
        ) {
            if (usedv[p1.x][p1.y]) {
                swap(p1, p3);
            }
            ok = true;
        }
        // 目指す場所が整数座標かどうか
        if (not ok and (uv1.y+uv1.x)%2 == 0 and (uv3.y+uv3.x)%2 == 0) {
            // x = (v+u)/2, y = (v-u)/2
            p1 = {(uv1.y+uv1.x)/2, (uv1.y-uv1.x)/2};
            p3 = {(uv3.y+uv3.x)/2, (uv3.y-uv3.x)/2};
            if (
                // 欲しい位置がグリッド内
                p1.x >= 0 and p1.x < N and p1.y >= 0 and p1.y < N and
                p3.x >= 0 and p3.x < N and p3.y >= 0 and p3.y < N and
                uv2.x != uv4.x and
                uv2.y != uv4.y and
                (usedv[p1.x][p1.y] ^ usedv[p3.x][p3.y])
            ) {
                if (usedv[p1.x][p1.y]) {
                    swap(p1, p3);
                }
                ok = true;
            }
        }
        // 3点がいい位置になかった
        if (not ok) {
            return {NG, NG};
        }
        vector<Point<int>> tmp = {p1, p2, p3, p4};
        rep(i, 4) {
            auto cur = tmp[i];
            int d = check_dir(tmp[i], tmp[(i+1)%4]);
            int revd = d%2 == 0 ? d+1 : d-1;
            auto [dx, dy] = dir8[d];
            while (cur != tmp[(i+1)%4]) {
                if (usede[d][cur.x][cur.y]) {
                    return {NG, NG};
                }
                cur.x += dx, cur.y += dy;
                if (cur != tmp[(i+1)%4] and usedv[cur.x][cur.y]) {
                    return {NG, NG};
                }
            }
        }
        // p1からp4まで行ければOK
        return {p1, p3};
    };
    auto put = [&](array<Point<int>, 4> p) -> void {
        assert(!usedv[p[0].x][p[0].y]);
        usedv[p[0].x][p[0].y] = 1;
        rep(i, 4) {
            auto cur = p[i];
            int d = check_dir(p[i], p[(i+1)%4]);
            int revd = d%2 == 0 ? d+1 : d-1;
            auto [dx, dy] = dir8[d];
            while (cur != p[(i+1)%4]) {
                assert(!usede[d][cur.x][cur.y]);
                usede[d][cur.x][cur.y] = 1;
                cur.x += dx, cur.y += dy;
                assert(!usede[revd][cur.x][cur.y]);
                usede[revd][cur.x][cur.y] = 1;
                if (cur == p[(i+1)%4]) {
                    assert(usedv[cur.x][cur.y]);
                } else {
                    assert(!usedv[cur.x][cur.y]);
                }
            }
        }
    };

    auto elapsed = timer.get_elapse();
    int opcnt = 0;
    vector<array<pii, 4>> ans;
    while (1) {
        if (opcnt%10 == 0) {
            elapsed = timer.get_elapse();
            if (elapsed >= TL) break;
        }
        int n = P.size();
        int i = randrange(0, n);
        int j = randrange(0, n);
        while (i == j) {
            j = randrange(0, n);
        }
        opcnt++;
        auto [p1, p3] = find_p1(P[i], P[j]);
        if (p1 == NG) continue;
        put({p1, P[i], p3, P[j]});
        ans.pb({p1, P[i], p3, P[j]});
        P.eb(p1);
        #ifdef __LOCAL
            // print("updated");
            // debug(opcnt);
        #endif
    }

    #ifdef __LOCAL
        debug(opcnt);
        ofs << ans.size() << endl;
        for (auto& p : ans) {
            ofs << p << endl;
        }
    #else
        print(ans.size());
        print(ans, '\n');
    #endif

    ld score = calc();
    return score;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        // vector<ll> T = {
        //     0,
        // };

        // 0からn件実施
        int n = 10;
        vector<ll> T;
        rep(i, n) {
            T.eb(i);
        }

        ld totalscore = 0;
        for (ll t : T) {
            cout << "case #" << t << " start" << endl;
            ld score = solve(t);
            cout << "case #" << t << " ";
            debug(score);
            cout << endl;
            totalscore += score;
        }
        debug(totalscore);
    #else
        solve();
    #endif

    return 0;
}

/*
・14のビーム*乱択から、乱択を改良。適当にペア探すのではなく、
　全探索して候補をリストアップしてその中から乱択、とした。これで3874万点！
・候補から単純に乱択ではなく、ビームと同様の優先付けをして、
　タイブレークだけ乱択とした。これで3931万点！
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

auto solve(int testcase=-1) {
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

    const int MX = 61;
    int N, M;
    cin >> N >> M;
    // debug(M);
    // debug(N*N);
    // debug(M/((ld)N*N));
    // ld rate = M / ((ld)N*N);
    array<array<int, MX>, MX> usedv = {};
    array<array<array<int, MX>, MX>, 8> usede = {};
    vector<Point<int>> P;
    const int TL = 4800;
    const Point<int> NG = {-1, -1};
    const Point<int> center = {(N-1)/2, (N-1)/2};
    ll S = 0, sm = 0;
    auto get_cost = [&](Point<int> p) -> int {
        return (p.x-center.x)*(p.x-center.x) + (p.y-center.y)*(p.y-center.y) + 1;
    };
    auto calc = [&]() -> ll {
        return round(1000000LL*N*N/(ld)M*sm/(ld)S);
    };
    // XY -> UV変換
    auto xy_to_uv = [](Point<int> p) -> Point<int> {
        return {p.x-p.y, p.x+p.y};
    };
    // UV -> XY変換
    auto uv_to_xy = [&](Point<int> uv) -> Point<int> {
        // 目指す位置が整数座標でない
        if ((uv.y+uv.x)%2 != 0) {
            return NG;
        }
        // x = (v+u)/2, y = (v-u)/2
        return {(uv.y+uv.x)/2, (uv.y-uv.x)/2};
    };
    // 到達しうる範囲。試した感じ、制約と同じN/4を基準にすれば良さそう
    int mnu = MOD, mxu = -MOD, mnv = MOD, mxv = -MOD;
    for (auto [x, y] : vector<Point<int>>{{N/4, N/4}, {N/4, N-N/4}, {N-N/4, N/4}, {N-N/4, N-N/4}}) {
        auto uv = xy_to_uv({x, y});
        chmin(mnu, uv.x);
        chmax(mxu, uv.x);
        chmin(mnv, uv.y);
        chmax(mxv, uv.y);
    }
    rep(i, M) {
        int x, y;
        cin >> x >> y;
        P.eb(x, y);
        sm += get_cost(P.back());
        usedv[x][y] = 1;
    }
    rep(x, N) {
        rep(y, N) {
            S += get_cost({x, y});
        }
    }
    auto isvalid = listnd(N, N, 0);
    vector<Point<int>> valids;
    rep(x, N) {
        rep(y, N) {
            auto uv = xy_to_uv({x, y});
            if (
                mnu <= uv.x and uv.x <= mxu and
                mnv <= uv.y and uv.y <= mxv
            ) {
                isvalid[x][y] = 1;
                valids.eb(x, y);
            }
        }
    }
    #ifdef __LOCAL
        debug(N*N);
        debug(valids.size());
    #endif

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
        Point<int> uv1 = xy_to_uv(p1);
        Point<int> uv2 = xy_to_uv(p2);
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
    // 渡された長方形が置けるかチェック(追加点はP[0])
    auto check_rect = [&](const array<Point<int>, 4>& P) {
        rep(i, 4) {
            auto cur = P[i];
            int d = check_dir(P[i], P[(i+1)%4]);
            int revd = d%2 == 0 ? d+1 : d-1;
            auto [dx, dy] = dir8[d];
            while (cur != P[(i+1)%4]) {
                if (usede[d][cur.x][cur.y]) {
                    return false;
                }
                cur.x += dx, cur.y += dy;
                if (cur != P[(i+1)%4] and usedv[cur.x][cur.y]) {
                    return false;
                }
            }
        }
        return true;
    };
    auto find_p1p3 = [&](Point<int> p2, Point<int> p4) -> vector<pair<Point<int>, Point<int>>> {
        Point<int> p1 = NG, p3 = NG, uv1 = NG, uv3 = NG;
        // 45度回転
        Point<int> uv2 = xy_to_uv(p2);
        Point<int> uv4 = xy_to_uv(p4);

        p1 = {p2.x, p4.y};
        p3 = {p4.x, p2.y};
        uv1 = {uv2.x, uv4.y};
        uv3 = {uv4.x, uv2.y};
        vector<pair<Point<int>, Point<int>>> res;
        // まずはxy座標でチェック
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
            if (check_rect({p1, p2, p3, p4})) {
                res.eb(p1, p3);
            }
        }
        // uv座標でチェック
        p1 = uv_to_xy(uv1);
        p3 = uv_to_xy(uv3);
        if (
            p1 != NG and p3 != NG and
            // 欲しい位置がグリッド内
            p1.x >= 0 and p1.x < N and p1.y >= 0 and p1.y < N and
            p3.x >= 0 and p3.x < N and p3.y >= 0 and p3.y < N and
            // 直線上はダメ
            uv2.x != uv4.x and
            uv2.y != uv4.y and
            // 45度以外の傾きはNG
            (uv1.x == uv2.x or uv1.y == uv2.y) and
            (uv2.x == uv3.x or uv2.y == uv3.y) and
            (uv3.x == uv4.x or uv3.y == uv4.y) and
            (uv4.x == uv1.x or uv4.y == uv1.y) and
            (usedv[p1.x][p1.y] ^ usedv[p3.x][p3.y])
        ) {
            if (usedv[p1.x][p1.y]) {
                swap(p1, p3);
            }
            if (check_rect({p1, p2, p3, p4})) {
                res.eb(p1, p3);
            }
        }
        return res;
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
        sm += get_cost(p[0]);
    };
    auto rollback = [&](vector<array<Point<int>, 4>>& curans, int t=-1) -> vector<array<Point<int>, 4>> {
        // 第2引数なしで最初まで戻す
        if (t == -1) {
            t = curans.size();
        }
        vector<array<Point<int>, 4>> res;
        rep(_, t) {
            auto p = curans.back(); curans.pop_back();
            assert(usedv[p[0].x][p[0].y]);
            rep(i, 4) {
                auto cur = p[i];
                int d = check_dir(p[i], p[(i+1)%4]);
                int revd = d%2 == 0 ? d+1 : d-1;
                auto [dx, dy] = dir8[d];
                while (cur != p[(i+1)%4]) {
                    assert(usede[d][cur.x][cur.y]);
                    usede[d][cur.x][cur.y] = 0;
                    cur.x += dx, cur.y += dy;
                    assert(usede[revd][cur.x][cur.y]);
                    usede[revd][cur.x][cur.y] = 0;
                    if (cur == p[(i+1)%4]) {
                        assert(usedv[cur.x][cur.y]);
                    } else {
                        assert(!usedv[cur.x][cur.y]);
                    }
                }
            }
            usedv[p[0].x][p[0].y] = 0;
            P.pop_back();
            sm -= get_cost(p[0]);
            res.pb(p);
        }
        // 行った削除操作を返す
        reverse(ALL(res));
        return res;
    };
    auto get_canditates = [&]() {
        // 遷移の候補を全探索
        vector<array<Point<int>, 4>> candi;
        for (auto p2 : valids) {
            if (not usedv[p2.x][p2.y]) continue;
            // 8方向に一番近い頂点を見に行く
            rep(d, 8) {
                auto [dx, dy] = dir8[d];
                int cx = p2.x, cy = p2.y;
                // この方向には既に辺があるのでダメ
                if (usede[d][cx][cy]) {
                    continue;
                }
                Point<int> p3 = NG;
                while (cx+dx >= 0 and cx+dx < N and cy+dy >= 0 and cy+dy < N) {
                    cx += dx, cy += dy;
                    if (usedv[cx][cy]) {
                        p3 = {cx, cy};
                        break;
                    }
                    // これ以上外側は無理
                    if (not isvalid[cx][cy]) {
                        break;
                    }
                }
                if (p3 != NG) {
                    // if (d%4 < 2) {
                    //     d+2-(d%2);
                    //     d+3-(d%2);
                    // } else {
                    //     d-2-(d%2);
                    //     d-1-(d%2);
                    // }
                    int nxd[2] = {
                        d + (d%4 < 2 ? 2 : -2) - (d%2),
                        d + (d%4 < 2 ? 3 : -1) - (d%2)
                    };
                    rep(i, 2) {
                        auto [dx2, dy2] = dir8[nxd[i]];
                        int cx2 = p3.x, cy2 = p3.y;
                        // この方向には既に辺があるのでダメ
                        if (usede[nxd[i]][cx2][cy2]) {
                            continue;
                        }
                        Point<int> p4 = NG;
                        while (cx2+dx2 >= 0 and cx2+dx2 < N and cy2+dy2 >= 0 and cy2+dy2 < N) {
                            cx2 += dx2, cy2 += dy2;
                            if (usedv[cx2][cy2]) {
                                p4 = {cx2, cy2};
                                break;
                            }
                            // これ以上外側は無理
                            if (not isvalid[cx2][cy2]) {
                                break;
                            }
                        }
                        // p2,p4の順序を固定して回転方向の重複を省く
                        if (p4 != NG and p2.x <= p4.x) {
                            for (auto [p1, _p3] : find_p1p3(p2, p4)) {
                                candi.pb({p1, p2, _p3, p4});
                            }
                        }
                    }
                }
            }
        }
        UNIQUE(candi);
        return candi;
    };
    // ランダムな頂点(と辺)を0～1個追加(追加個数を返す)
    auto add_random = [&](vector<array<Point<int>, 4>>& curans) -> int {
        int n = P.size();
        int i = randrange(0, n);
        int j = randrange(0, n);
        while (i == j) {
            j = randrange(0, n);
        }
        auto candi = find_p1p3(P[i], P[j]);
        if (candi.empty()) {
            return 0;
        }
        auto& [p1, p3] = candi[randrange(0, candi.size())];
        put({p1, P[i], p3, P[j]});
        curans.pb({p1, P[i], p3, P[j]});
        P.eb(p1);
        return 1;
    };
    // 優先度の高い頂点を0～1個追加(追加個数を返す)
    auto add_greedy = [&](vector<array<Point<int>, 4>>& curans) -> int {
        auto candi = get_canditates();
        if (candi.empty()) {
            return 0;
        }
        vector<pair<int, array<Point<int>, 4>>> vec;
        rep(i, candi.size()) {
            auto& [p1, p2, p3, p4] = candi[i];
            // なるべく辺の短い操作を優先させる
            ll x = abs(p1.x-p3.x) + abs(p1.y-p3.y);
            vec.pb({x, {p1, p2, p3, p4}});
        }
        sort(ALL(vec));
        auto& [_, arr] = vec[0];
        auto& [p1, p2, p3, p4] = arr;
        put({p1, p2, p3, p4});
        curans.pb({p1, p2, p3, p4});
        P.eb(p1);
        return 1;
    };

    vector<array<Point<int>, 4>> ans;
    ll mxscore = calc();
    const int BEAM_WIDTH = 10;
    // state[-x, score, id]
    using state = tuple<ll, ll, int>;
    priority_queue<state, vector<state>> cur_beam;
    cur_beam.push({0, 0, 0});
    vector<vector<array<Point<int>, 4>>> curanses;
    curanses.pb({});
    while (1) {
        priority_queue<state, vector<state>> nxt_beam;
        vector<vector<array<Point<int>, 4>>> nxtanses;
        rep(_, BEAM_WIDTH) {
            if (cur_beam.empty()) break;
            auto [__, score, id] = cur_beam.top(); cur_beam.pop();
            // 状態作成
            for (auto& arr : curanses[id]) {
                put(arr);
                P.eb(arr[0]);
            }

            auto candi = get_canditates();
            for (auto& [p1, p2, p3, p4] : candi) {
                put({p1, p2, p3, p4});
                curanses[id].pb({p1, p2, p3, p4});
                // なるべく辺の短い操作を優先させる
                ll x = abs(p1.x-p3.x) + abs(p1.y-p3.y);
                P.eb(p1);
                ll nxscore = calc();
                if (chmax(mxscore, nxscore)) {
                    ans = curanses[id];
                }
                nxt_beam.push({-x, nxscore, nxtanses.size()});
                nxtanses.pb(curanses[id]);
                rollback(curanses[id], 1);
            }

            // 状態戻し
            rollback(curanses[id]);
        }
        if (nxt_beam.empty()) break;
        swap(cur_beam, nxt_beam);
        swap(curanses, nxtanses);
    }

    // 残り時間で乱択やる
    auto elapsed = timer.get_elapse();
    int opcnt = 0;
    vector<array<Point<int>, 4>> curans;
    while (elapsed < TL) {
        while (elapsed < TL) {
            auto candi = get_canditates();
            if (candi.empty()) break;
            vector<tuple<ll, ll, array<Point<int>, 4>>> tmp;
            rep(i, candi.size()) {
                auto& [p1, p2, p3, p4] = candi[i];
                // なるべく辺の短い操作を優先させる
                ll a = abs(p1.x-p3.x) + abs(p1.y-p3.y);
                // タイブレークは乱択
                ll b = randrange(0, 1000000000);
                tmp.pb({a, b, {p1, p2, p3, p4}});
            }
            sort(ALL(tmp));
            auto& [p1, p2, p3, p4] = get<2>(tmp[0]);
            // int i = randrange(0, candi.size());
            // auto& [p1, p2, p3, p4] = candi[i];
            put({p1, p2, p3, p4});
            curans.pb({p1, p2, p3, p4});
            P.eb(p1);
            elapsed = timer.get_elapse();
        }
        opcnt++;
        ll score = calc();
        if (chmax(mxscore, score)) {
            ans = curans;
        }
        rollback(curans);
        assert(P.size() == M);
        elapsed = timer.get_elapse();
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

    return mxscore;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        vector<int> T = {
            0,
        };

        // sからn件実施
        // int s = 0;
        // int n = 20;
        // vector<int> T;
        // rep(i, s, s+n) {
        //     T.eb(i);
        // }

        ll totalscore = 0;
        for (int t : T) {
            cout << "case #" << t << " start" << endl;
            auto score = solve(t);
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

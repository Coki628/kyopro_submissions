/*
・場合分け、乱択
・全部乱択で条件色々作った。盤面によって効果的な条件とそうでないのがあるようなので。
　結構ブレはあるっぽいけど、最大で4008万点。40M乗った！
・get_canditatesの高速化をやった。予めその方向で次に来る頂点を前計算しておいて、
　最深部でのwhileループを回さないようにした。試行回数が2～3倍くらい増えた。
　あと密度による相性で明らかに望み薄なパターンを避けたりした。これで最大4106万点！
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

array<int, 10> C;
vector<ld> mxdens(10, -INF), mndens(10, INF);

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

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    const int MX = 61;
    int N, M;
    cin >> N >> M;
    // debug(M);
    // debug(N*N);
    // debug(M/((ld)N*N));
    ld dens = M / ((ld)N*N);
    array<array<int, MX>, MX> usedv = {};
    array<array<array<int, MX>, MX>, 8> usede = {};
    // nxtv[d][x][y] := 位置(x,y)から方向dへむかった時最初に頂点がある位置を返す(なければ(-1,-1))
    array<array<array<Point<int>, MX>, MX>, 8> nxtv = {};
    rep(d, 8) rep(x, MX) rep(y, MX) nxtv[d][x][y] = {-1, -1};
    vector<Point<int>> P;
    const int TL = 4800;
    const Point<int> NG = {-1, -1};
    const Point<int> center = {(N-1)/2, (N-1)/2};
    ll S = 0, sm = 0;
    ///////////////////////////////////////////////////////////////////////////////////////////////////

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
    auto valid = listnd(N, N, 0);
    rep(x, N) {
        rep(y, N) {
            S += get_cost({(int)x, (int)y});
            auto uv = xy_to_uv({(int)x, (int)y});
            if (
                mnu <= uv.x and uv.x <= mxu and
                mnv <= uv.y and uv.y <= mxv
            ) {
                valid[x][y] = 1;
            }
        }
    }
    auto update_nxtv = [&](const Point<int>& p) {
        rep(d, 8) {
            auto [dx, dy] = dir8[d];
            int revd = d%2 == 0 ? d+1 : d-1;
            int cx = p.x + dx, cy = p.y + dy;
            while (cx >= 0 and cx < N and cy >= 0 and cy < N and valid[cx][cy]) {
                nxtv[revd][cx][cy] = p;
                if (usedv[cx][cy]) break;
                cx += dx, cy += dy;
            }
        }
    };
    rep(i, M) {
        int x, y;
        cin >> x >> y;
        P.eb(x, y);
        sm += get_cost(P.back());
        usedv[x][y] = 1;
        update_nxtv(P.back());
    }
    #ifdef __LOCAL
        debug(N*N);
    #endif
    // p1からp2へ向かう方向
    auto check_dir = [&](const Point<int>& p1, const Point<int>& p2) -> int {
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
            // int revd = d%2 == 0 ? d+1 : d-1;
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
    auto find_p1p3 = [&](const Point<int>& p2, const Point<int>& p4) -> vector<pair<Point<int>, Point<int>>> {
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
    auto put = [&](const array<Point<int>, 4>& p) -> void {
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
        P.eb(p[0]);
        update_nxtv(p[0]);
    };
    auto remove_nxtv = [&](const Point<int>& p) {
        rep(d, 8) {
            auto [dx, dy] = dir8[d];
            int revd = d%2 == 0 ? d+1 : d-1;
            int cx = p.x + dx, cy = p.y + dy;
            while (cx >= 0 and cx < N and cy >= 0 and cy < N and valid[cx][cy]) {
                // 削除前はこのpを見てなきゃおかしい
                assert(nxtv[revd][cx][cy] == p);
                nxtv[revd][cx][cy] = nxtv[revd][p.x][p.y];
                if (usedv[cx][cy]) break;
                cx += dx, cy += dy;
            }
        }
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
            remove_nxtv(p[0]);
            res.pb(p);
        }
        // 行った削除操作を返す
        reverse(ALL(res));
        return res;
    };
    auto find_p1 = [&](const Point<int>& p2, const Point<int>& p3, const Point<int> p4) -> Point<int> {
        // 縦横
        if (check_dir(p2, p3) < 4) {
            if (p3.x == p4.x) {
                return {p2.x, p4.y};
            } else {
                return {p4.x, p2.y};
            }
        // 斜め
        } else {
            auto uv2 = xy_to_uv(p2);
            auto uv3 = xy_to_uv(p3);
            auto uv4 = xy_to_uv(p4);
            if (uv3.x == uv4.x) {
                return uv_to_xy({uv2.x, uv4.y});
            } else {
                return uv_to_xy({uv4.x, uv2.y});
            }
        }
    };
    auto get_canditates = [&]() {
        // 遷移の候補を全探索
        vector<array<Point<int>, 4>> candi;
        for (auto& p2 : P) {
            assert(usedv[p2.x][p2.y]);
            // 8方向に一番近い頂点を見に行く
            rep(d, 8) {
                int cx = p2.x, cy = p2.y;
                // この方向には既に辺があるのでダメ
                if (usede[d][cx][cy]) {
                    continue;
                }
                // p2 -> p3
                Point<int> p3 = nxtv[d][cx][cy];
                if (p3 != NG) {
                    int nxd[2] = {
                        (int)d + ((int)d%4 < 2 ? 2 : -2) - ((int)d%2),
                        (int)d + ((int)d%4 < 2 ? 3 : -1) - ((int)d%2)
                    };
                    rep(i, 2) {
                        int d2 = nxd[i];
                        int cx2 = p3.x, cy2 = p3.y;
                        // この方向には既に辺があるのでダメ
                        if (usede[d2][cx2][cy2]) {
                            continue;
                        }
                        // p3 -> p4
                        Point<int> p4 = nxtv[d2][cx2][cy2];
                        // p2,p4の順序を固定して回転方向の重複を省く
                        if (p4 != NG and p2.x <= p4.x) {
                            Point<int> p1 = find_p1(p2, p3, p4);
                            if (p1 != NG) {
                                int d3 = d%2 == 0 ? d+1 : d-1;
                                int cx3 = p4.x, cy3 = p4.y;
                                if (usede[d3][cx3][cy3]) {
                                    continue;
                                }
                                // p4 -> p1
                                // p1に頂点がなく、p1から見て最初に着く頂点がp4ならOK
                                bool ok = (not usedv[p1.x][p1.y] and nxtv[d][p1.x][p1.y] == p4);
                                // p1まで使用済頂点なく到達
                                if (ok) {
                                    int d4 = d2%2 == 0 ? d2+1 : d2-1;
                                    int cx4 = p1.x, cy4 = p1.y;
                                    if (usede[d4][cx4][cy4]) {
                                        continue;
                                    }
                                    // p1 -> p2
                                    // p1から見て最初に着く頂点がp2ならOK
                                    ok = (nxtv[d4][p1.x][p1.y] == p2);
                                    if (ok) {
                                        candi.pb({p1, p2, p3, p4});
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        // UNIQUE(candi);
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
        return 1;
    };

    vector<array<Point<int>, 4>> ans;
    ll mxscore = calc();
    auto elapsed = timer.get_elapse();
    int opcnt = 0;
    int bestoptype = -1;
    vector<array<Point<int>, 4>> curans;
    while (elapsed < TL) {
        int optype = randrange(0, 7);
        // 0,1は多いので割合を増やす
        if (optype == 5) optype = 0;
        elif (optype == 6) optype = 1;
        // 傾向として0はオールラウンド、1,2は密に強く、3,4は疎に強い
        // 明らかに望み薄なパターンが来たら切り替える
        if (optype == 1 and dens <= 0.04) optype = 0;
        if (optype == 3 and dens >= 0.06) optype = 0;
        if (optype == 4 and dens >= 0.06) optype = 0;
        // if (optype == 0 and dens >= 0.08) optype = 1;
        if (optype == 0) {
            while (elapsed < TL) {
                auto candi = get_canditates();
                if (candi.empty()) break;
                array<Point<int>, 4> nxt = {};
                ll mna = INF, mnb = INF;
                rep(i, candi.size()) {
                    auto& [p1, p2, p3, p4] = candi[i];
                    // なるべく辺の短い操作を優先させる
                    ll a = abs(p1.x-p3.x) + abs(p1.y-p3.y);
                    // タイブレークは乱択
                    ll b = randrange(0, 1000000000);
                    if (a < mna or (a == mna and b < mnb)) {
                        nxt = {p1, p2, p3, p4};
                        mna = a;
                        mnb = b;
                    }
                }
                auto& [p1, p2, p3, p4] = nxt;
                put({p1, p2, p3, p4});
                curans.pb({p1, p2, p3, p4});
                elapsed = timer.get_elapse();
            }
        } elif (optype == 1) {
            while (elapsed < TL) {
                auto candi = get_canditates();
                if (candi.empty()) break;
                array<Point<int>, 4> nxt = {};
                ll mna = INF, mnb = INF, mnc = INF;
                rep(i, candi.size()) {
                    auto& [p1, p2, p3, p4] = candi[i];
                    // なるべく辺の短い操作を優先させる
                    ll a = abs(p1.x-p3.x) + abs(p1.y-p3.y);
                    // なるべく中心寄りから埋める
                    ll b = get_cost(p1);
                    // タイブレークは乱択
                    ll c = randrange(0, 1000000000);
                    if (
                        a < mna or
                        (a == mna and b < mnb) or
                        (a == mna and b == mnb and c < mnc)
                    ) {
                        nxt = {p1, p2, p3, p4};
                        mna = a;
                        mnb = b;
                        mnc = c;
                    }
                }
                auto& [p1, p2, p3, p4] = nxt;
                put({p1, p2, p3, p4});
                curans.pb({p1, p2, p3, p4});
                elapsed = timer.get_elapse();
            }
        } elif (optype == 2) {
            while (elapsed < TL) {
                auto candi = get_canditates();
                if (candi.empty()) break;
                array<Point<int>, 4> nxt = {};
                ll mna = INF, mnb = INF, mnc = INF;
                rep(i, candi.size()) {
                    auto& [p1, p2, p3, p4] = candi[i];
                    // なるべく辺の短い操作を優先させる
                    ll a = abs(p1.x-p3.x) + abs(p1.y-p3.y);
                    // なるべく外寄りから埋める
                    ll b = -get_cost(p1);
                    // タイブレークは乱択
                    ll c = randrange(0, 1000000000);
                    if (
                        a < mna or
                        (a == mna and b < mnb) or
                        (a == mna and b == mnb and c < mnc)
                    ) {
                        nxt = {p1, p2, p3, p4};
                        mna = a;
                        mnb = b;
                        mnc = c;
                    }
                }
                auto& [p1, p2, p3, p4] = nxt;
                put({p1, p2, p3, p4});
                curans.pb({p1, p2, p3, p4});
                elapsed = timer.get_elapse();
            }
        } elif (optype == 3) {
            while (elapsed < TL) {
                auto candi = get_canditates();
                if (candi.empty()) break;
                array<Point<int>, 4> nxt = {};
                ll mna = INF, mnb = INF;
                rep(i, candi.size()) {
                    auto& [p1, p2, p3, p4] = candi[i];
                    // なるべく外寄りから埋める
                    ll a = -get_cost(p1);
                    // タイブレークは乱択
                    ll b = randrange(0, 1000000000);
                    if (a < mna or (a == mna and b < mnb)) {
                        nxt = {p1, p2, p3, p4};
                        mna = a;
                        mnb = b;
                    }
                }
                auto& [p1, p2, p3, p4] = nxt;
                put({p1, p2, p3, p4});
                curans.pb({p1, p2, p3, p4});
                elapsed = timer.get_elapse();
            }
        } elif (optype == 4) {
            while (elapsed < TL) {
                auto candi = get_canditates();
                if (candi.empty()) break;
                array<Point<int>, 4> nxt = {};
                ll mna = INF, mnb = INF, mnc = INF;
                rep(i, candi.size()) {
                    auto& [p1, p2, p3, p4] = candi[i];
                    // なるべく外寄りから埋める
                    ll a = -get_cost(p1);
                    // なるべく辺の短い操作を優先させる
                    ll b = abs(p1.x-p3.x) + abs(p1.y-p3.y);
                    // タイブレークは乱択
                    ll c = randrange(0, 1000000000);
                    if (
                        a < mna or
                        (a == mna and b < mnb) or
                        (a == mna and b == mnb and c < mnc)
                    ) {
                        nxt = {p1, p2, p3, p4};
                        mna = a;
                        mnb = b;
                        mnc = c;
                    }
                }
                auto& [p1, p2, p3, p4] = nxt;
                put({p1, p2, p3, p4});
                curans.pb({p1, p2, p3, p4});
                elapsed = timer.get_elapse();
            }
        // 100件中1個だけこれが当たるやつがいるけどとりあえずなし
        // } elif (optype == 5) {
        //     while (elapsed < TL) {
        //         auto candi = get_canditates();
        //         if (candi.empty()) break;
        //         array<Point<int>, 4> nxt = {};
        //         ll mna = INF, mnb = INF;
        //         rep(i, candi.size()) {
        //             auto& [p1, p2, p3, p4] = candi[i];
        //             // なるべく中寄りから埋める
        //             ll a = get_cost(p1);
        //             // タイブレークは乱択
        //             ll b = randrange(0, 1000000000);
        //             if (a < mna or (a == mna and b < mnb)) {
        //                 nxt = {p1, p2, p3, p4};
        //                 mna = a;
        //                 mnb = b;
        //             }
        //         }
        //         auto& [p1, p2, p3, p4] = nxt;
        //         put({p1, p2, p3, p4});
        //         curans.pb({p1, p2, p3, p4});
        //         elapsed = timer.get_elapse();
        //     }
        // ほぼ関係なさそう
        // } elif (optype == 6) {
        //     while (elapsed < TL) {
        //         int prvshapetype = -1;
        //         auto candi = get_canditates();
        //         if (candi.empty()) break;
        //         array<Point<int>, 4> nxt = {};
        //         ll mna = INF, mnb = INF, mnc = INF;
        //         rep(i, candi.size()) {
        //             auto& [p1, p2, p3, p4] = candi[i];
        //             // なるべく辺の短い操作を優先させる
        //             ll a = abs(p1.x-p3.x) + abs(p1.y-p3.y);
        //             // なるべく縦横と斜めを交互にする
        //             ll b = (check_dir(p1, p2) < 4) == prvshapetype;
        //             // タイブレークは乱択
        //             ll c = randrange(0, 1000000000);
        //             if (
        //                 a < mna or
        //                 (a == mna and b < mnb) or
        //                 (a == mna and b == mnb and c < mnc)
        //             ) {
        //                 nxt = {p1, p2, p3, p4};
        //                 mna = a;
        //                 mnb = b;
        //                 mnc = c;
        //             }
        //         }
        //         auto& [p1, p2, p3, p4] = nxt;
        //         put({p1, p2, p3, p4});
        //         curans.pb({p1, p2, p3, p4});
        //         elapsed = timer.get_elapse();
        //         prvshapetype = check_dir(p1, p2) < 4;
        //     }
        } else {
            assert(0);
        }

        opcnt++;
        ll score = calc();
        if (chmax(mxscore, score)) {
            ans = curans;
            bestoptype = optype;
        }
        rollback(curans);
        assert((int)P.size() == M);
        elapsed = timer.get_elapse();
    }

    #ifdef __LOCAL
        debug(opcnt);
        debug(dens);
        debug(bestoptype);
        C[bestoptype]++;
        chmax(mxdens[bestoptype], dens);
        chmin(mndens[bestoptype], dens);
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

// テスト番号指定
vector<int> gen_cases1(const vector<int>& T) {
    return T;
}

// sからn件実施
vector<int> gen_cases2(int s, int n) {
    vector<int> T;
    rep(i, s, s+n) {
        T.eb(i);
    }
    return T;
}

// [s,t)を実施
vector<int> gen_cases3(int s, int t) {
    vector<int> T;
    rep(i, s, t) {
        T.eb(i);
    }
    return T;
}

// [s,t)の範囲でランダムにn件実施
vector<int> gen_cases4(int s, int t, int n) {
    vector<int> T;
    rep(i, s, t) {
        T.eb(i);
    }
    shuffle(ALL(T), mt);
    return vector<int>(T.begin(), T.begin()+n);;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // テスト番号指定
        auto T = gen_cases1({5});
        // sからn件実施
        // auto T = gen_cases2(0, 20);
        // [s,t)を実施
        // auto T = gen_cases3(100, 200);
        // [s,t)の範囲でランダムにn件実施
        // auto T = gen_cases4(0, 100, 20);

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
        debug(C);
        debug(mxdens);
        debug(mndens);
    #else
        solve();
    #endif

    return 0;
}

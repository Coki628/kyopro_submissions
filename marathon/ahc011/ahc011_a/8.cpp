/*
・まだ色々あるんだけど、とりあえずパズル解くパートは時間かからないので、
　見込みある盤面全てで試すようにした。まだ時間目一杯にはしてない。
　これでも結構伸びて、1580万点くらい。
・3秒まで回してみた。これで無事2000万点は届いた。
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
#include "common/randrange.hpp"
#include "common/Timer.hpp"
#include "common/listnd.hpp"
#include "common/toint.hpp"
#include "common/chmin.hpp"
#include "common/chmax.hpp"
#include "common/sum.hpp"
#include "grid/gridtoid.hpp"
#include "grid/idtogrid.hpp"
#include "string/zfill.hpp"
#include "graph/UnionFind.hpp"

const int TL = 2700;

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

    int H, W, T;
    cin >> H >> T;
    W = H;
    int N = H * W;
    vector<string> grid(H);
    rep(i, H) cin >> grid[i];

    auto nodes = list2d(H, W, 0);
    // 左上右下
    const vector<pii> dir4 = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    map<pii, int> hwtod;
    rep(d, 4) hwtod[dir4[d]] = d;
    const vector<char> lurd = {'L', 'U', 'R', 'D'};
    int sh = -1, sw = -1;
    int L = 16;
    vector<int> C(L);
    rep(h, H) {
        rep(w, W) {
            // 行ける進行方向をビットで持つ
            nodes[h][w] = grid[h][w] <= '9' ? toint(grid[h][w]) : 10 + (grid[h][w]-'a');
            C[nodes[h][w]]++;
            if (grid[h][w] == '0') {
                sh = h, sw = w;
            }
        }
    }

    // 連結成分数を数えるDFS
    auto memo = list2d(H, W, 0);
    auto dfs = [&](auto&& f, int h, int w, int prvh, int prvw) -> int {
        if (memo[h][w] != 0) {
            return memo[h][w];
        }
        memo[h][w] = -1;
        int sm = 0;
        rep(d, 4) {
            if (!(nodes[h][w]>>d & 1)) continue;
            auto [dh, dw] = dir4[d];
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (nh == prvh and nw == prvw) continue;
            // 逆側からも道があるかチェック
            int revd = (d + 2) % 4;
            if (!(nodes[nh][nw]>>revd & 1)) continue;
            int res = f(f, nh, nw, h, w);
            // 閉路があったら即NG終了
            if (res == -1) {
                return -1;
            }
            sm += res;
        }
        memo[h][w] = sm + 1;
        return sm + 1;
    };

    // スコア計算
    auto calc = [&](int k) -> ld {
        if (k > T) {
            return 0;
        }
        memo = list2d(H, W, 0);
        int S = 0;
        rep(h, H) {
            rep(w, W) {
                chmax(S, dfs(dfs, h, w, -1, -1));
            }
        }
        if (S < N-1) {
            return round(500000 * S/(N-1));
        } else {
            return round(500000 * (2-k/T));
        }
    };

    // 位置(ch,cw)にピースcを置くことが妥当かどうか
    auto valid = [&](vvi& nodestmp, int ch, int cw, int c) -> bool {
        rep(d, 4) {
            auto [dh, dw] = dir4[d];
            int nh = ch + dh;
            int nw = cw + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) {
                // 行き止まりに向かう道が生えていたらNG
                if (c>>d & 1) {
                    return false;
                }
                continue;
            }
            if (nodestmp[nh][nw] != -1) {
                // こちらからの道と逆からの道の有無が一致しているか
                int revd = (d + 2) % 4;
                if ((c>>d & 1) ^ (nodestmp[nh][nw]>>revd & 1)) {
                    return false;
                }
            }
        }
        return true;
    };

    // 現状の盤面nodesでのbittonodestmpを達成させるためのコスト
    auto get_cost = [&](vector<vector<pii>>& bittonodestmp) {
        auto cost = list2d(H, W, INF);
        rep(h, H) {
            rep(w, W) {
                for (auto [h2, w2] : bittonodestmp[nodes[h][w]]) {
                    chmin(cost[h2][w2], abs(h-h2)+abs(w-w2));
                }
            }
        }
        ll sm = 0;
        rep(h, H) {
            rep(w, W) {
                if (cost[h][w] == INF) continue;
                sm += cost[h][w];
            }
        }
        return sm;
    };

    vector<int> bit(L-1);
    iota(ALL(bit), 1);
    UnionFind uf(N);
    auto dfs2 = [&](auto&& f, vvi& nodestmp, int ch, int cw) -> void {
        rep(d, 4) {
            if (!(nodestmp[ch][cw]>>d & 1)) continue;
            auto [dh, dw] = dir4[d];
            int nh = ch + dh;
            int nw = cw + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (nodestmp[nh][nw] != -1) continue;
            shuffle(ALL(bit), mt);
            rep(i, L-1) {
                if (C[bit[i]] == 0) continue;
                int u = gridtoid(ch, cw, W);
                int v = gridtoid(nh, nw, W);
                if (valid(nodestmp, nh, nw, bit[i]) and not uf.same(u, v)) {
                    nodestmp[nh][nw] = bit[i];
                    C[bit[i]]--;
                    uf.merge(u, v);
                    f(f, nodestmp, nh, nw);
                    break;
                }
            }
        }
    };

    auto nodes2 = list2d(H, W, -1);
    string ans;
    ld mxscore = 0;
    auto elapsed = timer.get_elapse();
    int opcnt = 0;
    while (1) {
        if (opcnt%1 == 0) {
            elapsed = timer.get_elapse();
            if (elapsed >= TL) break;
        }
        opcnt++;
        rep(h, H) {
            rep(w, W) {
                if (h == H-1 and w == W-1) continue;
                rep(c, 1, L) {
                    if (C[c] == 0) continue;
                    auto bkc = C;
                    auto nodestmp = list2d(H, W, -1);
                    nodestmp[H-1][W-1] = 0;
                    C[0]--;
                    nodestmp[h][w] = c;
                    if (valid(nodestmp, h, w, c)) {
                        C[c]--;
                        uf = UnionFind(N);
                        dfs2(dfs2, nodestmp, h, w);
                        ll use = N - sum(C);
                        // debug(use);
                        if (use >= N*2/3) {
                            // vector<vector<pii>> bittonodestmp(L);
                            // rep(h, H) {
                            //     rep(w, W) {
                            //         if (nodestmp[h][w] != -1) {
                            //             bittonodestmp[nodestmp[h][w]].eb(h, w);
                            //         }
                            //     }
                            // }
                            // 余りを適当な所に割り振る
                            int tmpc = 0;
                            rep(h, H) {
                                rep(w, W) {
                                    if (nodestmp[h][w] == -1) {
                                        while (C[tmpc] == 0) {
                                            tmpc++;
                                            assert(tmpc < L);
                                        }
                                        nodestmp[h][w] = tmpc;
                                        C[tmpc]--;
                                    }
                                }
                            }
                            assert(sum(C) == 0);

                            auto nodesbk = nodes;
                            string curans;
                            int k = 0;
                            auto fixed = list2d(H, W, false);
                            int ch = sh, cw = sw;

                            auto update = [&](int ch, int cw, int nh, int nw) -> void {
                                swap(nodes[ch][cw], nodes[nh][nw]);
                            };

                            auto move = [&](int ch, int cw, int nh, int nw) {
                                int dh = nh - ch;
                                int dw = nw - cw;
                                // 隣接移動
                                assert(abs(dh)+abs(dw) == 1);
                                update(ch, cw, nh, nw);
                                curans += lurd[hwtod[{dh, dw}]];
                                k++;
                            };

                            // (sh,sw)から(gh,gw)への最短ルートを返す
                            auto bfs = [&](int sh, int sw, int gh, int gw) -> vector<pii> {
                                auto res = list2d(H, W, INF);
                                auto prv = list2d(H, W, pii({-1, -1}));
                                queue<pii> que;
                                que.push({sh, sw});
                                res[sh][sw] = 0;
                                while (!que.empty()) {
                                    auto [h, w] = que.front(); que.pop();
                                    if (h == gh and w == gw) break;
                                    for (auto [dh, dw] : dir4) {
                                        int nh = h + dh;
                                        int nw = w + dw;
                                        if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                                        if (fixed[nh][nw]) continue;
                                        if (res[nh][nw] == INF) {
                                            res[nh][nw] = res[h][w] + 1;
                                            prv[nh][nw] = {h, w};
                                            que.push({nh, nw});
                                        }
                                    }
                                }
                                // 辿り着けない時がある(スワップできればいけそうなんだけど…)
                                if (prv[gh][gw] == mkp(-1, -1)) {
                                    return {};
                                }
                                vector<pii> route;
                                int ch = gh, cw = gw;
                                route.eb(ch, cw);
                                while (ch != sh or cw != sw) {
                                    tie(ch, cw) = prv[ch][cw];
                                    route.eb(ch, cw);
                                }
                                reverse(ALL(route));
                                return route;
                            };

                            // (sh,sw)から種類cのピースへの最短ルートを返す
                            auto bfs2 = [&](int sh, int sw, int c) -> vector<pii> {
                                auto res = list2d(H, W, INF);
                                auto prv = list2d(H, W, pii({-1, -1}));
                                queue<pii> que;
                                que.push({sh, sw});
                                res[sh][sw] = 0;
                                int gh = -1, gw = -1;
                                while (!que.empty()) {
                                    auto [h, w] = que.front(); que.pop();
                                    int curc = nodes[h][w];
                                    if (curc == c) {
                                        gh = h, gw = w;
                                        break;
                                    };
                                    for (auto [dh, dw] : dir4) {
                                        int nh = h + dh;
                                        int nw = w + dw;
                                        if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                                        if (fixed[nh][nw]) continue;
                                        if (res[nh][nw] == INF) {
                                            res[nh][nw] = res[h][w] + 1;
                                            prv[nh][nw] = {h, w};
                                            que.push({nh, nw});
                                        }
                                    }
                                }
                                // 辿り着けない時がある、多分
                                if (gh == -1) {
                                    return {};
                                }
                                vector<pii> route;
                                int ch = gh, cw = gw;
                                route.eb(ch, cw);
                                while (ch != sh or cw != sw) {
                                    tie(ch, cw) = prv[ch][cw];
                                    route.eb(ch, cw);
                                }
                                reverse(ALL(route));
                                return route;
                            };

                            // 予め決めた完成形を目指すように進める
                            auto bring = [&](int sh, int sw, int gh, int gw) {
                                // (sh,sw)を(gh,gw)に持ってくるルート
                                auto route = bfs(sh, sw, gh, gw);
                                if (sh == ch and sw == cw) {
                                    rep(i, 1, route.size()) {
                                        auto [ch2, cw2] = route[i-1];
                                        auto [nh2, nw2] = route[i];
                                        move(ch2, cw2, nh2, nw2);
                                    }
                                    ch = gh;
                                    cw = gw;
                                } else {
                                    rep(i, 1, route.size()) {
                                        auto [th, tw] = route[i-1];
                                        auto [nh, nw] = route[i];
                                        fixed[th][tw] = true;
                                        // 空マスを(nh,nw)に持ってくる
                                        auto route2 = bfs(ch, cw, nh, nw);
                                        if (route2.empty()) {
                                            fixed[th][tw] = false;
                                            return;
                                        }
                                        rep(j, 1, route2.size()) {
                                            auto [ch2, cw2] = route2[j-1];
                                            auto [nh2, nw2] = route2[j];
                                            move(ch2, cw2, nh2, nw2);
                                        }
                                        // (sh,sw)を1つ動かす
                                        move(nh, nw, th, tw);
                                        ch = th;
                                        cw = tw;
                                        fixed[th][tw] = false;
                                    }
                                }
                            };

                            auto bring2 = [&](int c, int gh, int gw) {
                                assert(c != 0);
                                // ピースcを(gh,gw)に持ってくるルート
                                auto route = bfs2(gh, gw, c);
                                if (route.size() <= 1) return;
                                reverse(ALL(route));
                                auto [sh, sw] = route[0];
                                if (sh == ch and sw == cw) {
                                    rep(i, 1, route.size()) {
                                        auto [ch2, cw2] = route[i-1];
                                        auto [nh2, nw2] = route[i];
                                        move(ch2, cw2, nh2, nw2);
                                    }
                                    ch = gh;
                                    cw = gw;
                                } else {
                                    rep(i, 1, route.size()) {
                                        auto [th, tw] = route[i-1];
                                        auto [nh, nw] = route[i];
                                        fixed[th][tw] = true;
                                        // 空マスを(nh,nw)に持ってくる
                                        auto route2 = bfs(ch, cw, nh, nw);
                                        if (route2.empty()) {
                                            fixed[th][tw] = false;
                                            return;
                                        }
                                        rep(j, 1, route2.size()) {
                                            auto [ch2, cw2] = route2[j-1];
                                            auto [nh2, nw2] = route2[j];
                                            move(ch2, cw2, nh2, nw2);
                                        }
                                        // (sh,sw)を1つ動かす
                                        move(nh, nw, th, tw);
                                        ch = th;
                                        cw = tw;
                                        fixed[th][tw] = false;
                                    }
                                }
                            };

                            // スライドパズルの解き方
                            // 参考：https://qiita.com/GANTZ/items/fb9a2062959701b8840f
                            // 　　　http://studio-boiler.com/k/kouryaku/kou.htm
                            // ・基本は隣に付けて1つ動かすを繰り返す。
                            // ・端2マスは同時に入れないと詰むので、2つ同時に引っ張ってくる感じにする。
                            // 　(2つが逆になってる時の直し方が難しい)
                            // ・これを縦横でやれば右端4マスしか残らないので、後は適当に回す。
                            // 　(偶奇で最後合わない時もある)
                            rep(h, H-2) {
                                rep(w, W-2) {
                                    assert(nodestmp[h][w] != -1);
                                    // 目当ての数字をここに持ってくるルート
                                    bring2(nodestmp[h][w], h, w);
                                    fixed[h][w] = true;
                                }
                                // 端2マスをまとめて決める
                                // (ch,cw),(h3,w3),(h2,w2)と並べる
                                bring2(nodestmp[h][W-1], h, W-2);
                                fixed[h][W-2] = true;
                                bring2(nodestmp[h][W-2], h+1, W-2);
                                fixed[h+1][W-2] = true;
                                bring(ch, cw, h, W-1);
                                // (h3,w3),(h2,w2)を正しい位置に
                                move(h, W-1, h, W-2);
                                move(h, W-2, h+1, W-2);
                                fixed[h][W-1] = true;
                                fixed[h+1][W-2] = false;
                                ch = h + 1;
                                cw = W - 2;
                            }
                            rep(w, W-2) {
                                // 端2マスをまとめて決める
                                // (ch,cw),(h3,w3),(h2,w2)と並べる
                                bring2(nodestmp[H-1][w], H-2, w);
                                fixed[H-2][w] = true;
                                bring2(nodestmp[H-2][w], H-2, w+1);
                                fixed[H-2][w+1] = true;
                                bring(ch, cw, H-1, w);
                                // (h3,w3),(h2,w2)を正しい位置に
                                move(H-1, w, H-2, w);
                                move(H-2, w, H-2, w+1);
                                fixed[H-1][w] = true;
                                fixed[H-2][w+1] = false;
                                ch = H - 2;
                                cw = w + 1;
                            }
                            move(H-2, W-2, H-2, W-1);
                            move(H-2, W-1, H-1, W-1);

                            // 3パターンのうちいいものを
                            ld score = calc(k);
                            string tmpans = curans;
                            rep(_, 2) {
                                move(H-1, W-1, H-1, W-2);
                                move(H-1, W-2, H-2, W-2);
                                move(H-2, W-2, H-2, W-1);
                                move(H-2, W-1, H-1, W-1);
                                if (chmax(score, calc(k))) {
                                    tmpans = curans;
                                }
                            }
                            if (chmax(mxscore, score)) {
                                ans = tmpans;
                            }
                            nodes = nodesbk;
                        }
                    }
                    C = bkc;
                }
            }
        }
    }

    #ifdef __LOCAL
        debug(opcnt);
    #endif
    print(ans);
    return mxscore;
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
            ld score = solve(t);
            cout << "case #" << t << " ";
            debug(score);
            totalscore += score;
        }
        debug(totalscore);
    #else
        solve();
    #endif

    return 0;
}

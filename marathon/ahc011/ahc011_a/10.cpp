/*
・怪しいとこは色々あるんだけどひと段落なので出した。
　結局端は1マスしかない隙間に欲しいやつがあるとつらいので、
　3つずつやることにした。それで9マス残って全探索はまだ(たくさんやるとなると)きついので、
　合わない時があるのは承知でそこは妥協することにした。
　色々良くしたつもりだけど、これは伸びず1910万点…。
　やっぱ盤面探すパート改善しないとダメかな。。
　ちょいちょい閉路作っちゃってるっぽいんだよね。
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
#include "common/HashMap.hpp"
#include "grid/gridtoid.hpp"
#include "grid/idtogrid.hpp"
#include "string/zfill.hpp"
#include "graph/UnionFind.hpp"

const int TL = 2700;
// 左上右下
const vector<pii> dir4 = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
const vector<char> lurd = {'L', 'U', 'R', 'D'};
const int L = 16;

// スコア計算
auto calc = [](
    int H, int W, int N, int T, int k, const vvi& nodes
) -> ld {
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

pair<ld, string> construct(
    int H, int W, int N, int T, int sh, int sw, string key,
    vvi nodes, const vvi& target, HashMap<pii, int>& hwtod
) {
    string curans, tmpans;
    ld score = 0;
    int k = 0;
    auto fixed = list2d(H, W, false);
    int ch = sh, cw = sw;
    try {
        auto update = [&](int ch, int cw, int nh, int nw) -> void {
            swap(nodes[ch][cw], nodes[nh][nw]);
            int i = gridtoid(ch, cw, W);
            int j = gridtoid(nh, nw, W);
            swap(key[i], key[j]);
        };

        auto move = [&](int ch, int cw, int nh, int nw) {
            int dh = nh - ch;
            int dw = nw - cw;
            // 隣接移動
            assert(abs(dh)+abs(dw) == 1);
            update(ch, cw, nh, nw);
            curans += lurd[hwtod[{dh, dw}]];
            k++;
            if (k == T) {
                throw -1;
            }
        };

        // (sh,sw)から(gh,gw)への最短ルートを返す
        auto bfs = [&](int sh, int sw, int gh, int gw) -> vector<pii> {
            auto visited = list2d(H, W, false);
            auto prv = list2d(H, W, pii({-1, -1}));
            queue<pii> que;
            que.push({sh, sw});
            visited[sh][sw] = true;
            while (que.size()) {
                auto [h, w] = que.front(); que.pop();
                if (h == gh and w == gw) break;
                for (auto [dh, dw] : dir4) {
                    int nh = h + dh;
                    int nw = w + dw;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (fixed[nh][nw]) continue;
                    if (not visited[nh][nw]) {
                        visited[nh][nw] = true;
                        prv[nh][nw] = {h, w};
                        que.push({nh, nw});
                    }
                }
            }
            // 辿り着けない時はなくなったはず
            // assert(sh == gh and sw == gw or prv[gh][gw] != mkp(-1, -1));
            if (not (sh == gh and sw == gw or prv[gh][gw] != mkp(-1, -1))) {
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
            auto visited = list2d(H, W, false);
            auto prv = list2d(H, W, pii({-1, -1}));
            queue<pii> que;
            que.push({sh, sw});
            visited[sh][sw] = true;
            int gh = -1, gw = -1;
            while (que.size()) {
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
                    if (not visited[nh][nw]) {
                        visited[nh][nw] = true;
                        prv[nh][nw] = {h, w};
                        que.push({nh, nw});
                    }
                }
            }
            // 辿り着けない時はなくなったはず
            // assert(gh != -1 and gw != -1);
            if (not (gh != -1 and gw != -1)) {
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

        // (sh,sw)を(gh,gw)に持ってくる
        auto bring = [&](int sh, int sw, int gh, int gw) {
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

        // ピース種類cを(gh,gw)に持ってくる
        auto bring2 = [&](int c, int gh, int gw) {
            assert(c != 0);
            auto route = bfs2(gh, gw, c);
            // 移動不要 or 無理
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

        auto swap_fix = [&](int ah, int aw, int bh, int bw) {
        };

        // スライドパズルの解き方
        // 参考：https://qiita.com/GANTZ/items/fb9a2062959701b8840f
        // 　　　http://studio-boiler.com/k/kouryaku/kou.htm
        // ・基本は隣に付けて1つ動かすを繰り返す。
        // ・端2マスは同時に入れないと詰むので、2つ同時に引っ張ってくる感じにする。
        // 　(2つが逆になってる時の直し方が難しい)
        // ・これを縦横でやれば右端4マスしか残らないので、後は適当に回す。
        // 　(偶奇？で最後絶対合わない時もある)
        rep(h, H-3) {
            rep(w, W-3) {
                assert(target[h][w] != -1);
                // 目当ての数字をここに持ってくるルート
                bring2(target[h][w], h, w);
                assert(nodes[h][w] == target[h][w]);
                fixed[h][w] = true;
            }
            // 端3マスをまとめて決める
            bring2(target[h][W-2], h, W-3);
            fixed[h][W-3] = true;
            bring2(target[h][W-3], h+1, W-3);
            fixed[h+1][W-3] = true;
            bring2(target[h][W-1], h, W-2);
            fixed[h][W-2] = true;
            // 正しい位置に
            bring(ch, cw, h, W-1);
            move(h, W-1, h, W-2);
            move(h, W-2, h, W-3);
            move(h, W-3, h+1, W-3);
            fixed[h][W-1] = true;
            fixed[h+1][W-3] = false;
            ch = h + 1;
            cw = W - 3;
        }
        rep(w, W-3) {
            // 端3マスをまとめて決める
            bring2(target[H-2][w], H-3, w);
            fixed[H-3][w] = true;
            bring2(target[H-3][w], H-3, w+1);
            fixed[H-3][w+1] = true;
            bring2(target[H-1][w], H-2, w);
            fixed[H-2][w] = true;
            // 正しい位置に
            bring(ch, cw, H-1, w);
            move(H-1, w, H-2, w);
            move(H-2, w, H-3, w);
            move(H-3, w, H-3, w+1);
            fixed[H-1][w] = true;
            fixed[H-3][w+1] = false;
            ch = H - 3;
            cw = w + 1;
        }
        bring2(target[H-3][W-3], H-3, W-3);
        fixed[H-3][W-3] = true;

        // auto brute_force = [&]() {
        //     HashMap<string, string> memo;
        //     queue<string> que;
        //     memo[key] = "";
        //     que.push(key);
        //     while (que.size()) {
        //         auto cur = que.front(); que.pop();
        //         int i = cur.find('0');
        //         auto [ch, cw] = idtogrid(i, W);
        //         auto prv = cur;
        //         rep(d, 4) {
        //             auto [dh, dw] = dir4[d];
        //             int nh = ch + dh;
        //             int nw = cw + dw;
        //             if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
        //             if (fixed[nh][nw]) continue;
        //             int j = gridtoid(nh, nw, W);
        //             swap(cur[i], cur[j]);
        //             if (not memo.count(cur)) {
        //                 memo[cur] = memo[prv] + lurd[d];
        //                 que.push(cur);
        //             }
        //             swap(cur[i], cur[j]);
        //         }
        //     }
        //     // 最大2万あってつらい
        //     auto sz = memo.size();
        // };
        // brute_force();

        bring2(target[H-2][W-3], H-2, W-3);
        fixed[H-2][W-3] = true;
        // ここから無理な時もあるんだけどまあやれるだけやる
        bring2(target[H-3][W-2], H-3, W-2);
        fixed[H-3][W-2] = true;
        bring2(target[H-1][W-3], H-1, W-3);
        fixed[H-1][W-3] = true;
        bring2(target[H-3][W-1], H-3, W-1);
        fixed[H-3][W-1] = true;

        // 右下端4マスは3パターンのうちいいものを
        score = calc(H, W, N, T, k, nodes);
        tmpans = curans;
        rep(_, 2) {
            move(H-1, W-1, H-1, W-2);
            move(H-1, W-2, H-2, W-2);
            move(H-2, W-2, H-2, W-1);
            move(H-2, W-1, H-1, W-1);
            if (chmax(score, calc(H, W, N, T, k, nodes))) {
                tmpans = curans;
            }
        }
        return {score, tmpans};
    } catch (int e) {
        // ターン数オーバー時の強制終了
        if (not tmpans.empty()) {
            return {score, tmpans};
        } else {
            return {calc(H, W, N, T, k, nodes), curans};
        }
    }
}

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

    HashMap<pii, int> hwtod;
    rep(d, 4) hwtod[dir4[d]] = d;
    auto nodes = list2d(H, W, 0);
    vector<int> C(L);
    int sh = -1, sw = -1;
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
    string key;
    rep(i, H) {
        key += grid[i];
    }

    // 位置(ch,cw)にピースcを置くことが妥当かどうか
    auto valid = [&](vvi& target, int ch, int cw, int c) -> bool {
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
            if (target[nh][nw] != -1) {
                // こちらからの道と逆からの道の有無が一致しているか
                int revd = (d + 2) % 4;
                if ((c>>d & 1) ^ (target[nh][nw]>>revd & 1)) {
                    return false;
                }
            }
        }
        return true;
    };

    // 現状の盤面nodesでのbittotargetを達成させるためのコスト
    auto get_cost = [&](vector<vector<pii>>& bittotarget) {
        auto cost = list2d(H, W, INF);
        rep(h, H) {
            rep(w, W) {
                for (auto [h2, w2] : bittotarget[nodes[h][w]]) {
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

    // 適当に進んで全域木構築を試みるDFS
    vector<int> bit(L-1);
    iota(ALL(bit), 1);
    UnionFind uf(N);
    auto dfs2 = [&](auto&& f, vvi& target, int ch, int cw) -> void {
        rep(d, 4) {
            if (!(target[ch][cw]>>d & 1)) continue;
            auto [dh, dw] = dir4[d];
            int nh = ch + dh;
            int nw = cw + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (target[nh][nw] != -1) continue;
            shuffle(ALL(bit), mt);
            rep(i, L-1) {
                if (C[bit[i]] == 0) continue;
                int u = gridtoid(ch, cw, W);
                int v = gridtoid(nh, nw, W);
                if (valid(target, nh, nw, bit[i]) and not uf.same(u, v)) {
                    target[nh][nw] = bit[i];
                    C[bit[i]]--;
                    uf.merge(u, v);
                    f(f, target, nh, nw);
                    break;
                }
            }
        }
    };

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
                    auto target = list2d(H, W, -1);
                    target[H-1][W-1] = 0;
                    C[0]--;
                    target[h][w] = c;
                    if (valid(target, h, w, c)) {
                        C[c]--;
                        uf = UnionFind(N);
                        dfs2(dfs2, target, h, w);
                        ll use = N - sum(C);
                        // debug(use);
                        if (use >= N*4/5) {
                            // 余りを適当な所に割り振る
                            int tmpc = 0;
                            rep(h, H) {
                                rep(w, W) {
                                    if (target[h][w] == -1) {
                                        while (C[tmpc] == 0) {
                                            tmpc++;
                                            assert(tmpc < L);
                                        }
                                        target[h][w] = tmpc;
                                        C[tmpc]--;
                                    }
                                }
                            }
                            assert(sum(C) == 0);

                            // vector<vector<pii>> bittotarget(L);
                            // rep(h, H) {
                            //     rep(w, W) {
                            //         if (target[h][w] != -1) {
                            //             bittotarget[target[h][w]].eb(h, w);
                            //         }
                            //     }
                            // }
                            // auto cost = get_cost(bittotarget);

                            // 今回のtargetに基づいてパズル完成を目指す
                            auto res = construct(
                                H, W, N, T, sh, sw, key,
                                nodes, target, hwtod
                            );
                            if (chmax(mxscore, res.first)) {
                                ans = res.second;
                            }
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

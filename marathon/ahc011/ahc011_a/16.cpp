/*
・回数できなくなるから没にしてたラスト9*9の全探索を採用してみた。
　意外と善戦してちょいベスト更新。2226万点台になった。
・本番中はこれで最終提出。木の構築が整わなかった割にはギリ青パフォ出たからまあ良かったか。
参考：https://eijirou-kyopro.hatenablog.com/entry/2022/06/05/224615
　　　https://twitter.com/G4NP0N_kyopro/status/1533396276166787073
・終了後、色々試そうとも思ったけど、実装面倒になってしまったのでここでお気持ちだけ書いておく…。
　まず、木の構築は山登りとか焼きなましでやるのが本筋だったぽい。
　eijirouさんの記事によると、入力と同じ方法(問題文内の折り畳み内に書いてある…)で、
　適当な木を作成、ピースの枚数を数えておいて、その差分を小さくしていくように、
　1本辺追加・1本外して閉路除去、を繰り返せばよかったらしい。
　山登りとかやりたかったけど、コストに何使えば良かったか妙案が出なかったんだよな。
　ピース枚数の差分か。で、この差分は2乗したものをコストとするといいそう。
　確かTLで他の人も2乗がいいって言ってた気がする。そのままだと変化が小さくて手掛かりには弱いのかな。
　で、別解としてDFSでも木の構築はできるとのこと。こちらはがんぽんさんのツイートより。
　自分の適当DFSと決定的に違うと思ったのは多分、
　各方向に繋がる道が現時点で何個残ってるかを管理することで、
　今残ってるピースと照らし合わせて、足りなくなるような場面では使わない、
　みたいな処理だったっぽい。(実装した訳じゃないのであくまで推測だけど…)
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
#include "common/HashSet.hpp"
#include "grid/gridtoid.hpp"
#include "grid/idtogrid.hpp"
#include "string/zfill.hpp"
#include "graph/UnionFind.hpp"

const int TL = 2700;
// 左上右下
const vector<pii> dir4 = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
const vector<char> lurd = {'L', 'U', 'R', 'D'};
const int L = 16;
int chartoint(char c) {
    return c <= '9' ? toint(c) : 10 + (c-'a');
}

// スコア計算
auto calc = [](
    int H, int W, int N, int T, int k, const vvi& nodes
) -> ld {
    if (k > T) {
        return 0;
    }
    UnionFind uf(N);
    rep(h, H) {
        rep(w, W) {
            rep(d, 2) {
                if (!(nodes[h][w]>>d & 1)) continue;
                auto [dh, dw] = dir4[d];
                int nh = h + dh;
                int nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                // 逆側からも道があるかチェック
                int revd = (d + 2) % 4;
                if (nodes[nh][nw]>>revd & 1) {
                    int u = gridtoid(h, w, W);
                    int v = gridtoid(nh, nw, W);
                    uf.merge(u, v);
                }
            }
        }
    }
    int S = 0;
    for (auto r : uf.get_roots()) {
        if (uf.is_tree(r)) {
            chmax(S, (int)uf.size(r));
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
        // ・端を2マスずつでやると、最後に動かせる領域が幅2になった時にたまに
        // 　めちゃ動かしづらくなるので、端は3マスずつ決めるとする。
        // 　これだと最後の3*3までは確実に合わせることができて、
        // 　3*3は8パズルなので全探索で状態2万くらいなので、ここは愚直全部やる。
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

        auto brute_force = [&]() {
            HashMap<string, string> memo;
            queue<string> que;
            memo[key] = "";
            que.push(key);
            while (que.size()) {
                auto cur = que.front(); que.pop();
                int i = cur.find('0');
                auto [ch, cw] = idtogrid(i, W);
                auto prv = cur;
                rep(d, 4) {
                    auto [dh, dw] = dir4[d];
                    int nh = ch + dh;
                    int nw = cw + dw;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (fixed[nh][nw]) continue;
                    int j = gridtoid(nh, nw, W);
                    swap(cur[i], cur[j]);
                    if (not memo.count(cur)) {
                        memo[cur] = memo[prv] + lurd[d];
                        que.push(cur);
                    }
                    swap(cur[i], cur[j]);
                }
            }
            int mxcnt = 3 * 3;
            for (auto& [curkey, addans] : memo) {
                int matchcnt = 0;
                rep(h, H-3, H) {
                    rep(w, W-3, W) {
                        int i = gridtoid(h, w, W);
                        nodes[h][w] = chartoint(curkey[i]);
                        if (curkey[i] == key[i]) matchcnt++;
                    }
                }
                if (matchcnt >= mxcnt-2) {
                    if (chmax(score, calc(H, W, N, T, k, nodes))) {
                        tmpans = curans + addans;
                    }
                }
            }
            
        };
        brute_force();
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
            nodes[h][w] = chartoint(grid[h][w]);
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
    auto valid = [&](
        vvi& target, int ch, int cw, int c
    ) -> bool {
        int edgecnt = 0;
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
                // 辺がつく場合、連結成分を確認
                if ((c>>d & 1) and (target[nh][nw]>>revd & 1)) {
                    edgecnt++;
                }
            }
        }
        // 2箇所以上つながったら閉路を作るのでNG
        if (edgecnt >= 2) {
            return false;
        }
        return true;
    };

    // ここにパーツcを置く時の辺を列挙
    auto check_edges = [&](
        vvi& target, int ch, int cw, int c
    ) -> vector<int> {
        vector<int> res;
        rep(d, 4) {
            auto [dh, dw] = dir4[d];
            int nh = ch + dh;
            int nw = cw + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (target[nh][nw] != -1) {
                int revd = (d + 2) % 4;
                if ((c>>d & 1) and (target[nh][nw]>>revd & 1)) {
                    res.eb(d);
                }
            }
        }
        return res;
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
    auto dfs2 = [&](
        auto&& f, vvi& target, vector<int>& C, UnionFind& uf, int ch, int cw
    ) -> void {
        rep(d, 4) {
            if (!(target[ch][cw]>>d & 1)) continue;
            auto [dh, dw] = dir4[d];
            int nh = ch + dh;
            int nw = cw + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (target[nh][nw] != -1) continue;
            int u = gridtoid(ch, cw, W);
            int v = gridtoid(nh, nw, W);
            shuffle(ALL(bit), mt);
            rep(i, L-1) {
                if (C[bit[i]] == 0) continue;
                if (valid(target, nh, nw, bit[i])) {
                    target[nh][nw] = bit[i];
                    C[bit[i]]--;
                    uf.merge(u, v);
                    f(f, target, C, uf, nh, nw);
                    break;
                }
            }
        }
    };

    // 余りを割り振る。残さず使い切れたかどうかを返す
    auto finalize = [&](vvi& target, vector<int>& C, int sh, int sw) -> bool {
        int tmpc = 0;
        rep(ch, H) {
            rep(cw, W) {
                if (target[ch][cw] == -1) {
                    rep(tmpc, L-1, -1, -1) {
                        if (C[tmpc] == 0) continue;
                        // まずは木になるものを
                        if (check_edges(target, ch, cw, tmpc).size() == 1) {
                            target[ch][cw] = tmpc;
                            C[tmpc]--;
                            break;
                        }
                    }
                }
            }
        }
        vector<pii> rest;
        rep(ch, H) {
            rep(cw, W) {
                if (target[ch][cw] == -1) {
                    rep(tmpc, L) {
                        if (C[tmpc] == 0) continue;
                        // 閉路を作らないもの何でも
                        if (check_edges(target, ch, cw, tmpc).size() <= 1) {
                            target[ch][cw] = tmpc;
                            C[tmpc]--;
                            break;
                        }
                    }
                    if (target[ch][cw] == -1) {
                        rest.eb(ch, cw);
                    }
                }
            }
        }
        return rest.size() == 0;
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
        int h = 0, w = 0;
        rep(c, 1, L) {
            if (C[c] == 0) continue;
            auto bkc = C;
            auto target = list2d(H, W, -1);
            target[H-1][W-1] = 0;
            C[0]--;
            target[h][w] = c;
            if (valid(target, h, w, c)) {
                C[c]--;
                UnionFind uf(N);
                dfs2(dfs2, target, C, uf, h, w);
                ll use = N - sum(C);
                // debug(use);
                if (use >= N*4/5) {
                    if (finalize(target, C, h, w)) {
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
            }
            C = bkc;
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
        vector<ll> T = {
            0,
        };
        // 0からn件実施
        // int n = 10;
        // vector<ll> T;
        // rep(i, n) {
        //     T.eb(i);
        // }
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

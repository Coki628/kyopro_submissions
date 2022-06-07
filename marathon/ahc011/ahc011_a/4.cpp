/*
・先に全域木に近い状態を前計算して、それの完成を目指す。
　なんだけど、そもそも全域木に近い状態が合ってなかった…。
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

const int TL = 2500;

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
    string key;
    rep(i, H) {
        key += grid[i];
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

    auto update = [&](int ch, int cw, int nh, int nw) -> void {
        swap(nodes[ch][cw], nodes[nh][nw]);
        int i = gridtoid(ch, cw, W);
        int j = gridtoid(nh, nw, W);
        swap(key[i], key[j]);
    };

    // 位置(ch,cw)にピースcを置くことが妥当かどうか
    auto valid = [&](vvi& nodes2, int ch, int cw, int c) -> bool {
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
            if (nodes2[nh][nw] != -1) {
                // こちらからの道と逆からの道の有無が一致しているか
                int revd = (d + 2) % 4;
                if ((c>>d & 1) ^ (nodes2[nh][nw]>>revd & 1)) {
                    return false;
                }
            }
        }
        return true;
    };

    auto get_cost = [&](vector<vector<pii>>& bittonodes2) {
        auto cost = list2d(H, W, INF);
        rep(h, H) {
            rep(w, W) {
                for (auto [h2, w2] : bittonodes2[nodes[h][w]]) {
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

    auto dfs2 = [&](auto&& f, vvi& nodes2, int ch, int cw) -> void {
        for (auto [dh, dw] : dir4) {
            int nh = ch + dh;
            int nw = cw + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (nodes2[nh][nw] != -1) continue;
            rep(c, 1, L) {
                if (C[c] == 0) continue;
                if (valid(nodes2, nh, nw, c)) {
                    nodes2[nh][nw] = c;
                    C[c]--;
                    f(f, nodes2, nh, nw);
                    break;
                }
            }
        }
    };

    auto nodes2 = list2d(H, W, -1);
    vector<vector<pii>> bittonodes2(L);
    ll mxuse = 0, expcost = -1;
    rep(h, H) {
        rep(w, W) {
            auto bkc = C;
            auto nodestmp = list2d(H, W, -1);
            nodestmp[h][w] = 0;
            C[0]--;
            dfs2(dfs2, nodestmp, h, w);
            ll use = N - sum(C);
            // debug(use);
            if (use >= mxuse) {
                vector<vector<pii>> bittonodestmp(L);
                rep(h, H) {
                    rep(w, W) {
                        if (nodestmp[h][w] != -1) {
                            bittonodestmp[nodestmp[h][w]].eb(h, w);
                        }
                    }
                }
                ll cost = get_cost(bittonodestmp);
                // debug(cost);

                if (use > mxuse) {
                    mxuse = use;
                    expcost = cost;
                    bittonodes2 = bittonodestmp;
                    nodes2 = nodestmp;
                } elif (use == mxuse and cost < expcost) {
                    expcost = cost;
                    bittonodes2 = bittonodestmp;
                    nodes2 = nodestmp;
                }
            }
            C = bkc;
        }
    }

    // 予め決めた完成形を目指すように進める
    ld mxscore = 0;
    string ans, cur;
    auto elapsed = timer.get_elapse();
    int opcnt = 0;
    const int ADD = 30;
    const int LIMIT = expcost + ADD;
    set<string> visited;
    visited.insert(key);
    auto dfs3 = [&](auto&& f, int ch, int cw, int prvh, int prvw, int k) -> bool {
        ld score = calc(k);
        opcnt++;
        if (chmax(mxscore, score)) {
            ans = cur;
        }
        elapsed = timer.get_elapse();
        if (elapsed >= TL) {
            return true;
        }
        vector<pii> P;
        rep(d, 4) {
            auto [dh, dw] = dir4[d];
            int nh = ch + dh;
            int nw = cw + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (nh == prvh and nw == prvw) continue;
                update(ch, cw, nh, nw);
                if (not visited.count(key)) {
                    visited.insert(key);
                    ll cost = get_cost(bittonodes2);
                    if (cost+k < LIMIT) {
                        P.eb(cost, d);
                    }
                }
                update(ch, cw, nh, nw);
        }
        sort(ALL(P));
        for (auto [cost, d] : P) {
            auto [dh, dw] = dir4[d];
            int nh = ch + dh;
            int nw = cw + dw;
            update(ch, cw, nh, nw);
            cur.pb(lurd[d]);
            if (f(f, nh, nw, ch, cw, k+1)) {
                return true;
            }
            update(ch, cw, nh, nw);
            cur.pop_back();
        }
        return false;
    };
    dfs3(dfs3, sh, sw, -1, -1, 0);

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

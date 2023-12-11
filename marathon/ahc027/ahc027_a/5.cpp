/*
・焼きなまし
・最初に構築した木から、辺の付け外しで焼きなましをする。
　これはまだスコア計算が愚直なので、試行回数が提出ビルドでも1200回くらい。
　スコアは何とほぼ変化なし…。。。
・スコア計算を高速化。試行回数は24000回くらいに増えた。
　スコアはむしろ悪くなって1598M。
　なんだけど、順位表見るとちょい上がってたので、よく分からんな。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
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
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"
#include "string/number_format.hpp"

#include "grid/gridtoid.hpp"
#include "grid/idtogrid.hpp"
#include "heuristics/AnnealingManager.hpp"
#include "graph/cycle_detection_for_namori.hpp"
#include "numbers/arithmetic_sequence_sum.hpp"

auto solve(int testcase = -1) {
    Timer timer;
#ifdef __LOCAL
#ifdef __DEBUG
    string basedir = "tools/";
#else
    string basedir = "../tools/";
#endif
    // 入力ファイル読み込み
    string filename = basedir + "in/" + zfill(tostr(testcase), 4) + ".txt";
    freopen(filename.c_str(), "r", stdin);
    // 出力ファイル準備
    filename = basedir + "out/" + zfill(tostr(testcase), 4) + ".txt";
    ofstream ofs(filename.c_str());
    if (!ofs) {
        print("error, please check if '" + basedir + "out/' dir exists");
        exit(0);
    }
#endif
    int H, W;
    cin >> H;
    W = H;
    // 下の壁
    vector<string> walls1(H - 1);
    // 右の壁
    vector<string> walls2(H);
    int blocked[H][W][4] = {};
    // 汚れやすさ
    auto D = listnd(H, W, 0);
    // 現在の汚れ状態
    vvi curd;
    int N = H * W;
    vvi nodes1(N);
    vector<int> dtoc = {'U', 'D', 'L', 'R'};
    vector<int> ctod(100, -1);
    ctod['U'] = 0;
    ctod['D'] = 1;
    ctod['L'] = 2;
    ctod['R'] = 3;
    vv<char> mp = listnd(N, N, '*');
    string ans;
    vector<int> visited(N);
    vvi last_visited(N);
    int M = 0;
    vector<pii> edges;
    vvi uvtoe = listnd(N, N, -1);
    vector<int> used(M);
    vvi nodes2(N);
    const int TL = 1800;
    AnnealingManager am(TL, 10000, 10, true);
    int opcnt = 0, okcnt = 0;

    cin >> walls1;
    cin >> walls2;
    rep(h, H - 1) {
        rep(w, W) {
            if (walls1[h][w] == '1') {
                blocked[h][w][1] = 1;
                blocked[h + 1][w][0] = 1;
            }
        }
    }
    rep(h, H) {
        rep(w, W - 1) {
            if (walls2[h][w] == '1') {
                blocked[h][w][3] = 1;
                blocked[h][w + 1][2] = 1;
            }
        }
    }
    rep(h, H) {
        rep(w, W) {
            cin >> D[h][w];
        }
    }

    auto update2 = [&](int ct, int ch, int cw) {
        int len = ct - last_visited[ch][cw];
        ll cost = arithmetic_sequence_sum<ll>(D[ch][cw], D[ch][cw], len);
        last_visited[ch][cw] = ct + 1;
        return cost;
    };
    // スコア計算
    auto calc2 = [&](string ans) -> ll {
        int L = ans.size();
        last_visited = listnd(H, W, 0);
        int ct = 0, ch = 0, cw = 0;
        for (auto c : ans) {
            ct++;
            int d = ctod[c];
            auto [dh, dw] = dir4[d];
            int nh = ch + dh;
            int nw = cw + dw;
            update2(ct, ch, cw);
            ch = nh, cw = nw;
        }
        ll sm = 0;
        rep(h, H) {
            rep(w, W) {
                int len = ct - last_visited[h][w];
                sm -= arithmetic_sequence_sum<ll>(D[h][w], D[h][w], len);
            }
        }
        for (auto c : ans) {
            ct++;
            int d = ctod[c];
            auto [dh, dw] = dir4[d];
            int nh = ch + dh;
            int nw = cw + dw;
            sm += update2(ct, ch, cw);
            ch = nh, cw = nw;
        }
        rep(h, H) {
            rep(w, W) {
                int len = ct - last_visited[h][w];
                sm += arithmetic_sequence_sum<ll>(D[h][w], D[h][w], len);
            }
        }
        double avg = sm / (double)L;
        return round(avg);
    };

    // 元の一般グラフを構築
    rep(h, H) {
        rep(w, W) {
            int u = gridtoid(h, w, W);
            rep(d, 4) {
                if (blocked[h][w][d]) continue;
                auto [dh, dw] = dir4[d];
                int nh = h + dh;
                int nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                int v = gridtoid(nh, nw, W);
                nodes1[u].eb(v);
                mp[u][v] = dtoc[d];
                if (u < v) {
                    edges.eb(u, v);
                    uvtoe[u][v] = M;
                    uvtoe[v][u] = M;
                    M++;
                }
            }
        }
    }

    // 全域木(DFS木)を走査して初期経路とする
    auto dfs = [&](auto &&f, int u, int prv) -> void {
        visited[u] = true;
        for (auto v : nodes1[u]) {
            if (v == prv) continue;
            if (visited[v]) continue;
            ans += mp[u][v];
            f(f, v, u);
            ans += mp[v][u];
            used[uvtoe[u][v]] = true;
            nodes2[u].eb(v);
            nodes2[v].eb(u);
        }
    };
    dfs(dfs, 0, -1);

    ll mxscore = calc2(ans);
    while (timer.get_elapse() < TL) {
        // 付ける辺を決める
        int e1 = -1;
        while (e1 == -1 or used[e1]) {
            e1 = randrange(0, M);
        }
        auto nodes2bk = nodes2;
        used[e1] = true;
        auto [u1, v1] = edges[e1];
        nodes2[u1].eb(v1);
        nodes2[v1].eb(u1);

        assert(count(ALL(used), 1) == N);

        // なもり閉路を見つけてそれらを外す候補とする
        auto cycle = cycle_detection_for_namori(nodes2);
        int n = cycle.size();
        vector<int> cands;
        rep(i, n) {
            int u = cycle[i];
            int v = cycle[(i + 1) % n];
            int e = uvtoe[u][v];
            cands.eb(e);
        }
        int m = cands.size();

        // 外す辺を決める
        int e2 = cands[randrange(0, m)];
        used[e2] = false;
        auto [u2, v2] = edges[e2];
        assert(find(ALL(nodes2[u2]), v2) != nodes2[u2].end());
        assert(find(ALL(nodes2[v2]), u2) != nodes2[v2].end());
        nodes2[u2].erase(find(ALL(nodes2[u2]), v2));
        nodes2[v2].erase(find(ALL(nodes2[v2]), u2));

        string bk;
        swap(bk, ans);
        auto dfs2 = [&](auto &&f, int u, int prv) -> void {
            for (auto v : nodes2[u]) {
                if (v == prv) continue;
                ans += mp[u][v];
                f(f, v, u);
                ans += mp[v][u];
            }
        };
        dfs2(dfs2, 0, -1);
        ll score = calc2(ans);
        if (am.judge(mxscore, score, timer.get_elapse())) {
            mxscore = score;
            okcnt++;
        } else {
            used[e1] = false;
            used[e2] = true;
            ans = move(bk);
            nodes2 = nodes2bk;
        }
        opcnt++;
    }
    debug(opcnt, okcnt);

#ifdef __LOCAL
    ofs << ans << endl;
#else
    print(ans);
#endif

    return mxscore;
}

// テスト番号指定
vector<int> gen_cases1(const vector<int> &T) {
    return T;
}

// sからn件実施
vector<int> gen_cases2(int s, int n) {
    vector<int> T;
    rep(i, s, s + n) {
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
    return vector<int>(T.begin(), T.begin() + n);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

#ifdef __LOCAL
    // テスト番号指定
    // auto T = gen_cases1({0});
    // sからn件実施
    auto T = gen_cases2(0, 20);
    // [s,t)を実施
    // auto T = gen_cases3(0, 100);
    // [s,t)の範囲でランダムにn件実施
    // auto T = gen_cases4(0, 100, 20);

    ll totalscore = 0;
    for (int t : T) {
        cout << "case #" << t << " start" << endl;
        auto score = solve(t);
        cout << "case #" << t << " score: ";
        print(number_format(score));
        cout << endl;
        totalscore += score;
    }
    cout << "total score: ";
    print(number_format(totalscore));
#else
    solve();
#endif

    return 0;
}

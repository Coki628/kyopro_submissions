/*
・ルールベースで貪欲
・初期経路を作った後は「今最も汚れている場所」へ向かうことを繰り返す。
　スコアは3000M超で案外全然ダメだった…。
　ここから次に向かう場所の条件改善していけないだろうか。
・改善した。「汚れ具合/距離」みたいな式で優先度を決めた。
　これだと程よく近くの汚れ気味なマスを優先してくれる。
　色々微調整試した結果、100を掛けてある。スコアは925M。
・これならそもそも最初のDFS1周やらなくても良くない？
　と外してみた。すると意外にもちょい下がって936M。
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
#include "datastructure/LazySegmentTree.hpp"
#include "graph/get_route.hpp"

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
    int N = H * W;
    vector<int> D2(N);
    vvi nodes1(N);
    vector<char> dtoc = {'U', 'D', 'L', 'R'};
    vector<int> ctod(100, -1);
    ctod['U'] = 0;
    ctod['D'] = 1;
    ctod['L'] = 2;
    ctod['R'] = 3;
    vv<char> mp = listnd(N, N, '*');
    string ans;
    vector<int> visited(N);
    vvi last_visited = listnd(N, N, 0);
    int M = 0;
    vector<pii> edges;
    vvi uvtoe = listnd(N, N, -1);
    vector<int> etod;
    const int TL = 1800;

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
    rep(i, N) {
        auto [h, w] = idtogrid(i, W);
        D2[i] = D[h][w];
    }

    // 汚れ具合を更新しながら最もひどい所を見つけるセグ木
    struct Node {
        int t, id;
    };
    auto f = [&D2](const Node &a, const Node &b) -> Node {
        if (a.id == -1) return b;
        if (b.id == -1) return a;
        if (a.t * D2[a.id] > b.t * D2[b.id]) {
            return a;
        } else if (a.t * D2[a.id] < b.t * D2[b.id]) {
            return b;
        } else if (D2[a.id] >= D2[b.id]) {
            return a;
        } else {
            return b;
        }
    };
    auto g = [](const Node &a, ll b) -> Node {
        return { a.t + b, a.id };
    };
    auto h = [](ll a, ll b) -> ll { return a + b; };
    const Node T = {0, -1};
    const ll E = 0;
    auto seg = get_lazy_segment_tree(N, f, g, h, T, E);
    rep(i, N) {
        seg.set(i, {0, (int)i});
    }
    seg.build();

    auto update2 = [&](int ct, int ch, int cw) {
        int len = ct - last_visited[ch][cw];
        ll cost = arithmetic_sequence_sum<ll>(D[ch][cw], D[ch][cw], len);
        last_visited[ch][cw] = ct + 1;
        int i = gridtoid(ch, cw, W);
        seg.update(0, N, 1);
        seg.update(i, -seg[i].t);
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
                    etod.eb(d);
                    assert(d == 1 or d == 3);
                    M++;
                }
            }
        }
    }

    // 全域木(DFS木)を走査して初期経路とする
    // auto dfs = [&](auto &&f, int u, int prv) -> void {
    //     visited[u] = true;
    //     auto [ch, cw] = idtogrid(u, W);
    //     for (auto v : nodes1[u]) {
    //         if (v == prv) continue;
    //         if (visited[v]) continue;
    //         auto [nh, nw] = idtogrid(v, W);
    //         ans += mp[u][v];
    //         update2(ans.size(), nh, nw);
    //         f(f, v, u);
    //         ans += mp[v][u];
    //         update2(ans.size(), ch, cw);
    //     }
    // };
    // dfs(dfs, 0, -1);

    // 全頂点対で復元配列を前計算
    auto prv = listnd(N, N, -1);
    vvl dist(N);
    rep(i, N) {
        auto bfs = [&](const vvi &nodes, const vector<int> &src) {
            int N = nodes.size();
            vector<ll> res(N, INF);
            queue<int> que;
            for (int s : src) {
                res[s] = 0;
                que.push(s);
            }
            while (!que.empty()) {
                int u = que.front();
                que.pop();
                for (auto v : nodes[u]) {
                    if (chmin(res[v], res[u] + 1)) {
                        que.push(v);
                        prv[i][v] = u;
                    }
                }
            }
            return res;
        };
        dist[i] = bfs(nodes1, {(int)i});
    }

    auto find_next = [&](int u) {
        auto [ch, cw] = idtogrid(u, W);
        vector<double> score(N, -1);
        rep(v, N) {
            if (v == u) continue;
            auto [nh, nw] = idtogrid(v, W);
            double di = dist[u][v];
            double a = seg[v].t * D2[v];
            score[v] = a * 100 / di;
            // 未訪問優先補正
            if (last_visited[nh][nw] == 0) {
                score[v] += 10;
            }
        }
        int nxt = max_element(ALL(score)) - score.begin();
        return nxt;
    };

    // とりあえず帰り道用に暫定で(H + W) * 3としておく
    int LIMIT = 1e5 - (H + W) * 3;
    int u = 0;
    while (ans.size() < LIMIT and timer.get_elapse() < TL) {
        // auto [mxt, v] = seg.query(0, N);
        int v = find_next(u);
        assert(v != u);
        auto route = get_route(prv[u], u, v);
        assert(route.size() >= 2);
        rep(i, route.size() - 1) {
            int a = route[i];
            int b = route[i + 1];
            int d = etod[uvtoe[a][b]];
            // 戻り向き
            if (a > b) d--;
            ans += dtoc[d];
            auto [nh, nw] = idtogrid(b, W);
            update2(ans.size(), nh, nw);
        }
        u = route.back();
    }
    // 帰り
    auto route = get_route(prv[u], u, 0);
    rep(i, route.size() - 1) {
        int a = route[i];
        int b = route[i + 1];
        int d = etod[uvtoe[a][b]];
        // 戻り向き
        if (a > b) d--;
        ans += dtoc[d];
        auto [nh, nw] = idtogrid(b, W);
        update2(ans.size(), nh, nw);
    }

    assert(ans.size() <= 1e5);
    ll mxscore = calc2(ans);

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

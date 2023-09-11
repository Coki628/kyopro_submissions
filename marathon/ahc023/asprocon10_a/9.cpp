/*
・方針転換。BFSで全域木を構築して、葉から順に埋めてく感じ。
　ちょっと良くなった。2966万。
・操作全体の実行時間がさほど長くなかったので、
　全域木の辺の張り方をランダムにして全行程を2秒めいっぱいまで試した。
　これで3131万。30M乗ったね。
・全行程終わった後、隙間を埋めるように残った作物を入れていくことにした。
　グリッド*時系列の3次元空間上に細長い棒を差し込むイメージで、入れられる場所を探していく。
　これで3641万！結構上がってきた。
・次の段階のために整えた。
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
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"
#include "string/number_format.hpp"

#include "grid/gridtoid.hpp"
#include "grid/idtogrid.hpp"
#include "graph/HeavyLightDecomposition.hpp"
#include "datastructure/SegmentTree.hpp"

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
    int T = 100, H = 20, W = 20;
    int sh, sw = 0;
    cin >> T >> H >> W >> sh;
    // int blocked[H][W][4] = {};
    auto blocked = listnd(H, W, 4, 0);
    // 下の境界
    rep(h, H - 1) {
        rep(w, W) {
            char tmp;
            cin >> tmp;
            blocked[h][w][1] = tmp - '0';
            blocked[h + 1][w][0] = tmp - '0';
        }
    }
    // 右の境界
    rep(h, H) {
        rep(w, W - 1) {
            char tmp;
            cin >> tmp;
            blocked[h][w][3] = tmp - '0';
            blocked[h][w + 1][2] = tmp - '0';
        }
    }
    rep(h, H) {
        blocked[h][0][2] = 1;
        blocked[h][W - 1][3] = 1;
    }
    rep(w, W) {
        blocked[0][w][0] = 1;
        blocked[H - 1][w][1] = 1;
    }
    int K;
    cin >> K;
    vector<ll> S(K), D(K);
    rep(k, K) {
        cin >> S[k] >> D[k];
    }
    // 作物の優先度
    vector<array<ll, 3>> agris;
    rep(k, K) {
        agris.pb({S[k], -D[k], k});
    }
    // 左端ソート、降順右端ソート
    sort(ALL(agris));
    int N = H * W;

    // スコア計算
    auto calc = [&](vector<array<ll, 4>>& ans) {
        ll sm = 0;
        for (auto [k, h, w, t] : ans) {
            k--;
            sm += D[k] - S[k] + 1;
        }
        return 1e6 * sm / (H * W * T);
    };

    const int TL = 1000;
    ll mxscore = 0;
    vector<array<ll, 4>> ans;
    vector<int> perm = {0, 1, 2, 3};
    int opcnt = 0;
    vvi nodes(N);
    vector<int> abandoned;
    vector<pii> distorder;
    int root = gridtoid(sh, sw, W);

    while (timer.get_elapse() < TL) {
        vvi curnodes(N);
        // グリッドBFS：出口セルからの距離
        auto bfs = [&](const vector<pii> &src, bool struct_tree = false) {
            auto res = list2d(H, W, INF);
            queue<pii> que;
            for (auto [h, w] : src) {
                que.push({h, w});
                res[h][w] = 0;
            }
            while (!que.empty()) {
                ll h, w;
                tie(h, w) = que.front();
                que.pop();
                // 辺の張り方をランダムにする
                shuffle(ALL(perm), mt);
                rep(i, 4) {
                    int d = perm[i];
                    int revd = d % 2 == 0 ? d + 1 : d - 1;
                    auto [dh, dw] = dir4[d];
                    int nh = h + dh;
                    int nw = w + dw;
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    if (blocked[h][w][d]) continue;
                    if (res[nh][nw] == INF) {
                        // 全域木の構築
                        if (struct_tree) {
                            int u = gridtoid(h, w, W);
                            int v = gridtoid(nh, nw, W);
                            curnodes[u].eb(v);
                            // curnodes[v].eb(u);
                        }
                        res[nh][nw] = res[h][w] + 1;
                        que.push({nh, nw});
                    }
                }
            }
            return res;
        };
        auto dist = bfs({{sh, sw}}, true);
        // マスを距離遠い順で並べておく
        vector<pii> curdistorder;
        rep(u, N) {
            auto [h, w] = idtogrid(u, W);
            curdistorder.eb(dist[h][w], u);
        }
        sort(curdistorder.rbegin(), curdistorder.rend());
        HeavyLightDecomposition curhld(curnodes, root);
        // seg[hld.in[u]] := uに今割り当てられている作物kのD[k]
        auto segmn = get_segment_tree(N, [](ll a, ll b) { return min(a, b); }, INF);
        auto segmx = get_segment_tree(N, [](ll a, ll b) { return max(a, b); }, -INF);

        auto grid_used = listnd(H, W, 0);
        // 未使用セル
        priority_queue<array<ll, 3>> que_unused;
        // B[h,w] := セル(h,w)の優先度
        vector<ll> B(N);
        vector<ll> graphtok(N, -1);

        auto add_agri = [&](int h, int w, int k) {
            grid_used[h][w] = 1;
            int u = gridtoid(h, w, W);
            graphtok[u] = k;
            segmn.update(curhld.in[u], D[k]);
            segmx.update(curhld.in[u], D[k]);
        };
        auto remove_agri = [&](int h, int w) {
            grid_used[h][w] = 0;
            int u = gridtoid(h, w, W);
            graphtok[u] = -1;
            segmn.update(curhld.in[u], INF);
            segmx.update(curhld.in[u], -INF);
        };
        // 周囲の状況によって重み付け
        auto get_wait = [&](int h, int w) {
            ll u = gridtoid(h, w, W);
            return curhld.dep[u];
        };
        auto is_applicable = [&](int h, int w, int c) {
            int u = gridtoid(h, w, W);
            // ここより先で取れる作物の最小収穫時が自身より大きい(遅い)
            ll mn = segmn.query(curhld.in[u], curhld.out[u]);
            // ここより手前で取れる作物の最大収穫時(1つもあってはいけない)
            ll mx = curhld.query(u, root, -INF, [&](ll a, ll b) { return segmx.query(a, b); }, [](ll a, ll b) { return max(a, b); });
            return mx <= -INF and c <= mn;
        };

        rep(h, H) {
            rep(w, W) {
                ll i = gridtoid(h, w, W);
                B[i] = get_wait(h, w);
                que_unused.push({B[i], dist[h][w], gridtoid(h, w, W)});
            }
        }

        // A[i] := K[i]をどこで使ってるか
        vector<int> A(K, -1);
        vvi adj(T + 1);
        rep(k, K) {
            adj[D[k]].eb(k);
        }

        vector<array<ll, 4>> curans;
        vector<int> curabandoned;
        ll curk = 0;
        rep(t, 1, T + 1) {
            vector<array<ll, 3>> tmp;
            while (curk < K and que_unused.size()) {
                auto [wa, di, i] = que_unused.top();
                auto [h, w] = idtogrid(i, W);
                auto [_, __, k] = agris[curk];
                if (S[k] < t) {
                    // この作物はもう間に合わない
                    curabandoned.pb(k);
                    curk++;
                    continue;
                }
                que_unused.pop();
                if (is_applicable(h, w, D[k])) {
                    add_agri(h, w, k);
                    A[k] = i;
                    curans.pb({k + 1, h, w, t});
                    curk++;
                } else {
                    remove_agri(h, w);
                    // このマスはこの日には使わない
                    tmp.pb({wa, di, i});
                }
            }
            for (auto arr : tmp) {
                que_unused.push(arr);
            }
            // 収穫
            for (auto k : adj[t]) {
                if (A[k] != -1) {
                    auto [h, w] = idtogrid(A[k], W);
                    remove_agri(h, w);
                    ll i = gridtoid(h, w, W);
                    que_unused.push({B[i], dist[h][w], A[k]});
                    A[k] = -1;
                }
            }
        }

        ll score = calc(curans);
        if (chmax(mxscore, score)) {
            ans = curans;
            nodes = curnodes;
            abandoned = curabandoned;
            distorder = curdistorder;
        }
        opcnt++;
    }
#ifdef __LOCAL
    debug(mxscore);
    debug(opcnt);
#endif

    HeavyLightDecomposition hld(nodes, root);
    auto used3d = listnd(T + 1, N, 0);
    auto plant3d = listnd(T + 1, N, 0);
    auto harvest3d = listnd(T + 1, N, 0);
    for (auto& [k, h, w, t] : ans) {
        k--;
        int u = gridtoid(h, w, W);
        // 埋まっているセルの記録
        rep(tt, t, D[k] + 1) {
            used3d[tt][u] = true;
        }
        plant3d[t][u] = true;
        harvest3d[D[k]][u] = true;
        k++;
    }
    for (auto& [k, h, w, t] : ans) {
        k--;
        int u = gridtoid(h, w, W);
        // 早めに植えてしまっている所をギリギリまで遅らせる
        rep(tt, S[k], t, -1) {
            // この時点で植えに行けるか祖先チェック
            bool ok = true;
            int cur = u;
            while (cur != root) {
                if (used3d[tt][cur]) {
                    ok = false;
                    break;
                }
                cur = hld.par[cur];
            }
            if (used3d[tt][cur]) {
                ok = false;
            }
            if (ok) {
                rep(ttt, t, tt) {
                    used3d[ttt][u] = false;
                }
                plant3d[tt][u] = true;
                plant3d[t][u] = false;
                t = tt;
                break;
            }
        }
        k++;
    }

    for (auto k : abandoned) {
        int t = S[k];
        // 遠いセル優先でやる
        for (auto [_, u] : distorder) {
            bool ok = true;
            // まず大前提として必要な期間そのセルが空いているか
            rep(tt, t, D[k] + 1) {
                if (used3d[tt][u]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                // 次に各時点で木を辿って状態を確認する
                bool ok1 = true, ok2 = true;
                rep(tt, t, D[k] + 1) {
                    // 部分木
                    auto dfs = [&](auto&& f, int u) -> bool {
                        // 時間経過中に「植える瞬間/収穫の瞬間」があるとアウト
                        if (tt > t and plant3d[tt][u] or tt < D[k] and harvest3d[tt][u]) {
                            ok1 = false;
                            return false;
                        }
                        for (auto v : nodes[u]) {
                            if (!f(f, v)) {
                                return false;
                            }
                        }
                        return true;
                    };
                    dfs(dfs, u);
                    if (not ok1) break;
                }
                // 祖先(植える時と収穫時だけでいいはず)
                for (auto tt : vector<ll>{t, D[k]}) {
                    int cur = u;
                    while (cur != root) {
                        if (used3d[tt][cur]) {
                            ok2 = false;
                            break;
                        }
                        cur = hld.par[cur];
                    }
                    if (used3d[tt][cur]) {
                        ok2 = false;
                    }
                }
                if (ok1 and ok2) {
                    // 植える
                    rep(tt, t, D[k] + 1) {
                        used3d[tt][u] = true;
                    }
                    plant3d[t][u] = true;
                    harvest3d[D[k]][u] = true;
                    auto [h, w] = idtogrid(u, W);
                    ans.pb({k + 1, h, w, t});
                    break;
                }
            }
        }
    }
    mxscore = calc(ans);

#ifdef __LOCAL
    debug(mxscore);
    debug(timer.get_elapse());
#endif



#ifdef __LOCAL
    ofs << ans.size() << endl;
    for (auto [k, h, w, t] : ans) {
        ofs << k << ' ' << h << ' ' << w << ' ' << t << endl;
    }
    debug(ans.size());
    debug(timer.get_elapse());
#else
    print(ans.size());
    print(ans, '\n');
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
    // auto T = gen_cases1({58, 81});
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

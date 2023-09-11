/*
・10までの方針に11で作った山登りを追加。
　こっちだと10～20回程度の追加は見込めた。とはいえ少ないけど…。
　少しだけ伸びてこれが3656万。
・山登りでの操作を普通に2点スワップにした。ちょっと下がって3645万。。
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
#include "datastructure/BIT.hpp"

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
    int dummy, sh, sw = 0;
    cin >> dummy >> dummy >> dummy >> sh;
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
    vector<pii> distorder;
    vector<int> abandoned;
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
                que_unused.push({get_wait(h, w), dist[h][w], gridtoid(h, w, W)});
            }
        }

        vector<int> curA(K, -1);
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
                    curA[k] = i;
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
                if (curA[k] != -1) {
                    auto [h, w] = idtogrid(curA[k], W);
                    remove_agri(h, w);
                    ll i = gridtoid(h, w, W);
                    que_unused.push({get_wait(h, w), dist[h][w], curA[k]});
                }
            }
        }

        ll score = calc(curans);
        if (chmax(mxscore, score)) {
            ans = curans;
            nodes = curnodes;
            distorder = curdistorder;
            abandoned = curabandoned;
        }
        opcnt++;
    }
#ifdef __LOCAL
    debug(mxscore);
    debug(opcnt);
    debug(abandoned.size());
#endif

    HeavyLightDecomposition hld(nodes, root);
    vector<BIT<int>> useda3d(T + 1, BIT<int>{N});
    vector<BIT<int>> usedb3d(T + 1, BIT<int>{N});
    vector<BIT<int>> plant3d(T + 1, BIT<int>{N});
    vector<BIT<int>> harvest3d(T + 1, BIT<int>{N});
    // A[i] := K[i]をどのセルで使ってるか
    vector<int> A(K, -1);
    // B[i] := K[i]の格納されているansのindex
    vector<int> B(K, -1);
    // S2[k] := 作物kを植えた時刻
    vector<int> S2(K, -1);

    // 作物kを時刻tでアサインできるか
    auto is_assignable = [&](int k, int t) -> int {
        // 遠いセル優先でやる
        for (auto [_, u] : distorder) {
            if (useda3d[t][hld.in[u]] != 0 or usedb3d[t][hld.in[u]] != 0) {
                continue;
            }
            // 各時点で木を辿って状態を確認する
            int ok1 = true, ok2 = true;
            rep(tt, t, D[k] + 1) {
                // 部分木
                // 時間経過中に「植える瞬間/収穫の瞬間」があるとアウト
                if (tt > t) {
                    ok1 &= !plant3d[tt].query(hld.in[u], hld.out[u]);
                }
                if (tt < D[k]) {
                    ok1 &= !harvest3d[tt].query(hld.in[u], hld.out[u]);
                }
                if (not ok1) {
                    break;
                }
            }
            // 祖先(植える時と収穫時だけでいいはず)
            if (ok1) {
                ok2 &= !hld.query(u, root, 0, [&](int a, int b) { return useda3d[t].query(a, b); }, [](ll a, ll b) { return a + b; });
                ok2 &= !hld.query(u, root, 0, [&](int a, int b) { return usedb3d[D[k]].query(a, b); }, [](ll a, ll b) { return a + b; });
            }
            if (ok1 and ok2) {
                return u;
            }
        }
        return -1;
    };
    auto add_k = [&](int k, int t = -1) -> int {
        // 第2引数なし
        if (t == -1) {
            t = S[k];
        }
        int u = is_assignable(k, t);
        if (u != -1) {
            A[k] = u;
            S2[k] = t;
            rep(t, S2[k] + 1, D[k] + 1) {
                useda3d[t].add(hld.in[u], 1);
            }
            rep(t, S2[k], D[k]) {
                usedb3d[t].add(hld.in[u], 1);
            }
            plant3d[S2[k]].add(hld.in[u], 1);
            harvest3d[D[k]].add(hld.in[u], 1);
        }
        return u;
    };
    auto remove_k = [&](int k) -> void {
        assert(S2[k] != -1);
        assert(A[k] != -1);
        int u = A[k];
        rep(t, S2[k] + 1, D[k] + 1) {
            assert(useda3d[t][hld.in[u]] == 1);
            useda3d[t].add(hld.in[u], -1);
        }
        rep(t, S2[k], D[k]) {
            assert(usedb3d[t][hld.in[u]] == 1);
            usedb3d[t].add(hld.in[u], -1);
        }
        assert(plant3d[S2[k]][hld.in[u]] == 1);
        plant3d[S2[k]].add(hld.in[u], -1);
        assert(harvest3d[D[k]][hld.in[u]] == 1);
        harvest3d[D[k]].add(hld.in[u], -1);
        A[k] = -1;
        S2[k] = -1;
    };

    int M = ans.size();
    rep(i, M) {
        auto [k, h, w, t] = ans[i];
        k--;
        int u = gridtoid(h, w, W);
        // 埋まっているセルの記録
        rep(tt, t + 1, D[k] + 1) {
            useda3d[tt].add(hld.in[u], 1);
        }
        rep(tt, t, D[k]) {
            usedb3d[tt].add(hld.in[u], 1);
        }
        plant3d[t].add(hld.in[u], 1);
        harvest3d[D[k]].add(hld.in[u], 1);
        A[k] = u;
        B[k] = i;
        S2[k] = t;
        k++;
    }

    for (auto& [k, h, w, t] : ans) {
        k--;
        int u = gridtoid(h, w, W);
        // 早めに植えてしまっている所をギリギリまで遅らせる
        rep(tt, S[k], t, -1) {
            // この時点で植えに行けるか祖先チェック
            int ok = !hld.query(u, root, 0, [&](int a, int b) { return useda3d[tt].query(a, b); }, [](ll a, ll b) { return a + b; });
            if (ok) {
                rep(ttt, t + 1, tt + 1) {
                    assert(useda3d[ttt][hld.in[u]] == 1);
                    useda3d[ttt].add(hld.in[u], -1);
                }
                rep(ttt, t, tt) {
                    assert(usedb3d[ttt][hld.in[u]] == 1);
                    usedb3d[ttt].add(hld.in[u], -1);
                }
                plant3d[tt].add(hld.in[u], 1);
                plant3d[t].add(hld.in[u], -1);
                t = tt;
                S2[k] = tt;
                break;
            }
        }
        k++;
    }

    int success1 = 0;
    for (auto k : abandoned) {
        int u = add_k(k);
        if (u != -1) {
            auto [h, w] = idtogrid(u, W);
            ans.pb({k + 1, h, w, S[k]});
            B[k] = M;
            M++;
            success1++;
        }
    }
    mxscore = calc(ans);

#ifdef __LOCAL
    debug(success1);
    debug(mxscore);
#endif

    const int TL2 = 1800;
    int opcnt2 = 0, success2 = 0;
    int coef = 1e6 / (H * W * T);
    while (timer.get_elapse() < TL2) {
        int k1, k2;
        while (1) {
            k1 = randrange(0, K);
            k2 = randrange(0, K);
            if (B[k2] != -1) {
                swap(k1, k2);
            }
            if (B[k1] != -1 and B[k2] == -1) {
                break;
            }
        }

        // スコア伸びないならやる意味なし
        int score1 = coef * (D[k1] - S[k1] + 1);
        int score2 = coef * (D[k2] - S[k2] + 1);
        if (score1 >= score2) {
            continue;
        }

        int s2bk = S2[k1];
        remove_k(k1);
        int v = add_k(k2);
        if (v != -1) {
            success2++;
            mxscore += (score2 - score1);
            // 削除済みとする
            ans[B[k1]][0] = -1;
            B[k1] = -1;
            auto [h2, w2] = idtogrid(v, W);
            ans.pb({k2 + 1, h2, w2, S2[k2]});
            B[k2] = M;
            M++;
        } else {
            int u = add_k(k1, s2bk);
            assert(u != -1);
            auto [h1, w1] = idtogrid(u, W);
            ans[B[k1]][1] = h1;
            ans[B[k1]][2] = w1;
        }
        opcnt2++;
    }
    // 削除済を整理
    auto tmpans = ans;
    ans.clear();
    rep(i, M) {
        auto [k, h, w, t] = tmpans[i];
        if (k != -1) {
            ans.pb({k, h, w, t});
        }
    }

#ifdef __LOCAL
    debug(opcnt2);
    debug(success2);
    debug(mxscore);
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

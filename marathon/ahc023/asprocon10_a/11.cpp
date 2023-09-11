/*
・山登りのベースを作ったけどマジで大変だった。添字とかバグとの闘いだった…。
　そしてこの「k1を引っこ抜いてからk2と両方入れる」の方針だとほぼ成功しないことが判明。。
　別の更新方法を検討する必要がある。
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
    vector<pii> distorder;
    int root = gridtoid(sh, sw, W);
    vector<BIT<int>> useda3d(T + 1, BIT<int>{N});
    vector<BIT<int>> usedb3d(T + 1, BIT<int>{N});
    vector<BIT<int>> plant3d(T + 1, BIT<int>{N});
    vector<BIT<int>> harvest3d(T + 1, BIT<int>{N});
    HeavyLightDecomposition hld(nodes, root);
    // A[i] := K[i]をどのセルで使ってるか
    vector<int> A(K, -1);
    // B[i] := K[i]の格納されているansのindex
    vector<int> B(K, -1);
    // S2[k] := 作物kを植えた時刻
    vector<int> S2(K, -1);
    vector<int> assigned(K);
    vector<pii> rangeorder;
    rep(i, K) {
        rangeorder.eb(D[i] - S[i], i);
    }
    sort(rangeorder.rbegin(), rangeorder.rend());

    // 作物kを時刻tでアサインできるか
    auto is_assignable = [D, root](
        int k,
        int t,
        vector<pii>& distorder,
        vector<BIT<int>>& useda3d,
        vector<BIT<int>>& usedb3d,
        vector<BIT<int>>& plant3d,
        vector<BIT<int>>& harvest3d,
        HeavyLightDecomposition& hld
    ) -> int {
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
    auto add_k = [S, D, is_assignable](
        int k,
        vector<pii>& distorder,
        vector<BIT<int>>& useda3d,
        vector<BIT<int>>& usedb3d,
        vector<BIT<int>>& plant3d,
        vector<BIT<int>>& harvest3d,
        HeavyLightDecomposition& hld,
        vector<int>& A,
        vector<int>& S2,
        int t = -1
    ) -> int {
        // 第2引数なし
        if (t == -1) {
            t = S[k];
        }
        int u = is_assignable(k, t, distorder, useda3d, usedb3d, plant3d, harvest3d, hld);
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
    auto remove_k = [D](
        int k,
        vector<BIT<int>>& useda3d,
        vector<BIT<int>>& usedb3d,
        vector<BIT<int>>& plant3d,
        vector<BIT<int>>& harvest3d,
        HeavyLightDecomposition& hld,
        vector<int>& A,
        vector<int>& S2
    ) -> void {
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
        vector<BIT<int>> curuseda3d(T + 1, BIT<int>{N});
        vector<BIT<int>> curusedb3d(T + 1, BIT<int>{N});
        vector<BIT<int>> curplant3d(T + 1, BIT<int>{N});
        vector<BIT<int>> curharvest3d(T + 1, BIT<int>{N});
        vector<int> curA(K, -1);
        vector<int> curB(K, -1);
        vector<int> curS2(K, -1);
        vector<int> curassigned(K);
        vector<array<ll, 4>> curans;

        // 期間長い順で貪欲割り当て
        for (auto [_, k] : rangeorder) {
            int u = add_k(k, curdistorder, curuseda3d, curusedb3d, curplant3d, curharvest3d, curhld, curA, curS2);
            if (u != -1) {
                auto [h, w] = idtogrid(u, W);
                curB[k] = curans.size();
                curans.pb({k + 1, h, w, S[k]});
            }
        }

        ll score = calc(curans);
        if (chmax(mxscore, score)) {
            ans = curans;
            nodes = curnodes;
            hld = curhld;
            distorder = curdistorder;
            useda3d = curuseda3d;
            usedb3d = curusedb3d;
            plant3d = curplant3d;
            harvest3d = curharvest3d;
        }
        opcnt++;
    }
#ifdef __LOCAL
    debug(mxscore);
    debug(opcnt);
#endif

    int M = ans.size();
    rep(i, M) {
        auto [k, h, w, t] = ans[i];
        k--;
        int u = gridtoid(h, w, W);
        A[k] = u;
        B[k] = i;
        S2[k] = t;
        k++;
    }

    const int TL2 = 1800;
    int opcnt2 = 0, success2 = 0;
    while (timer.get_elapse() < TL2) {
        // k1を引っこ抜いてからk2と両方入れる
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

        remove_k(k1, useda3d, usedb3d, plant3d, harvest3d, hld, A, S2);
        int v = add_k(k2, distorder, useda3d, usedb3d, plant3d, harvest3d, hld, A, S2);
        if (v != -1) {
            int u = add_k(k1, distorder, useda3d, usedb3d, plant3d, harvest3d, hld, A, S2);
            if (u != -1) {
                // OK!
                success2++;
                int i1 = B[k1];
                auto [h1, w1] = idtogrid(u, W);
                auto [h2, w2] = idtogrid(v, W);
                ans[i1] = {k1 + 1, h1, w1, S2[k1]};
                ans.pb({k2 + 1, h2, w2, S2[k2]});
                B[k2] = M;
                M++;
            } else {
                remove_k(k2, useda3d, usedb3d, plant3d, harvest3d, hld, A, S2);
                int u = add_k(k1, distorder, useda3d, usedb3d, plant3d, harvest3d, hld, A, S2);
                assert(u != -1);
                auto [h1, w1] = idtogrid(u, W);
                ans[B[k1]][1] = h1;
                ans[B[k1]][2] = w1;
            }
        } else {
            int u = add_k(k1, distorder, useda3d, usedb3d, plant3d, harvest3d, hld, A, S2);
            assert(u != -1);
            auto [h1, w1] = idtogrid(u, W);
            ans[B[k1]][1] = h1;
            ans[B[k1]][2] = w1;
        }
        opcnt2++;
    }
    mxscore = calc(ans);

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

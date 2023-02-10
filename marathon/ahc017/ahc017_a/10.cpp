/*
・パスがユークリッド距離をベースに作られていることが分かったので、
　一番近くにある辺が遠いやつ優先みたいなのを動的更新していこうとしたけど、
　毎回再計算してソートするの重すぎていくつかTL間に合わない感じ…。
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

#include "common/sum.hpp"
#include "common/max.hpp"
#include "common/sample.hpp"
#include "graph/UnionFind.hpp"

#include "acl/mincostflow.hpp"

const int MX = 1000000000;

// ダイクストラ復元付き
template<typename T>
pair<vector<T>, vector<int>> dijkstra(const vector<vector<pair<int, T>>> &nodes, int src, int goal = -1) {
    int N = nodes.size();
    vector<T> res(N, MX);
    vector<int> prv(N, -1);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
    res[src] = 0;
    que.push({0, src});

    while (que.size()) {
        auto [dist, u] = que.top();
        que.pop();
        if (u == goal) return {res, prv};
        if (res[u] < dist) continue;
        for (auto [v, cost] : nodes[u]) {
            if (chmin(res[v], dist + cost)) {
                prv[v] = u;
                que.push({dist + cost, v});
            }
        }
    }
    return {res, prv};
}

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
    const int TL = 4000;
    int N, M, D, K;
    cin >> N >> M >> D >> K;
    vector<vector<pii>> nodes(N);
    auto G = listnd(N, N, MX);
    auto ptoe = listnd(N, N, 0);
    vector<pii> etop(M);
    vector<int> cost(M);
    vector<ll> scores(D + 1);
    vector<int> edgecnt(N);
    vvi adj(N);
    rep(e, M) {
        ll u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        nodes[u].eb(v, w);
        nodes[v].eb(u, w);
        // 同じ辺ペアが2回来ないことは保証されてたら嬉しい
        assert(G[u][v] == MX);
        G[u][v] = w;
        G[v][u] = w;
        ptoe[u][v] = e;
        ptoe[v][u] = e;
        // u < v は制約で保証
        etop[e] = {u, v};
        cost[e] = w;
        edgecnt[u]++;
        edgecnt[v]++;
    }
    // debug(edgecnt);

    // 描画用頂点座標
    vector<int> X(N), Y(N);
    rep(i, N) {
        cin >> X[i] >> Y[i];
    }

    // template<typename T>
    // using vv = vector<vector<T>>;

    vector<int> pathcost(M);
    // 現在の連結状態での全点対距離取得
    auto get_dist_all = [N, ptoe, &pathcost](vector<vector<pii>> &nodes, bool restore = false) -> vvi {
        vvi res = listnd(N, N, 0);
        rep(u, N) {
            vector<int> prv(N);
            tie(res[u], prv) = dijkstra(nodes, u);
            if (restore) {
                rep(v, N) {
                    if (v == u) continue;
                    int cur = v;
                    while (prv[cur] != -1) {
                        int nxt = prv[cur];
                        int e = ptoe[cur][nxt];
                        pathcost[e]++;
                        cur = nxt;
                    }
                }
            }
        }
        return res;
    };
    vvi base = get_dist_all(nodes, true);
    // 計算
    auto calc = [D, N](const vector<ll> &scores) -> ll {
        return round(1000 * (double)sum(scores) / (D * (N * (N - 1) / 2)));
    };
    // 現在のグラフに対してスコア計算
    auto sum_day = [N, base](const vvi &G) -> ll {
        ll sm = 0;
        rep(u, N) {
            rep(v, u + 1, N) {
                assert(G[u][v] == G[v][u]);
                assert(G[u][v] - base[u][v] >= 0);
                assert(G[u][v] - base[u][v] <= MX);
                sm += G[u][v] - base[u][v];
            }
        }
        return sm;
    };
    // 1日のシミュレート
    auto simulate = [etop, cost, sum_day, get_dist_all](
                        int d,
                        vector<vector<pii>> &nodes,
                        const vvi &adj
                    ) -> ll {
        for (auto e : adj[d]) {
            auto [u, v] = etop[e];
            nodes[u].erase(find(ALL(nodes[u]), mkp(v, cost[e])));
            nodes[v].erase(find(ALL(nodes[v]), mkp(u, cost[e])));
        }
        ll res = sum_day(get_dist_all(nodes));
        for (auto e : adj[d]) {
            auto [u, v] = etop[e];
            nodes[u].eb(v, cost[e]);
            nodes[v].eb(u, cost[e]);
        }
        return res;
    };
    // 全日程のシミュレート
    auto simulate_all = [M, D, simulate, calc](
                            vector<vector<pii>> &nodes,
                            const vector<int> ans,
                            vector<ll> &scores,
                            vvi &adj
                        ) -> ll {
        rep(e, M) {
            adj[ans[e]].eb(e);
        }
        rep(d, 1, D + 1) {
            scores[d] = simulate(d, nodes, adj);
        }
        return calc(scores);
    };

    auto recalc_cost = [M, X, Y, etop](const int added, vector<array<int, 4>> &edges) -> void {
        int e1 = added;
        auto [u1, v1] = etop[e1];
        // 今回繋ぐ辺へのユークリッド距離で更新
        for (auto& [stc, ec, rand, e2] : edges) {
            auto [u2, v2] = etop[e2];
            chmin(ec, (int)round(min({
                hypot(X[u1] - X[u2], Y[u1] - Y[u2]),
                hypot(X[u1] - X[v2], Y[u1] - Y[v2]),
                hypot(X[v1] - X[u2], Y[v1] - Y[u2]),
                hypot(X[v1] - X[v2], Y[v1] - Y[v2]),
            })));
        }
        sort(ALL(edges));
    };
    // 辺順序シャッフル用
    vector<int> P(M);
    iota(ALL(P), 0);
    vector<int> stcost(M);
    // STを生成
    auto make_st = [N, M, etop, edgecnt, recalc_cost](vector<int> &stcost) -> bitset<3000> {
        vector<array<int, 4>> edges;
        rep(e, M) {
            // 1. STに使われた回数, 2. 追加済みの辺でユークリッド距離で一番近いやつへの距離, 3. ランダム
            edges.pb({-stcost[e], MX, (int)randrange(0, MX), (int)e});
        }
        sort(ALL(edges));
        UnionFind uf(N);
        bitset<3000> res;
        rep(_, M) {
            auto [__, ___, ____, e] = edges.back();
            edges.pop_back();
            auto [u, v] = etop[e];
            if (not uf.same(u, v)) {
                // 使われた辺にコストをかける
                stcost[e]++;
                uf.merge(u, v);
                recalc_cost(e, edges);
            } else {
                // STに含まれない辺
                res.set(e);
            }
        }
        return res;
    };

    // とりあえず30
    int ST_COUNT = max(30, D);
    int each = ST_COUNT / D;
    vector<bitset<3000>> edges_set;
    rep(_, each) {
        stcost.assign(M, 0);
        rep(__, D) {
            edges_set.eb(make_st(stcost));
        }
    }
    vector<pair<int, vector<int>>> good_pos;
    rep(i, each) {
        vector<int> pos(D);
        iota(ALL(pos), i);
        bitset<3000> cur;
        rep(i, D) {
            cur |= edges_set[pos[i]];
        }
        good_pos.eb(cur.count(), pos);
    }

    // 優先度が高い方から時間めいっぱいまで試す
    ll mnscore = INF, mncost = INF;
    vector<int> ans(M);
    int opcnt = 0;
    rep(k, good_pos.size()) {
        vector<int> curans(M);
        // 重み付きマッチングでSTに含まれない方を優先して繋ぐ
        atcoder::mcf_graph<ll, ll> mcf(D + M + 2);
        int s = D + M;
        int t = D + M + 1;
        rep(i, D) {
            mcf.add_edge(s, i, K, 0);
            auto &edges = edges_set[good_pos[k].second[i]];
            rep(j, M) {
                mcf.add_edge(i, D + j, 1, !edges[j]);
            }
        }
        rep(j, M) {
            mcf.add_edge(D + j, t, 1, 0);
        }
        auto [f, c] = mcf.flow(s, t);
        assert(f == M);
        if (timer.get_elapse() >= TL) break;
        chmin(mncost, c);
        vector<int> C(D + 1);
        for (auto [from, to, cap, flow, cost] : mcf.edges()) {
            if (from < D and D <= to and to < D + M and flow >= 1) {
                int i = from;
                int j = to - D;
                curans[j] = i + 1;
                C[i + 1]++;
            }
        }
        assert(max(C) <= K);

        ll curscore = simulate_all(nodes, curans, scores, adj);
        if (curscore < mnscore) {
            mnscore = curscore;
            ans = curans;
        }
        rep(i, N) {
            adj[i].clear();
        }
        opcnt++;
        if (timer.get_elapse() >= TL) break;
    }

#ifdef __LOCAL
    debug(timer.get_elapse());
    debug(N);
    debug(D * K);
    debug(M);
    debug(opcnt);
    debug(M - good_pos[0].first);
    debug(mncost);
    ofs << ans << endl;
#else
    print(ans);
#endif

    return mnscore;
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
    auto T = gen_cases2(0, 50);
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

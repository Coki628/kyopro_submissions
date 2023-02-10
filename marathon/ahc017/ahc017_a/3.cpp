/*
・色々整理して山登り。思ったより伸びず…。ローカルだと159G→97Gとかになったんだけど、
　提出は34G→36Gになって、ここは同じ絶対評価表示のはずなのに全然違うのよく分からん。
　で、順位表だと少し(50位くらい)だけ上がった感じ。
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
#include "common/sum.hpp"
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"
#include "string/number_format.hpp"

const int MX = 1000000000;

// ダイクストラ
template<typename T>
vector<T> dijkstra(const vector<vector<pair<int, T>>> &nodes, int src, int goal = -1) {
    int N = nodes.size();
    vector<T> res(N, MX);
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> que;
    res[src] = 0;
    que.push({0, src});

    while (que.size()) {
        auto [dist, u] = que.top();
        que.pop();
        if (u == goal) return res;
        if (res[u] < dist) continue;
        for (auto [v, cost] : nodes[u]) {
            if (chmin(res[v], dist + cost)) {
                que.push({dist + cost, v});
            }
        }
    }
    return res;
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
    const int TL = 5700;
    int N, M, D, K;
    cin >> N >> M >> D >> K;
    vector<vector<pii>> nodes(N);
    auto G = listnd(N, N, MX);
    auto ptoe = listnd(N, N, 0);
    vector<pii> etop(M);
    vector<int> cost(M);
    vector<ll> scores(D + 1);
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
    }

    // 描画用頂点座標
    rep(i, N) {
        ll x, y;
        cin >> x >> y;
    }

    // 現在の連結状態での全点対距離取得
    auto get_dist_all = [N](vector<vector<pii>> &nodes) -> vvi {
        vvi res = listnd(N, N, 0);
        rep(u, N) {
            res[u] = dijkstra(nodes, u);
        }
        return res;
    };
    vvi base = get_dist_all(nodes);
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

    // とりあえず適当に乱択
    vector<int> ans(M), C(D + 1);
    rep(i, M) {
        int d = -1;
        while (1) {
            d = randrange(1, D + 1);
            if (C[d] < K) {
                C[d]++;
                break;
            }
        }
        ans[i] = d;
    }

    ll mnscore = simulate_all(nodes, ans, scores, adj);
    auto elapsed = timer.get_elapse();
    int opcnt = 0;
    while (elapsed < TL) {
        int e = randrange(0, M);
        int nxd = -1;
        while (1) {
            nxd = randrange(1, D + 1);
            if (nxd == ans[e] or C[nxd] == K) continue;
            break;
        }
        assert(nxd != -1);

        // 1点更新
        int pvd = ans[e];
        ans[e] = nxd;
        adj[nxd].eb(e);
        adj[pvd].erase(find(ALL(adj[pvd]), e));
        ll nxdscore = simulate(nxd, nodes, adj);
        ll pvdscore = simulate(pvd, nodes, adj);
        // 移動先日のコスト差分
        ll nxddiff = nxdscore - scores[nxd];
        // 移動元日のコスト差分
        ll pvddiff = pvdscore - scores[pvd];
        ll diff = nxddiff + pvddiff;
        if (diff < 0) {
            // OK, update
            scores[nxd] = nxdscore;
            scores[pvd] = pvdscore;
            C[nxd]++;
            C[pvd]--;
            mnscore = calc(scores);
        } else {
            // rollback
            ans[e] = pvd;
            adj[pvd].eb(e);
            adj[nxd].erase(find(ALL(adj[nxd]), e));
        }
        opcnt++;
        elapsed = timer.get_elapse();
    }

#ifdef __LOCAL
    debug(opcnt);
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

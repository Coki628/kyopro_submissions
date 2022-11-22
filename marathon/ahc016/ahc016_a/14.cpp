/*
・グラフの判定を次数だけでなく、隣接する頂点の次数の和みたいなものも使った。
　手元実行しか試してないけど、元々の状態よりは伸びず…。20ケースで250Mくらい。
　(今のベストは400Mくらい行く)
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
#include "common/ceil.hpp"

// 埋め込み
#include "tools/embedded.hpp"

auto solve(int testcase=-1) {
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

    const int TL = 4700;
    int M;
    const int Q = 100;
    double eps;
    cin >> M >> eps;
    #ifdef __LOCAL
        debug(M);
        debug(eps);
    #endif

    // スコア計算
    auto calc = [](int E, int N) -> int {
        return round(1e9 * pow(0.9, E) / N);
    };
    // 隣接リスト → 出力用01文字列変換
    auto graphtostr = [](int N, const vvi& nodes) -> string {
        string res;
        rep(u, N) {
            vector<int> vec(N);
            for (auto v : nodes[u]) {
                vec[v] = 1;
            }
            rep(v, u+1, N) {
                res += '0' + vec[v];
            }
        }
        return res;
    };
    // 出力用01文字列 → 隣接リスト変換
    auto strtograph = [](int N, const string& S) -> vvi {
        vvi res(N);
        int i = 0;
        rep(u, N) {
            rep(v, u+1, N) {
                if (S[i] == '1') {
                    res[u].eb(v);
                    res[v].eb(u);
                }
                i++;
            }
        }
        return res;
    };
    // 隣接リストからグラフのキー(頂点毎の次数の集合)を取得
    auto get_key = [](int N, const vvi& nodes) -> vector<pii> {
        vector<int> res1(N), res2(N);
        rep(u, N) {
            res1[u] = nodes[u].size();
            for (auto v : nodes[u]) {
                res2[u] += nodes[v].size();
            }
        }
        sort(res1.rbegin(), res1.rend());
        sort(res2.rbegin(), res2.rend());
        vector<pii> res;
        rep(i, N) {
            res.eb(res1[i], res2[i]);
        }
        // sort(res.rbegin(), res.rend());
        return res;
    };
    // 渡されるグラフHの生成シミュレーション
    auto generate_input_graph = [eps](int N, const vvi& G) -> vvi {
        vvi H(N);
        rep(u, N) {
            vector<int> vec(N);
            for (auto v : G[u]) {
                vec[v] = 1;
            }
            rep(v, u+1, N) {
                if (randrange(0, 100) < eps*100) {
                    vec[v] = 1 - vec[v];
                }
                if (vec[v]) {
                    H[u].eb(v);
                    H[v].eb(u);
                }
            }
        }
        vector<int> vec(N);
        iota(ALL(vec), 0);
        shuffle(ALL(vec), mt);
        vvi tmp(N);
        rep(u, N) {
            for (auto v : H[u]) {
                tmp[vec[u]].eb(vec[v]);
            }
        }
        swap(tmp, H);
        return H;
    };
    // expectsからHに一番近いものを見つける
    auto find = [M, eps, get_key, strtograph](
        int N,
        const vector<vector<pair<double, double>>>& expects,
        const string& H
    ) -> int {
        vector<pii> target_key = get_key(N, strtograph(N, H));
        vector<pair<double, int>> vec;
        rep(i, M) {
            double diffsm1 = 0, diffsm2 = 0;
            rep(u, N) {
                // 差分の2乗
                diffsm1 += abs(expects[i][u].first-target_key[u].first) * abs(expects[i][u].first-target_key[u].first);
                diffsm2 += abs(expects[i][u].second-target_key[u].second) * abs(expects[i][u].second-target_key[u].second);
            }
            vec.eb(diffsm2, i);
        }
        sort(ALL(vec));
        return vec[0].second;
    };
    // ダメダメな時の検索
    auto find2 = [M, eps, get_key, strtograph, find](
        int N,
        const vector<vector<pair<double, double>>>& expects,
        const string& H
    ) -> int {
        // return find(N, expects, H);
        int L = H.size();
        if (count(ALL(H), '0') > L/2) {
            return randrange(0, M/2);
        } else {
            return randrange(M/2, M);
        }
    };
    // M個のグラフ作成
    auto create_graphs = [M, strtograph, get_key](int N)
    -> tuple<vector<string>, vector<vvi>, vector<vector<pii>>> {
        auto graphs = listnd(M, N, vector<int>());
        vector<string> G(M);
        // グラフのキー(頂点毎の次数の集合)
        auto keys = listnd(M, N, mkp(0, 0));
        int L = N * (N-1) / 2;
        int each = L / M;
        rep(i, M) {
            G[i] = string(each*i, '1') + string(L-each*i, '0');
            graphs[i] = strtograph(N, G[i]);
            keys[i] = get_key(N, graphs[i]);
        }
        return {G, graphs, keys};
    };
    // M個のグラフ作成2(ダメダメなやつ用)
    auto create_graphs2 = [M, strtograph, get_key](int N)
    -> tuple<vector<string>, vector<vvi>, vector<vector<pii>>> {
        auto graphs = listnd(M, N, vector<int>());
        vector<string> G(M);
        // グラフのキー(頂点毎の次数の集合)
        auto keys = listnd(M, N, mkp(0, 0));
        int L = N * (N-1) / 2;
        // 前後半の2択にする
        rep(i, M/2) {
            G[i] = string(L, '0');
            graphs[i] = strtograph(N, G[i]);
            keys[i] = get_key(N, graphs[i]);
        }
        rep(i, M/2, M) {
            G[i] = string(L, '1');
            graphs[i] = strtograph(N, G[i]);
            keys[i] = get_key(N, graphs[i]);
        }
        return {G, graphs, keys};
    };
    // 各M個のグラフに対してHが取りそうなキー値を算出
    auto create_expects = [M, eps](int N, const vector<vector<pii>>& keys, vector<vvi>& graphs) -> vector<vector<pair<double, double>>> {
        auto expects = listnd(M, 0, mkp(0.0, 0.0));
        rep(i, M) {
            vector<double> res1(N), res2(N);
            auto mat = listnd(N, N, 0);
            rep(u, N) {
                int cur = keys[i][u].first;
                int currev = N - cur - 1;
                res1[u] = cur*(1.0-eps) + currev*eps;
                for (auto v : graphs[i][u]) {
                    mat[u][v] = 1;
                }
            }
            rep(u, N) {
                rep(v, N) {
                    if (v == u) continue;
                    rep(w, N) {
                        if (w == v) continue;
                        int e1 = mat[u][v];
                        int e2 = mat[v][w];
                        res2[u] += (e1 ? (1-eps) : eps) * (e2 ? (1-eps) : eps);
                    }
                }
            }
            sort(res1.rbegin(), res1.rend());
            sort(res2.rbegin(), res2.rend());
            rep(u, N) {
                expects[i].eb(res1[u], res2[u]);
            }
            // sort(expects[i].rbegin(), expects[i].rend());
        }
        return expects;
    };
    auto create_expects2 = [M, eps, create_expects](int N, const vector<vector<pii>>& keys, vector<vvi>& graphs) -> vector<vector<pair<double, double>>> {
        return create_expects(N, keys, graphs);
    };
    // 一連の流れをシミュレート
    auto simulate = [Q, M, create_graphs, create_expects, graphtostr, generate_input_graph, find, calc](
        int N
    ) -> double {
        auto [G, graphs, keys] = create_graphs(N);
        auto expects = create_expects(N, keys, graphs);
        int E = 0;
        rep(k, Q) {
            int s = randrange(0, M);
            string H = graphtostr(N, generate_input_graph(N, graphs[s]));
            int t = find(N, expects, H);
            if (t != s) {
                E++;
            }
        }
        return calc(E, N);
    };

    // 埋め込みから最適なNを取得
    int e = eps * 100;
    assert(embedded.count({M, e}));
    auto [N, mx] = embedded[{M, e}];

    // どうにもなんないやつを個別対応
    bool bad = false;
    if (mx < 20000 or N == 4) {
        bad = true;
        N = 4;
    }

    #ifdef __LOCAL
        debug(timer.get_elapse());
        debug(N);
        debug(bad);
    #endif
    #ifdef __LOCAL
        ofs << N << endl;
    #else
        cout << N << endl;
    #endif

    auto [G, graphs, keys] = not bad ? create_graphs(N) : create_graphs2(N);
    rep(i, M) {
        #ifdef __LOCAL
            ofs << G[i] << endl;
        #else
            cout << G[i] << endl;
        #endif
    }

    auto expects = not bad ? create_expects(N, keys, graphs) : create_expects2(N, keys, graphs);
    int E = 0;
    rep(k, Q) {
        string H;
        #ifdef __LOCAL
            int s;
            cin >> s;
            H = graphtostr(N, generate_input_graph(N, graphs[s]));
        #else
            cin >> H;
        #endif

        int t;
        if (not bad) {
            // ここで判定
            t = find(N, expects, H);
        } else {
            // t = randrange(0, M);
            t = find2(N, expects, H);
        }

        #ifdef __LOCAL
            ofs << t << endl;
        #else
            cout << t << endl;
        #endif

        #ifdef __LOCAL
            if (t != s) {
                E++;
            }
        #else
            // never know
        #endif
    }

    ll mxscore = 0;
    #ifdef __LOCAL
        mxscore = calc(E, N);
        string seed;
        cin >> seed;
    #endif
    return mxscore;
}

// テスト番号指定
vector<int> gen_cases1(const vector<int>& T) {
    return T;
}

// sからn件実施
vector<int> gen_cases2(int s, int n) {
    vector<int> T;
    rep(i, s, s+n) {
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
    return vector<int>(T.begin(), T.begin()+n);;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(2);

    #ifdef __LOCAL
        // テスト番号指定
        // auto T = gen_cases1({0});
        // sからn件実施
        auto T = gen_cases2(0, 20);
        // [s,t)を実施
        // auto T = gen_cases3(0, 300);
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

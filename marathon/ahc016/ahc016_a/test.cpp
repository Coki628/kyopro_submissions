/*
・M*epsの全通りで全Nを試してみて、最適っぽい場所を前計算しておく。
　埋め込み用の書式も出力する。
・最初各操作30回でやろうとしたら時間かかりすぎて、10回にした。
　10回でも比較的均した値が出るように、和を取るようにした。
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

pii solve(ofstream& ofs, int M, double eps) {
    const int Q = 100;
    debug(M);
    debug(eps);

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
    auto get_key = [](int N, const vvi& nodes) -> vector<int> {
        vector<int> res(N);
        rep(i, N) {
            res[i] = nodes[i].size();
        }
        sort(res.rbegin(), res.rend());
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
        const vector<vector<double>>& expects,
        const string& H
    ) -> int {
        vector<int> target_key = get_key(N, strtograph(N, H));
        vector<pair<double, int>> vec;
        rep(i, M) {
            double diffsm = 0;
            rep(u, N) {
                // 差分の2乗
                diffsm += abs(expects[i][u]-target_key[u]) * abs(expects[i][u]-target_key[u]);
            }
            vec.eb(diffsm, i);
        }
        sort(ALL(vec));
        return vec[0].second;
    };
    // M個のグラフ作成
    auto create_graphs = [M, strtograph, get_key](int N)
    -> tuple<vector<string>, vector<vvi>, vvi> {
        auto graphs = listnd(M, N, vector<int>());
        vector<string> G(M);
        // グラフのキー(頂点毎の次数の集合)
        auto keys = listnd(M, N, 0);
        int L = N * (N-1) / 2;
        int each = L / M;
        rep(i, M) {
            G[i] = string(each*i, '1') + string(L-each*i, '0');
            graphs[i] = strtograph(N, G[i]);
            keys[i] = get_key(N, graphs[i]);
        }
        return {G, graphs, keys};
    };
    // 各M個のグラフに対してHが取りそうなキー値を算出
    auto create_expects = [M, eps](int N, const vvi& keys) -> vector<vector<double>> {
        auto expects = listnd(M, N, 0.0);
        rep(i, M) {
            rep(u, N) {
                int cur = keys[i][u];
                int currev = N - cur - 1;
                expects[i][u] = cur*(1.0-eps) + currev*eps;
            }
            sort(expects[i].rbegin(), expects[i].rend());
        }
        return expects;
    };
    // 一連の流れをシミュレート
    auto simulate = [Q, M, create_graphs, create_expects, graphtostr, generate_input_graph, find, calc](
        int N
    ) -> double {
        auto [G, graphs, keys] = create_graphs(N);
        auto expects = create_expects(N, keys);
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

    const int OPCNT = 10;
    vector<ll> C(101);
    int mx = 0;
    rep(_, OPCNT) {
        rep(n, 4, 101) {
            int score = simulate(n);
            C[n] += score;
            chmax(mx, score);
        }
    }
    vector<pii> vec;
    rep(n, 4, 101) {
        // タイはnが小さい方優先
        vec.eb(C[n], -n);
    }
    sort(vec.rbegin(), vec.rend());
    // スコア総和が大きかったNに決める
    int N = -vec[0].second;

    // debug(C);
    debug(N);
    debug(number_format(mx));
    cout << endl;

    ofs << "M: " << M << endl;
    ofs << "eps: " << eps << endl;
    ofs << "C: [";
    rep(i, C.size()) {
        ofs << C[i];
        if (i != C.size()-1) {
            ofs << ", ";
        } else {
            ofs << "]" << endl;
        }
    }
    ofs << "N: " << N << endl;
    ofs << "mx: " << number_format(mx) << endl;
    ofs << endl;

    return {N, mx};
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(2);

    // 出力ファイル準備
    string filename = "tools/test/result.txt";
    ofstream ofs(filename.c_str());
    if (!ofs) {
        print("error, please check if 'tools/test/' dir exists");
        exit(0);
    }

    cout << "Start!" << endl;

    // M,eps全通り
    map<pii, pii> mp;
    rep(m, 10, 101) {
        rep(e, 41) {
            double eps = e * 0.01;
            auto [n, mx] = solve(ofs, m, eps);
            mp[{m, e}] = {n, mx};
        }
    }
    // 埋め込み用書式
    ofs << "map<pii, pii> mp = {" << endl;
    for (auto [k, v] : mp) {
        auto [m, e] = k;
        auto [n, mx] = v;
        ofs << "    {{" << m << ", " << e << "}, {" << n << ", " << mx << "}}," << endl;
    }
    ofs << "};" << endl;

    cout << "Successfully Done!" << endl;
    return 0;
}

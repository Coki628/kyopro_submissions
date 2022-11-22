/*
・Nの確定を丁寧にした。一連の流れをシミュして、一番良さそうなものを選ぶ。
　率の悪いケースの解決には繋がらないけど、比較的率の良いケースでかなり改善したはず。
　色々調整して、一番いいのがこれで708M！
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

auto solve(int testcase=-1) {
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
    auto calc = [](int E, int N) -> double {
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
    auto create_expects = [M, eps](int N, const vvi& keys) {
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

    // 辺の本数から下限を見つけておく
    int lo = 100, hi = 100;
    rep(i, 100, 3, -1) {
        if (i*(i-1)/2 >= M) {
            lo = i;
        } else {
            break;
        }
    }
    // Nを試す個数、増やせばより細かくチェックできるけど、TLが厳しくなって回数が減る
    const int CNT = 30;
    int each = ceil(hi-lo, CNT);
    vector<int> val;
    rep(i, lo, hi, each) {
        val.eb(i);
    }
    val.eb(hi);
    int sz = val.size();
    vector<int> C(sz);
    int opcnt = 0;
    bool end = false;
    // 時間いっぱいまでシミュ
    while (timer.get_elapse() < TL) {
        double mx = 0, idx = -1;
        rep(i, sz) {
            double score = simulate(val[i]);
            if (chmax(mx, score)) {
                idx = i;
            }
            if (timer.get_elapse() >= TL) {
                end = true;
                break;
            }
        }
        if (not end) {
            C[idx]++;
            opcnt++;
        }
    }
    vector<pii> vec;
    rep(i, sz) {
        vec.eb(C[i], i);
    }
    sort(vec.rbegin(), vec.rend());
    // 一番ハイスコア取得が多かったNに決める
    int N = val[vec[0].second];
    #ifdef __LOCAL
        debug(timer.get_elapse());
        debug(val);
        debug(C);
        debug(N);
        debug(opcnt);
    #endif
    #ifdef __LOCAL
        ofs << N << endl;
    #else
        cout << N << endl;
    #endif

    auto [G, graphs, keys] = create_graphs(N);
    rep(i, M) {
        #ifdef __LOCAL
            ofs << G[i] << endl;
        #else
            cout << G[i] << endl;
        #endif
    }

    auto expects = create_expects(N, keys);
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

        // ここで判定
        int t = find(N, expects, H);

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
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // テスト番号指定
        // auto T = gen_cases1({0, 70, 76});
        // sからn件実施
        // auto T = gen_cases2(0, 20);
        // [s,t)を実施
        auto T = gen_cases3(50, 100);
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

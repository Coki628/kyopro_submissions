/*
・グラフの生成方法を変更。辺ベースで有無を均等に割り振るみたいな感じに。
　あとそれによって少ない頂点数でも対応できる範囲が増えたようなので、
　2%だった閾値を10%まで増やせた。これで448M。
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

    int N = eps < 0.10 ? M : 100;
    #ifdef __LOCAL
        ofs << N << endl;
    #else
        cout << N << endl;
    #endif

    // スコア計算
    auto calc = [](int E, int N) -> double {
        return round(1e9 * pow(0.9, E) / N);
    };
    // 隣接リスト → 出力用01文字列変換
    auto graphtostr = [N](const vvi& nodes) -> string {
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
    auto strtograph = [N](const string& S) -> vvi {
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
    auto get_key = [N](const vvi& nodes) -> vector<int> {
        vector<int> res(N);
        rep(i, N) {
            res[i] = nodes[i].size();
        }
        sort(res.rbegin(), res.rend());
        return res;
    };
    // 渡されるグラフHの生成シミュレーション
    auto generate_input_graph = [N, eps](const vvi& G) -> vvi {
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
    // keysからHに一番近いものを見つける
    auto find = [M, N, get_key, strtograph](const vector<vector<double>>& keys, const string& H) -> int {
        vector<int> target_key = get_key(strtograph(H));
        vector<pair<double, int>> vec;
        rep(i, M) {
            double diffsm = 0;
            rep(u, N) {
                // 差分の2乗
                diffsm += abs(keys[i][u]-target_key[u]) * abs(keys[i][u]-target_key[u]);
            }
            vec.eb(diffsm, i);
        }
        sort(ALL(vec));
        return vec[0].second;
    };

    // create graph here
    auto graphs = listnd(M, N, vector<int>());
    vector<string> G(M);
    // グラフのキー(頂点毎の次数の集合)
    auto keys = listnd(M, N, 0);
    int L = N * (N-1) / 2;
    int each = L / M;
    rep(i, M) {
        G[i] = string(each*i, '1') + string(L-each*i, '0');
        graphs[i] = strtograph(G[i]);
        keys[i] = get_key(graphs[i]);
    }
    rep(i, M) {
        #ifdef __LOCAL
            ofs << G[i] << endl;
        #else
            cout << G[i] << endl;
        #endif
    }

    // Hが取りそうなキー値を算出しておく
    auto expects = listnd(M, N, 0.0);
    rep(i, M) {
        rep(u, N) {
            int cur = keys[i][u];
            int currev = N - cur - 1;
            expects[i][u] = cur*(1.0-eps) + currev*eps;
        }
    }

    int E = 0;
    rep(k, Q) {
        string H;
        #ifdef __LOCAL
            int s;
            cin >> s;
            H = graphtostr(generate_input_graph(graphs[s]));
        #else
            cin >> H;
        #endif

        // ここで判定
        int t = find(expects, H);

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
    return vector<int>(T.begin(), T.begin()+n);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // テスト番号指定
        // auto T = gen_cases1({1});
        // sからn件実施
        auto T = gen_cases2(50, 50);
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

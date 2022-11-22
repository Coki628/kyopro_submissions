/*
・とりあえず考えた貪欲。
　次数に差をつけて、ソートすることでシャッフルに対応させる。これで84Mくらい。
　改変率の高いケースでダメダメ…。
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

    int M;
    const int Q = 100;
    double eps;
    cin >> M >> eps;

    int N = M;
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
    auto graphtostr = [&](const vvi& nodes) -> string {
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
    auto strtograph = [&](const string& S) -> vvi {
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
    // 渡されるグラフHの生成シミュレーション
    auto generate_input_graph = [&](const vvi& G) {
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
        return graphtostr(H);
    };
    // hashsからHに一番近いものを見つける
    auto find = [&](const vvi& hashs, const string& H) -> int {
        vector<int> hash(N);
        auto nodes = strtograph(H);
        rep(u, N) {
            hash[u] = nodes[u].size();
        }
        sort(hash.rbegin(), hash.rend());

        vector<pll> vec;
        rep(i, M) {
            ll diffsm = 0;
            rep(u, N) {
                diffsm += abs(hashs[i][u] - hash[u]);
            }
            vec.eb(diffsm, i);
        }
        sort(ALL(vec));
        return vec[0].second;
    };

    // create graph here
    auto graphs = listnd(M, N, vector<int>());
    auto hashs = listnd(N, M, 0);
    rep(i, M) {
        auto& nodes = graphs[i];
        rep(u, i) {
            rep(v, u+1, N) {
                nodes[u].eb(v);
                nodes[v].eb(u);
            }
        }
        rep(u, N) {
            hashs[i][u] = nodes[u].size();
        }
    }
    vector<string> G(M);
    rep(i, M) {
        G[i] = graphtostr(graphs[i]);
        #ifdef __LOCAL
            ofs << G[i] << endl;
        #else
            cout << G[i] << endl;
        #endif
    }

    int E = 0;
    rep(k, Q) {
        string H;
        #ifdef __LOCAL
            int s;
            cin >> s;
            H = generate_input_graph(graphs[s]);
        #else
            cin >> H;
        #endif

        // ここで判定
        int t = find(hashs, H);

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

    ld mxscore = 0;
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
        // auto T = gen_cases1({1});
        // sからn件実施
        auto T = gen_cases2(0, 20);
        // [s,t)を実施
        // auto T = gen_cases3(0, 100);
        // [s,t)の範囲でランダムにn件実施
        // auto T = gen_cases4(0, 100, 20);

        ld totalscore = 0;
        for (int t : T) {
            cout << "case #" << t << " start" << endl;
            auto score = solve(t);
            cout << "case #" << t << " ";
            debug(score);
            cout << endl;
            totalscore += score;
        }
        debug(totalscore);
    #else
        solve();
    #endif

    return 0;
}

/*
・初期解
・とりあえず動作確認なので乱択で。
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

    auto calc = [](int E, int N) -> double {
        return round(1e9 * pow(0.9, E) / N);
    };
    auto graphtostr = [&](const vvi& nodes) {
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
        shuffle(ALL(H), mt);
        return graphtostr(H);
    };

    // create graph here
    auto graphs = listnd(M, N, vector<int>());
    rep(i, M) {
        // 一直線グラフ
        rep(u, N-1) {
            graphs[i][u].eb(u+1);
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

    // ローカルでの答え生成
    #ifdef __LOCAL
        vector<int> ans(Q);
        rep(i, Q) {
            ans[i] = randrange(0, M);
        }
    #endif
    int E = 0;
    rep(k, Q) {
        string H;
        #ifdef __LOCAL
            H = generate_input_graph(graphs[ans[k]]);
        #else
            cin >> H;
        #endif

        // ここで判定

        // とりあえず適当に乱択
        int t = randrange(0, M);
        #ifdef __LOCAL
            ofs << t << endl;
        #else
            cout << t << endl;
        #endif

        #ifdef __LOCAL
            if (t != ans[k]) {
                E++;
            }
        #else
            // never know
        #endif
    }

    ld mxscore = 0;
    #ifdef __LOCAL
        mxscore = calc(E, N);
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
        auto T = gen_cases1({0});
        // sからn件実施
        // auto T = gen_cases2(0, 20);
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

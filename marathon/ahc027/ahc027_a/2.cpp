/*
・とりあえず初期解。
・サンプルプログラムが木を構築してそのルートとしていたので、
　同じような感じで自分ではBFS木を構築してオイラーツアーした。
　でもサンプルと同じDFS木のがまだ良かったかもしれん。。
　これでスコアが2068Mくらい。
・やっぱりDFS木にしてみた。こっちのが全然まし。。
　スコアが1541Mくらい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
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
    int H, W;
    cin >> H;
    W = H;
    // 下の壁
    vector<string> walls1(H - 1);
    cin >> walls1;
    // 右の壁
    vector<string> walls2(H);
    cin >> walls2;
    int blocked[H][W][4] = {};
    rep(h, H - 1) {
        rep(w, W) {
            if (walls1[h][w] == '1') {
                blocked[h][w][1] = 1;
                blocked[h + 1][w][0] = 1;
            }
        }
    }
    rep(h, H) {
        rep(w, W - 1) {
            if (walls2[h][w] == '1') {
                blocked[h][w][3] = 1;
                blocked[h][w + 1][2] = 1;
            }
        }
    }

    // 元の一般グラフを構築
    int N = H * W;
    vvi nodes1(N);
    vector<int> dtoc = {'U', 'D', 'L', 'R'};
    map<pii, char> mp;
    rep(h, H) {
        rep(w, W) {
            int u = gridtoid(h, w, W);
            rep(d, 4) {
                if (blocked[h][w][d]) continue;
                auto [dh, dw] = dir4[d];
                int nh = h + dh;
                int nw = w + dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                int v = gridtoid(nh, nw, W);
                nodes1[u].eb(v);
                nodes1[v].eb(u);
                mp[{u, v}] = dtoc[d];
            }
        }
    }

    // 全域木(DFS木)を走査してルートとする
    string ans;
    vector<int> visited(N);
    auto dfs = [&](auto &&f, int u, int prv) -> void {
        visited[u] = true;
        for (auto v : nodes1[u]) {
            if (v == prv) continue;
            if (visited[v]) continue;
            ans += mp[{u, v}];
            f(f, v, u);
            ans += mp[{v, u}];
        }
    };
    dfs(dfs, 0, -1);

    ll mxscore = 0;

#ifdef __LOCAL
    ofs << ans << endl;
#else
    print(ans);
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
    auto T = gen_cases1({0});
    // sからn件実施
    // auto T = gen_cases2(0, 20);
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

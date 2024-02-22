/*
・全部見つかったかどうかは分かるので、その時点で作業打ち切りにした。
　スコアは少し、12.7G -> 11.4G に改善。
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
#include "common/Timer.hpp"
#include "grid/constants/directions.hpp"
#include "random/randrange.hpp"
#include "random/randint.hpp"
#include "string/number_format.hpp"
#include "string/zfill.hpp"

#include "common/join.hpp"

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
    int N, M;
    double eps;
    cin >> N >> M >> eps;
    vv<pii> vec(M);
    int vtotal = 0;
    rep(i, M) {
        int d;
        cin >> d;
        rep(j, d) {
            int h, w;
            cin >> h >> w;
            vec[i].eb(h, w);
            vtotal++;
        }
    }
#ifdef __LOCAL
    vector<pii> D;
    rep(i, M) {
        ll h, w;
        cin >> h >> w;
        D.eb(h, w);
    }
    auto grid = listnd(N, N, 0);
    vector<pii> vcells;
    rep(h, N) {
        rep(w, N) {
            cin >> grid[h][w];
            if (grid[h][w] > 0) {
                vcells.eb(h, w);
            }
        }
    }
    sort(ALL(vcells));
    vector<double> E;
    rep(i, 2 * N * N) {
        double e;
        cin >> e;
        E.eb(e);
    }
    auto calc = [vcells](vector<pii> ans, double cost) -> int {
        sort(ALL(ans));
        if (ans == vcells) {
            return round(1e6 * cost);
        } else {
            return 1e9;
        }
    };
    auto ask = [&](int op, const vector<pii> &cells, int qcnt) -> pair<double, double> {
        if (op == 1) {
            auto [h, w] = cells[0];
            return {grid[h][w], 1};
        } else {
            int sm = 0;
            for (auto &[h, w] : cells) {
                sm += grid[h][w];
            }
            int k = cells.size();
            // 正規分布 平均μ 分散σ
            double mu = (k - sm) * eps + sm * (1 - eps);
            double sigma = sqrt(k * eps * (1 - eps));
            return {max(round(mu + sigma * E[qcnt]), 0.0), 1 / sqrt(k)};
        }
    };
#endif

    vector<pii> ans;
    int qcnt = 0, vcnt = 0;
    double cost = 0;
    bool ok = false;
    rep(h, N) {
        rep(w, N) {
#ifdef __LOCAL
            ofs << "q 1 " << h << " " << w << endl;
            auto [v, c] = ask(1, {{h, w}}, qcnt);
            cost += c;
#else
            cout << "q 1 " << h << " " << w << endl;
            int v;
            cin >> v;
#endif
            if (v > 0) {
                ans.eb(h, w);
            }
            vcnt += v;
            qcnt++;
            if (vcnt == vtotal) {
                ok = true;
                break;
            }
        }
        if (ok) break;
    }

    int mnscore = 1e9;
#ifdef __LOCAL
    ofs << "a " << ans.size() << " ";
    ofs << join(ans, " ") << endl;
    int score = calc(ans, cost);
    if (score == 1e9) {
        cost++;
    } else {
        chmin(mnscore, score);
    }
    debug(cost);
#else
    cout << "a " << ans.size() << " ";
    cout << join(ans, " ") << endl;
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

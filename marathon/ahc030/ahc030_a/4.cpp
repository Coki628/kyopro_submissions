/*
・乱択で当たりマス探す時に、四方合わせて5マスでチェックしてみた。
　スコアはほぼ変化なし。。
・結局、これが最終提出。今回後半はほぼ何もできなかったな…。
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
    auto respond = [&](int k, const vector<pii> &cells, int qcnt) -> pair<int, double> {
        if (k == 1) {
            auto [h, w] = cells[0];
            return {grid[h][w], 1};
        } else {
            int sm = 0;
            for (auto &[h, w] : cells) {
                sm += grid[h][w];
            }
            // 正規分布 平均μ 分散σ
            double mu = (k - sm) * eps + sm * (1 - eps);
            double sigma = sqrt(k * eps * (1 - eps));
            return {max(round(mu + sigma * E[qcnt]), 0.0), 1 / sqrt(k)};
        }
    };
#endif
    auto ask = [&](const vector<pii> &cells, int qcnt) -> pair<int, double> {
        int k = cells.size();
#ifdef __LOCAL
        ofs << "q " << k << " " << join(cells, " ") << endl;
        auto [v, c] = respond(k, cells, qcnt);
#else
        cout << "q " << k << " " << join(cells, " ") << endl;
        int v;
        cin >> v;
        double c = 1 / sqrt(k);
#endif
        return {v, c};
    };

    vector<pii> ans;
    int qcnt = 0, vcnt = 0;
    double cost = 0;
    auto used = listnd(N, N, 0);
    while (vcnt < vtotal) {
        int h = randrange(1, N - 1);
        int w = randrange(1, N - 1);
        if (used[h][w]) continue;
        vector<pii> cur;
        cur.eb(h, w);
        for (auto [dh, dw] : dir4) {
            int ch = h + dh, cw = w + dw;
            cur.eb(ch, cw);
        }
        auto [v, c] = ask(cur, qcnt++);
        cost += c;
        if (v > 0) {
            auto bfs = [&]() {
                queue<pii> que;
                que.push({h, w});
                while (!que.empty()) {
                    auto [ch, cw] = que.front();
                    que.pop();
                    for (auto [dh, dw] : dir4) {
                        int nh = ch + dh;
                        int nw = cw + dw;
                        if (nh < 0 or nw < 0 or nh >= N or nw >= N) continue;
                        if (used[nh][nw]) continue;
                        auto [v, c] = ask({{nh, nw}}, qcnt++);
                        vcnt += v;
                        cost += c;
                        used[nh][nw] = true;
                        if (v > 0) {
                            ans.eb(nh, nw);
                            que.push({nh, nw});
                        }
                    }
                }
            };
            bfs();
        }
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
    // auto T = gen_cases1({1});
    // sからn件実施
    // auto T = gen_cases2(0, 20);
    // [s,t)を実施
    auto T = gen_cases3(0, 100);
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

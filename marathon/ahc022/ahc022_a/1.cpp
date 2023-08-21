/*
・最初の提出。とりあえず各出口セルに等間隔に温度割り振って、
　何回か計測して予測値から一番近そうなやつ、みたいにした。
　Sが小さいとこれでかなり当たるんだけど、大きいとどうにもならん。
　スコアが21Mくらいで相対が緑中位くらい。
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

#include "common/modulo.hpp"

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
    int L, N, S;
    cin >> L >> N >> S;
    vector<pii> cells;
    // 設定する温度の最大値。(制約の最大は1000)
    // これが大きければ各セルの温度間隔が大きくなるので判別しやすくなる半面、
    // 隣接セルの温度差は大きくなるので設置コストは高くなる。
    const int MXTEMP = 1000;
    const int MXOP = 10000;
    auto P = listnd(L, L, -1);
    // 1つの出口セルにかけられる操作回数
    int eachcnt = MXOP / N;
    vector<int> E(N);
    vector<pair<ld, int>> avgs(N);
    // 配置時コスト, 計測時コスト
    ll cost1 = 0, cost2 = 0;

    rep(i, N) {
        ll h, w;
        cin >> h >> w;
        cells.eb(h, w);
    }

    // 出口のあるセルを決める
    rep(i, N) {
        int temp = MXTEMP / N * i;
        auto [h, w] = cells[i];
        P[h][w] = temp;
    }
    // その他のセルを決める
    rep(h, L) {
        rep(w, L) {
            if (P[h][w] == -1) {
                P[h][w] = MXTEMP / 2;
            }
        }
    }
    // 配置時コスト
    rep(h, L) {
        rep(w, L) {
            cost1 += pow(P[h][w] - P[(h + 1) % L][w], 2);
            cost1 += pow(P[h][w] - P[h][(w + 1) % L], 2);
        }
    }
    
    // 配置の出力
    rep(h, L) {
#ifdef __LOCAL
        rep(w, L) {
            ofs << P[h][w];
            if (w == L - 1) {
                ofs << endl;
            } else {
                ofs << ' ';
            }
        }
#else
        print(P[h]);
#endif
    }

#ifdef __LOCAL
    vector<int> A(N);
    cin >> A;
    // 温度計測
    auto measure = [A, cells, P, S](int i, int y, int x) {
        // 対応する出口セル番号
        int j = A[i];
        auto [h, w] = cells[j];
        // 今回の誤差
        int f;
        cin >> f;
        return clamp(P[h][w] + f, 0, 1000);
    };
    // スコア計算
    auto calc = [N, A](vector<int> &E, int cost1, int cost2) -> pair<ll, int> {
        int W = 0;
        rep(i, N) {
            if (A[i] != E[i]) {
                W++;
            }
        }
        return {ceil(1e14 * pow(0.8, W) / (cost1 + cost2 + 1e5)), W};
    };
#endif

    rep(i, N) {
        int sm = 0;
        rep(j, eachcnt) {
            ll m, y = 0, x = 0;
            // 計測時コスト
            cost2 += 100 * (10 + abs(y) + abs(x));
#ifdef __LOCAL
            ofs << i << ' ' << y << ' ' << x << endl;
            m = measure(i, y, x);
#else
            cout << i << ' ' << y << ' ' << x << endl;
            cin >> m;
#endif
            sm += m;
        }
        avgs[i] = {sm / (ld)eachcnt, i};
    }
    sort(ALL(avgs));
    rep(i, N) {
        auto [_, j] = avgs[i];
        E[j] = i;
    }

    // 回答の出力
#ifdef __LOCAL
    ofs << "-1 -1 -1" << endl;
    for (auto e : E) {
        ofs << e << endl;
    }
    // 余分な出力を破棄
    int rest = MXOP - N * eachcnt;
    rep(_, rest) {
        ll tmp;
        cin >> tmp;
    }
#else
    cout << "-1 -1 -1" << endl;
    print(E, '\n');
#endif

    ll mxscore = 0, W = 0;
#ifdef __LOCAL
    tie(mxscore, W) = calc(E, cost1, cost2);
    debug(L);
    debug(N);
    debug(S);
    debug(W);
    debug(cost1);
    debug(cost2);
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

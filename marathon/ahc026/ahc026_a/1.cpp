/*
・とりあえず初期解。
　取り出したいやつより上を適当な場所に移動させる。
　これでスコアは1217Kくらい。
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

#include "common/subarray.hpp"

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
    const int N = 200, M = 10, K = N / M;
    int tmp;
    cin >> tmp >> tmp;
    auto box = listnd(M, K, 0);
    rep(i, M) {
        rep(j, K) {
            cin >> box[i][j];
            box[i][j]--;
        }
    }

    vector<pii> ans;
    int cost = 0;
    auto calc = [](int v) {
        return max(1, 10000 - v);
    };
    // 箱iを見つける、山jと位置kを返す
    auto find = [&](int i) -> pii {
        rep(j, M) {
            bool ok = false;
            rep(k, box[j].size()) {
                if (box[j][k] == i) {
                    return {j, k};
                }
            }
        }
        return {-1, -1};
    };
    // 山fromのk番目以降を山toへ移動
    auto op1 = [&](int from, int to, int k) {
        ans.eb(box[from][k] + 1, to + 1);
        int sz = box[from].size();
        auto tmp = subarray(box[from], k, sz);
        cost += tmp.size();
        for (auto v : tmp) {
            box[to].eb(v);
        }
        rep(_, sz - k) {
            box[from].pop_back();
        }
    };
    // 山mから箱vを回収する
    auto op2 = [&](int m, int v) {
        ans.eb(v + 1, 0);
        assert(box[m].back() == v);
        box[m].pop_back();
    };
    rep(i, N) {
        auto [m, k] = find(i);
        // 上の箱をどかす
        if (k < box[m].size() - 1) {
            int nxt = m;
            while (nxt == m) {
                // 移動先は適当に
                nxt = randrange(0, M);
            }
            op1(m, nxt, k + 1);
        }
        op2(m, i);
    }

    ll mxscore = calc(cost);

    for (auto [v, i] : ans) {
#ifdef __LOCAL
        ofs << v << ' ' << i << endl;
#else
        cout << v << ' ' << i << endl;
#endif
    }

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
    // auto T = gen_cases1({0});
    // sからn件実施
    auto T = gen_cases2(0, 20);
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

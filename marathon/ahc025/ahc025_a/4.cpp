/*
・最初から後半パートの方針でやる方針。伸びなかった。
　やっぱり最初のソートはしておいた方がいいみたいだ。
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

#include "common/ceil.hpp"

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
    int N, D, Q;
    cin >> N >> D >> Q;
#ifdef __LOCAL
    vector<int> W(N);
    cin >> W;
#endif
    // 質問クエリ
    auto ask = [&](vector<int> &L, vector<int> &R) -> char {
        int nl = L.size();
        int nr = R.size();
#ifdef __LOCAL
        ofs << nl << " " << nr << " ";
        rep(i, nl) {
            ofs << L[i] << " ";
        }
        rep(i, nr) {
            ofs << R[i];
            if (i == nr - 1) {
                ofs << endl;
            } else {
                ofs << " ";
            }
        }
        // ローカル用計算ロジック
        int lsm = 0, rsm = 0;
        for (auto i : L) {
            lsm += W[i];
        }
        for (auto i : R) {
            rsm += W[i];
        }
        // debug(lsm - rsm);
        if (lsm == rsm) {
            return '=';
        } else if (lsm < rsm) {
            return '<';
        } else {
            return '>';
        }
#else
        cout << nl << " " << nr << " ";
        rep(i, nl) {
            cout << L[i] << " ";
        }
        rep(i, nr) {
            cout << R[i];
            if (i == nr - 1) {
                cout << endl;
            } else {
                cout << " ";
            }
        }
        char res;
        cin >> res;
        return res;
#endif
    };
    // 回答クエリ
    auto answer = [&](vector<int> &D) -> void {
#ifdef __LOCAL
        ofs << D << endl;
#else
        cout << D << endl;
#endif
    };
#ifdef __LOCAL
    // スコア計算
    auto calc = [D, W](vector<int> &vec) {
        ll sm = 0;
        for (auto t : vec) {
            sm += t;
        }
        ld avg = sm / (ld)D;
        ld v = 0;
        for (auto t : vec) {
            v += (t - avg) * (t - avg);
        }
        v /= D;
        return 1 + round(100 * sqrt(v));
    };
#endif
    vvi bucket2(D);
    vector<int> ans(N);
    rep(i, N) {
        ans[i] = i % D;
        bucket2[ans[i]].eb(i);
    }

    // 山iのa番目を山jに移す(移動先の山jでのindexを返す)
    auto move = [&](int i, int j, int a = -1) -> int {
        if (a == -1) {
            a = randrange(0, bucket2[i].size());
        }
        ans[bucket2[i][a]] = j;
        int b = bucket2[j].size();
        bucket2[j].eb(bucket2[i][a]);
        bucket2[i].erase(bucket2[i].begin() + a);
        return b;
    };
    int q = 0;
    while (q < Q) {
        int i = randrange(0, D);
        int j = randrange(0, D);
        while (j == i) {
            j = randrange(0, D);
        }
        q++;
        char cur = ask(bucket2[i], bucket2[j]);
        if (q == Q) break;
        if (cur == '>') {
            swap(i, j);
            cur = '<';
        }
        while (q < Q and cur == '<' and bucket2[j].size() >= 2) {
            // 重い方から軽い方へ1つ移動
            int b = move(j, i);
            q++;
            char nxt = ask(bucket2[i], bucket2[j]);
            // 逆転してしまったら戻す
            if (nxt == '>') {
                move(i, j, b);
                break;
            }
        }
    }
    answer(ans);

    ll mxscore = 0;
#ifdef __LOCAL
    vector<int> sm2(D);
    rep(i, N) {
        sm2[ans[i]] += W[i];
    }
    debug(sm2);
    mxscore = calc(sm2);
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
    // auto T = gen_cases1({5});
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

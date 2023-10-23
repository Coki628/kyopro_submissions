/*
・ライブラリ整備：焼きなまし
　21億点くらいだったやつは28億点くらいになった。
　その後、温度調整をして、33億点台になった。
　まあ結局山登りの36億より低いんだけどね。
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

#include "heuristics/AnnealingManager.hpp"

const int L = 8;
const string letters = "ABCDEFGH.";
const int N = 20;
vector<string> S;
vector<string> mat(N, string(N, '.'));

unordered_map<string, int> C;

void count_all() {
    rep(i, N) {
        rep(j, N) {
            string cur;
            rep(k, j, N) {
                cur += mat[i][k];
                C[cur]++;
            }
        }
    }
    rep(j, N) {
        rep(i, N) {
            string cur;
            rep(k, i, N) {
                cur += mat[k][j];
                C[cur]++;
            }
        }
    }
}

void count(ll h, ll w, char c) {
    rep(j, N) {
        string cur;
        rep(k, j, N) {
            cur += mat[h][k];
            C[cur]--;
        }
    }
    rep(i, N) {
        string cur;
        rep(k, i, N) {
            cur += mat[k][w];
            C[cur]--;
        }
    }
    mat[h][w] = c;
    rep(j, N) {
        string cur;
        rep(k, j, N) {
            cur += mat[h][k];
            C[cur]++;
        }
    }
    rep(i, N) {
        string cur;
        rep(k, i, N) {
            cur += mat[k][w];
            C[cur]++;
        }
    }
}

ll calc_all(ll M, ll d = N * N) {
    ll cnt = 0;
    for (auto &s : S) {
        if (C[s]) cnt++;
    }
    if (cnt < M) {
        return round(1e8 * cnt / M);
    } else {
        return round(1e8 * 2 * N * N / (2 * N * N - d));
    }
}

const int TL = 2500;
const double T0 = 100000;
const double T1 = 100;

auto solve(int testcase = -1) {
    Timer timer;
    C.reserve(1e6);
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

    ll _, M;
    cin >> _ >> M;
    S.resize(M);
    rep(i, M) {
        cin >> S[i];
    }

    // 初期解(貪欲)
    sort(ALL(S));
    ll k = 0;
    rep(i, N) {
        ll j = 0;
        while (j < N) {
            if (j + S[k].size() < N) {
                rep(l, S[k].size()) {
                    mat[i][j + l] = S[k][l];
                }
                j += S[k].size();
                k++;
            } else {
                break;
            }
        }
    }
    count_all();
    ll score = calc_all(M);
#ifdef __LOCAL
    debug(score);
#endif

    // 焼きなまし
    AnnealingManager am(TL, T0, T1, false, 2);
    auto elapsed = timer.get_elapse();
    ll opcnt = 0, okcnt = 0, ok2cnt = 0;
    ll mxdiff = 0;
    while (elapsed < TL) {
        opcnt++;
        ll h = randrange(0, N);
        ll w = randrange(0, N);
        ll c = randrange(0, L);
        char prevc = mat[h][w];
        count(h, w, letters[c]);
        ll nxscore = calc_all(M);
        ll diff = nxscore - score;
        chmax(mxdiff, abs(diff));
        if (am.judge(score, nxscore, elapsed)) {
            okcnt++;
            if (diff < 0) {
                ok2cnt++;
            }
            score = nxscore;
        } else {
            count(h, w, prevc);
        }
        elapsed = timer.get_elapse();
    }
#ifdef __LOCAL
    debug(score);
    debug(opcnt);
    debug(okcnt);
    debug(ok2cnt);
    debug(mxdiff);
    debug(C.size());
#endif

    rep(i, N) {
#ifdef __LOCAL
        ofs << mat[i] << endl;
#else
        print(mat[i]);
#endif
    }
    return score;
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

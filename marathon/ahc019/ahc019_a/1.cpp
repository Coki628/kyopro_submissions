/*
・とりあえず初期解。今回はここまでバグらせてないのでまあいい感じか。
・両方で共通で使えるやつだけまとめて、残りは1個ずつで置けるだけ置いた感じ。
　これが絶対スコアで16544G。
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

#include "common/divmod.hpp"
#include "graph/UnionFind.hpp"

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
    int D;
    cin >> D;
    auto F1 = listnd(D, D, 0);
    auto R1 = listnd(D, D, 0);
    auto F2 = listnd(D, D, 0);
    auto R2 = listnd(D, D, 0);
    rep(i, D) {
        rep(j, D) {
            char c;
            cin >> c;
            F1[i][j] = c - '0';
        }
    }
    rep(i, D) {
        rep(j, D) {
            char c;
            cin >> c;
            R1[i][j] = c - '0';
        }
    }
    rep(i, D) {
        rep(j, D) {
            char c;
            cin >> c;
            F2[i][j] = c - '0';
        }
    }
    rep(i, D) {
        rep(j, D) {
            char c;
            cin >> c;
            R2[i][j] = c - '0';
        }
    }

    auto d3tod1 = [D](int x, int y, int z) -> int {
        return x * D * D + y * D + z;
    };
    auto d1tod3 = [D](int v) -> array<int, 3> {
        auto [x, yz] = divmod(v, D * D);
        auto [y, z] = divmod(v, D);
        return {x, y, z};
    };
    const vector<array<int, 3>> dir6 = {
        {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1},
    };

    // 両方共通で置ける位置
    auto both_used = listnd(D, D, D, 0);
    UnionFind uf(D * D * D);
    rep(x, D) {
        rep(y, D) {
            rep(z, D) {
                if (F1[z][x] and R1[z][y] and F2[z][x] and R2[z][y]) {
                    both_used[x][y][z] = 1;
                    for (auto [dx, dy, dz] : dir6) {
                        int nx = x + dx;
                        int ny = y + dy;
                        int nz = z + dz;
                        if (nx < 0 or ny < 0 or nz < 0 or nx >= D or ny >= D or
                            nz >= D)
                            continue;
                        if (both_used[nx][ny][nz]) {
                            int u = d3tod1(x, y, z);
                            int v = d3tod1(nx, ny, nz);
                            uf.merge(u, v);
                        }
                    }
                }
            }
        }
    }

    auto ans = listnd(2, D * D * D, 0);
    // その連結成分のブロック番号
    vector<int> number(D * D * D, -1);
    int n = 0;
    rep(x, D) {
        rep(y, D) {
            rep(z, D) {
                int u = d3tod1(x, y, z);
                if (both_used[x][y][z]) {
                    int r = uf.find(u);
                    if (number[r] == -1) {
                        number[r] = ++n;
                    }
                    ans[0][u] = number[r];
                    ans[1][u] = number[r];
                } else if (F1[z][x] and R1[z][y]) {
                    ans[0][u] = ++n;
                } else if (F2[z][x] and R2[z][y]) {
                    ans[1][u] = ++n;
                }
            }
        }
    }

    // スコア計算は後で
    ll mxscore = 0;

#ifdef __LOCAL
    ofs << n << endl;
    ofs << ans[0] << endl;
    ofs << ans[1] << endl;
#else
    print(n);
    print(ans[0]);
    print(ans[1]);
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

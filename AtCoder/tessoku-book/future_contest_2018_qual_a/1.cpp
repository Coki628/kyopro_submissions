/*
・山登り、焼きなまし
・どっちも変わらないようだった。多分近傍の取り方が本と違うのが良くない。
・あと、速度は訪問済をset管理だと回数500くらいとかなのに、
　100*100配列毎回持ったら15000回くらい回せた。
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
    const int TL = 5700;
    const int T0 = 180;
    const int T1 = 1;
    const int N = 100;
    int Q = 1000;
    auto A = listnd(N, N, 0);
    auto B = listnd(N, N, 0);

    rep(i, N) {
        rep(j, N) {
            cin >> A[i][j];
        }
    }

    auto calc = [](ll sm) {
        return 2e8 - sm;
    };
    auto add = [&](int x, int y, int h) -> int {
        int diff = 0;
        bool visited[N][N] = {};
        queue<array<int, 3>> que;
        que.push({x, y, h});
        visited[x][y] = true;
        while (que.size()) {
            auto [cx, cy, ch] = que.front();
            que.pop();
            diff -= abs(B[cx][cy] - A[cx][cy]);
            B[cx][cy] += ch;
            diff += abs(B[cx][cy] - A[cx][cy]);
            if (ch == 1) continue;
            for (auto [dx, dy] : dir4) {
                int nx = cx + dx;
                int ny = cy + dy;
                if (nx < 0 or ny < 0 or nx >= N or ny >= N) continue;
                if (visited[nx][ny]) continue;
                que.push({nx, ny, ch - 1});
                visited[nx][ny] = true;
            }
        }
        return diff;
    };
    auto remove = [&](int x, int y, int h) -> int {
        int diff = 0;
        bool visited[N][N] = {};
        queue<array<int, 3>> que;
        que.push({x, y, h});
        visited[x][y] = true;
        while (que.size()) {
            auto [cx, cy, ch] = que.front();
            que.pop();
            diff -= abs(B[cx][cy] - A[cx][cy]);
            B[cx][cy] -= ch;
            diff += abs(B[cx][cy] - A[cx][cy]);
            if (ch == 1) continue;
            for (auto [dx, dy] : dir4) {
                int nx = cx + dx;
                int ny = cy + dy;
                if (nx < 0 or ny < 0 or nx >= N or ny >= N) continue;
                if (visited[nx][ny]) continue;
                que.push({nx, ny, ch - 1});
                visited[nx][ny] = true;
            }
        }
        return diff;
    };

    ll sm = 0;
    rep(i, N) {
        rep(j, N) {
            sm += A[i][j];
        }
    }
    vector<array<int, 3>> qs(Q);
    rep(i, Q) {
        int x = randrange(0, N);
        int y = randrange(0, N);
        int h = randrange(1, N + 1);
        qs[i] = {x, y, h};
        sm += add(x, y, h);
    }
    debug(sm);

    AnnealingManager am(TL, T0, T1, true, 1);
    auto elapsed = timer.get_elapse();
    int opcnt = 0, okcnt = 0;
    while (elapsed < TL) {
        int i = randrange(0, Q);
        auto [cx, cy, ch] = qs[i];
        int nx = randrange(0, N);
        int ny = randrange(0, N);
        int nh = randrange(1, N + 1);
        int diff = remove(cx, cy, ch) + add(nx, ny, nh);
        ll nxsm = sm + diff;
        if (am.judge(sm, nxsm, elapsed)) {
            qs[i] = {nx, ny, nh};
            sm = nxsm;
            okcnt++;
        } else {
            remove(nx, ny, nh);
            add(cx, cy, ch);
        }
        elapsed = timer.get_elapse();
        opcnt++;
    }
    debug(opcnt);
    debug(okcnt);
    debug(sm);

#ifdef __LOCAL
    ofs << Q << endl;
    rep(i, Q) {
        ofs << qs[i][0] << ' ' << qs[i][1] << ' ' << qs[i][2] << endl;
    }
#else
    cout << Q << endl;
    rep(i, Q) {
        cout << qs[i][0] << ' ' << qs[i][1] << ' ' << qs[i][2] << endl;
    }
#endif

    ll mxscore = calc(sm);
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

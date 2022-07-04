/*
・1点更新山登り。これで7100万点。
・llをintにしたり。
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
#include "common/randrange.hpp"
#include "common/Timer.hpp"
#include "common/chmin.hpp"
#include "common/chmax.hpp"
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"

const int TL = 2800;

ld solve(int testcase=-1) {
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

    ll N, K;
    cin >> N >> K;
    auto A = LIST<int>(10);
    A.insert(A.begin(), 0);
    vector<ll> X(N), Y(N);
    ll xmn = INF, ymn = INF, xmx = -INF, ymx = -INF;
    rep(i, N) {
        cin >> X[i] >> Y[i];
        chmin(xmn, X[i]);
        chmin(ymn, Y[i]);
        chmax(xmx, X[i]);
        chmax(ymx, Y[i]);
    }

    // 初期解
    vector<array<int, 4>> ans;
    // ll k = randrange(1, K+1);
    rep(i, K) {
        int px = randrange(xmn, xmx+1);
        int py = randrange(ymn, ymx+1);
        int qx = randrange(xmn, xmx+1);
        int qy = randrange(ymn, ymx+1);
        ans.pb({px, py, qx, qy});
    }

    // from lib.rs
    auto compute_score = [&](const vector<array<int, 4>>& ans) -> ld {
        vvi pieces;
        vector<int> piece(N);
        iota(ALL(piece), 0);
        pieces.eb(piece);
        for (auto [px, py, qx, qy] : ans) {
            vvi new_pieces;
            for (auto piece : pieces) {
                vector<int> left, right;
                for (auto j : piece) {
                    ll side = (qx-px) * (Y[j]-py) - (qy-py) * (X[j]-px);
                    if (side > 0) {
                        left.eb(j);
                    } else if (side < 0) {
                        right.eb(j);
                    }
                }
                if (left.size() > 0) {
                    new_pieces.eb(left);
                }
                if (right.size() > 0) {
                    new_pieces.eb(right);
                }
            }
            pieces = new_pieces;
        }
        vector<int> B(11);
        for (auto piece : pieces) {
            if (piece.size() <= 10) {
                B[piece.size()]++;
            }
        }
        int num = 0;
        int den = 0;
        rep(i, 1, 11) {
            num += min(A[i], B[i]);
            den += A[i];
        }
        return round((ld)1e6 * num / den);
    };

    auto compute_partial = [&](vector<array<int, 4>>& ans, int i, array<int, 4> nxt) {
        
    };

    ll score = compute_score(ans);
    auto elapsed = timer.get_elapse();
    int opcnt = 0;
    while (1) {
        if (opcnt%1 == 0) {
            elapsed = timer.get_elapse();
            if (elapsed >= TL) break;
        }
        opcnt++;
        int i = randrange(0, K);
        int px = randrange(xmn, xmx+1);
        int py = randrange(ymn, ymx+1);
        int qx = randrange(xmn, xmx+1);
        int qy = randrange(ymn, ymx+1);
        auto prv = ans[i];
        ans[i] = {px, py, qx, qy};
        ll nxscore = compute_score(ans);
        if (nxscore > score) {
            score = nxscore;
        } else {
            ans[i] = prv;
        }
    }
    #ifdef __LOCAL
        debug(opcnt);
    #endif

    print(ans.size());
    for (auto arr : ans) print(arr);

    score = compute_score(ans);
    return score;
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    #ifdef __LOCAL
        // 実施テスト番号
        vector<ll> T = {
            0,
        };

        // 0からn件実施
        // int n = 10;
        // vector<ll> T;
        // rep(i, n) {
        //     T.eb(i);
        // }

        ld totalscore = 0;
        for (ll t : T) {
            ld score = solve(t);
            cout << "case #" << t << " ";
            debug(score);
            totalscore += score;
        }
        debug(totalscore);
    #else
        solve();
    #endif

    return 0;
}

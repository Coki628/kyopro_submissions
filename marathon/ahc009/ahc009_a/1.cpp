/*
・これは初期解のみ。とりあえずグリッド構築だけして、出力する文字列は完全ランダム。
・まあこの倍化したグリッドの構築が地獄の始まりだったんだが…。
　今回は行けない方向は辺を張らない的な処理にして、頂点は増やさないが吉だった。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "common/listnd.hpp"
#include "grid/constants/directions.hpp"
#include "string/zfill.hpp"

const int H = 41, W = 41;
vector<string> grid(H, string(W, '.'));
vector<char> itoc = {'L', 'R', 'D', 'U'};

ld solve(int testcase=-1) {
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/"+zfill(tostr(testcase), 4)+".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/"+zfill(tostr(testcase), 4)+".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print(-1);
            exit(0);
        }
    #endif

    // 外側の壁
    rep(h, H) {
        grid[h][0] = grid[h][W-1] = '#';
    }
    rep(w, W) {
        grid[0][w] = grid[H-1][w] = '#';
    }
    // 固定壁
    rep(h, H) {
        rep(w, W) {
            if (h%2 == 0 and w%2 == 0) {
                grid[h][w] = '#';
            }
        }
    }
    ll sh, sw, th, tw;
    ld p;
    cin >> sh >> sw >> th >> tw >> p;
    sh = sh*2 + 1;
    sw = sw*2 + 1;
    th = th*2 + 1;
    tw = tw*2 + 1;
    grid[sh][sw] = 'S';
    grid[th][tw] = 'G';
    // 横軸の壁
    rep(i, 20) {
        string row;
        cin >> row;
        ll h = i*2 + 1;
        rep(j, 19) {
            ll w = (j+1) * 2;
            if (row[j] == '1') {
                grid[h][w] = '#';
            }
        }
    }
    // 縦軸の壁
    rep(i, 19) {
        string row;
        cin >> row;
        ll h = (i+1) * 2;
        rep(j, 20) {
            ll w = j*2 + 1;
            if (row[j] == '1') {
                grid[h][w] = '#';
            }
        }
    }
    // rep(h, H) {
    //     print(grid[h]);
    // }

    string ans;
    ll N = 200;
    rep(i, N) {
        ans += itoc[randrange(0, 4)];
    }

    #ifdef __LOCAL
        ofs << ans << endl;
    #else
        print(ans);
    #endif

    ld score = 0;
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
        // 100件実施
        // vector<ll> T;
        // rep(i, 100) {
        //     T.eb(i);
        // }
        ld score = 0;
        for (ll t : T) {
            score += solve(t);
        }
        debug(score);
    #else
        solve();
    #endif

    return 0;
}

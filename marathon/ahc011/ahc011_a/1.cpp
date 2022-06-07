/*
・初期解。
・とりあえずスコア計算の関数作って、毎回乱択で動かして一番マシなやつってした。
　これで500万点くらい。
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
#include "common/listnd.hpp"
#include "common/toint.hpp"
#include "common/chmax.hpp"
#include "string/zfill.hpp"

ld solve(int testcase=-1) {
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

    ll H, W, T;
    cin >> H >> T;
    W = H;
    ll N = H * W;
    vector<string> grid(H);
    rep(i, H) cin >> grid[i];

    auto nodes = list2d(H, W, 0);
    // 左上右下
    const vector<pii> dir4 = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
    const vector<char> lurd = {'L', 'U', 'R', 'D'};
    int ch = -1, cw = -1;
    rep(h, H) {
        rep(w, W) {
            // 行ける進行方向をビットで持つ
            nodes[h][w] = grid[h][w] <= '9' ? toint(grid[h][w]) : 10 + (grid[h][w]-'a');
            if (grid[h][w] == '0') {
                ch = h, cw = w;
            }
        }
    }

    // 連結成分数を数えるDFS
    auto memo = list2d(H, W, 0);
    auto dfs = [&](auto&& f, int h, int w, int prvh, int prvw) -> int {
        if (memo[h][w] != 0) {
            return memo[h][w];
        }
        memo[h][w] = -1;
        int sm = 0;
        rep(d, 4) {
            if (!(nodes[h][w]>>d & 1)) continue;
            auto [dh, dw] = dir4[d];
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (nh == prvh and nw == prvw) continue;
            // 逆側からも道があるかチェック
            int revd = (d + 2) % 4;
            if (!(nodes[nh][nw]>>revd & 1)) continue;
            int res = f(f, nh, nw, h, w);
            // 閉路があったら即NG終了
            if (res == -1) {
                return -1;
            }
            sm += res;
        }
        memo[h][w] = sm + 1;
        return sm + 1;
    };

    // スコア計算
    auto calc = [&](int k) -> ld {
        memo = list2d(H, W, 0);
        int S = 0;
        rep(h, H) {
            rep(w, W) {
                chmax(S, dfs(dfs, h, w, -1, -1));
            }
        }
        if (S < N-1) {
            return round(500000 * S/(N-1));
        } else {
            return round(500000 * (2-k/T));
        }
    };

    vector<ld> scores(T+1);
    int k = 0;
    scores[k] = calc(k);
    string ans;
    while (k < T) {
        ll nh = -1, nw = -1, d = -1;
        while (nh < 0 or nw < 0 or nh >= H or nw >= W) {
            d = randrange(0, 4);
            auto [dh, dw] = dir4[d];
            nh = ch + dh;
            nw = cw + dw;
        }
        swap(nodes[ch][cw], nodes[nh][nw]);
        ch = nh;
        cw = nw;
        k++;
        scores[k] = calc(k);
        ans += lurd[d];
    }
    int mxi = max_element(ALL(scores)) - scores.begin();
    ans = ans.substr(0, mxi);
    print(ans);
    return scores[mxi];
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

/*
・山登り、確率DP
・終了後。スコア計算パートを精査して、バグ潰した。
　グリッド倍化してる関係上、進むのは2歩ずつなんだけど、
　壁があるのは1歩先なのに、壁チェックも2歩先でやってた…。
　スコアがヴィジュアライザーと合ったのを確認して投げたら、
　64億くらいに大幅スコアアップ。ここまでやってたら青上位だった…。
　まじでもったいねぇ。。。
・ちなみにスコア合わなくて原因が分からず、そもそも確率DPでOKなのかも自信がなくなり、
　ヴィジュアライザーのスコア計算が何やってるか分かればいいのにって思ってたけど、
　rustの提供されてるコード内にそれも同梱されてるから、見れば分かるね。気付かなかった…。
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

const ll TL = 1900;
const int N = 200;
const int H = 41, W = 41;
vector<string> grid(H, string(W, '.'));
vector<char> itoc = {'U', 'D', 'L', 'R'};
map<char, int> ctoi = {{'U', 0}, {'D', 1}, {'L', 2}, {'R', 3}};
ld dp[N+1][H][W];

// グリッドBFS(経路復元)
string bfs(const vector<string> &grid, const vector<pii> &src, char invalid='#', const pii &goal={-1, -1}) {

    int H = grid.size();
    int W = grid[0].size();
    auto dist = list2d(H, W, INF);
    auto dirs = list2d(H, W, -1);
    const vector<pii> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    queue<pii> que;
    for (auto [h, w] : src) {
        que.push({h, w});
        dist[h][w] = 0;
    }
    while (!que.empty()) {
        auto [h, w] = que.front(); que.pop();
        rep(d, 4) {
            auto [dh, dw] = directions[d];
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (grid[nh][nw] == invalid) continue;
            if (dist[nh][nw] == INF) {
                dist[nh][nw] = dist[h][w] + 1;
                dirs[nh][nw] = d%2 == 0 ? d+1 : d-1;
                que.push({nh, nw});
            }
        }
    }

    // 経路復元
    string res;
    vector<char> itoc = {'U', 'D', 'L', 'R'};
    auto [sh, sw] = src[0];
    auto [ch, cw] = goal;
    while (ch != sh or cw != sw) {
        int d = dirs[ch][cw];
        auto [dh, dw] = directions[d];
        ch += dh;
        cw += dw;
        if ((ch+cw)%2 == 0) {
            res += itoc[d%2 == 0 ? d+1 : d-1];
        }
    }
    reverse(ALL(res));
    return res;
}

ld solve(int testcase=-1) {
    Timer timer;
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

    auto calc = [&](const string& ans) -> ld {
        // auto dp = list3d(N+1, H, W, (ld)0);
        rep(i, N+1) rep(h, 1, H-1, 2) rep(w, 1, W-1, 2) dp[i][h][w] = 0;
        dp[0][sh][sw] = 1;
        rep(i, N) {
            auto [dh, dw] = directions[ctoi[ans[i]]];
            rep(h, 1, H-1, 2) {
                rep(w, 1, W-1, 2) {
                    if (grid[h][w] =='#') continue;
                    if (h == th and w == tw) continue;
                    ll nh = h + dh;
                    ll nw = w + dw;
                    if (grid[nh][nw] == '#') {
                        dp[i+1][h][w] += dp[i][h][w];
                    } else {
                        nh += dh;
                        nw += dw;
                        dp[i+1][h][w] += dp[i][h][w]*p;
                        dp[i+1][nh][nw] += dp[i][h][w]*(1-p);
                    }
                }
            }
        }
        ld res = 0;
        rep(i, N+1) {
            res += dp[i][th][tw]*(401-i);
        }
        return round(250000*res);
    };

    string ans = bfs(grid, {{sh, sw}}, '#', {th, tw});
    // 同じ方に行く確率
    ll x = 100;
    while (ans.size() < N) {
        ll i = randrange(0, (ll)ans.size());
        ll pp = randrange(0, 100);
        ans.insert(ans.begin()+i, pp < x ? ans[i] : itoc[randrange(0, 4)]);
    }
    ld score = calc(ans);
    auto elapsed = timer.get_elapse();
    ll opcnt = 0;
    while (1) {
        if (opcnt%1 == 0) {
            elapsed = timer.get_elapse();
            if (elapsed >= TL) break;
        }
        opcnt++;
        ll i = randrange(0, N);
        char prvc = ans[i];
        while (1) {
            char c = itoc[randrange(0, 4)];
            if (c != ans[i]) {
                ans[i] = c;
                break;
            }
        }
        ld nxt = calc(ans);
        if (nxt >= score) {
            score = nxt;
        } else {
            ans[i] = prvc;
        }
    }
    #ifdef __LOCAL
        debug(opcnt);
    #endif

    #ifdef __LOCAL
        ofs << ans << endl;
    #else
        print(ans);
    #endif

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

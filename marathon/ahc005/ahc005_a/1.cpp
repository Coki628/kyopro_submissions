/*
参考：https://twitter.com/butsurizuki/status/1423963291676672000
・とりあえず初期解。あんま自分で方針立たなかったから、最初からTL見た。
・交差点セルを頂点としてグラフ作って全点間の距離と生き方をワーシャルフロイド、
　この全頂点を辿れば少なくとも全セルを網羅できるので、ひとまず前から順にやった。
　このTSPをここから2点スワップとかで山登りする予定。この時点でスコアは499万くらい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/common/input.hpp"
#include "../../../_lib/cpp/_src/common/print.hpp"
#include "../../../_lib/cpp/_src/common/randrange.hpp"
#include "../../../_lib/cpp/_src/common/Timer.hpp"
#include "../../../_lib/cpp/_src/grid/constants/directions.hpp"
#include "../../../_lib/cpp/_src/string/zfill.hpp"

#include "../../../_lib/cpp/_src/common/listnd.hpp"
#include "../../../_lib/cpp/_src/common/toint.hpp"
#include "../../../_lib/cpp/_src/common/chmin.hpp"

ld calc(int N, ll t) {
    return round(10000+10000000LL*N/(ld)t);
}

template<typename T>
pair<vector<vector<T>>, vector<vector<string>>> warshall_floyd(vector<vector<T>> G, vector<vector<string>> S) {
    ll N = G.size();
    rep(i, N) G[i][i] = 0;
    rep(k, N) {
        rep(i, N) {
            rep(j, N) {
                if (chmin(G[i][j], G[i][k] + G[k][j])) {
                    S[i][j] = S[i][k] + S[k][j];
                }
            }
        }
    }
    rep(i, N) {
        if (G[i][i] < 0) {
            return {};
        }
    }
    return {G, S};
}

void solve(int t=-1) {
    #ifdef __LOCAL
        // 入力ファイル読み込み
        string filename = "tools/in/"+zfill(tostr(t), 4)+".txt";
        freopen(filename.c_str(), "r", stdin);
        // 出力ファイル準備
        filename = "tools/out/"+zfill(tostr(t), 4)+".txt";
        ofstream ofs(filename.c_str());
        if (!ofs) {
            print(-1);
            return;
        }
    #endif

    ll N, sh, sw;
    cin >> N >> sh >> sw;
    vector<string> grid(N);
    rep(i, N) cin >> grid[i];
    ll H = N, W = N;

    // 交差点セルを集める
    vector<pll> cells;
    cells.eb(sh, sw);
    rep(h, H) {
        rep(w, W) {
            if (h == sh and w == sw) continue;
            if (grid[h][w] == '#') continue;
            bool hash = false, hasw = false;
            rep(d, 4) {
                auto [dh, dw] = dir4[d];
                ll nh = h+dh;
                ll nw = w+dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                if (grid[nh][nw] == '#') continue;
                if (d < 2) {
                    hash = true;
                } else {
                    hasw = true;
                }
            }
            // 縦横両方に道があれば交差点とする
            if (hash and hasw) {
                cells.eb(h, w);
            }
        }
    }

    // 交差点セルを頂点としたグラフを構築
    N = cells.size();
    auto G = list2d(N, N, INF);
    auto hwtou = list2d(H, W, -1);
    rep(u, N) {
        auto [h, w] = cells[u];
        hwtou[h][w] = u;
    }
    auto S = list2d(N, N, string());
    const vector<char> dtos = {'U', 'D', 'L', 'R'};
    rep(u, N) {
        auto [h, w] = cells[u];
        rep(d, 4) {
            // 上下左右でぶつかる交差点へ辺を張る
            auto [dh, dw] = dir4[d];
            ll nh = h, nw = w, cost = 0, cnt = 0;
            while (1) {
                nh += dh;
                nw += dw;
                if (nh < 0 or nw < 0 or nh >= H or nw >= W) break;
                if (grid[nh][nw] == '#') break;
                cost += toint(grid[nh][nw]);
                cnt++;
                if (hwtou[nh][nw] != -1) {
                    ll v = hwtou[nh][nw];
                    G[u][v] = cost;
                    S[u][v] = string(cnt, dtos[d]);
                    break;
                }
            }
        }
    }
    // 全点間最短距離とその行き方のUDLR
    tie(G, S) = warshall_floyd(G, S);

    // とりあえず今は前から順に
    vector<ll> route(N);
    iota(ALL(route), 0);
    string ans;
    ll time = 0;
    rep(i, N) {
        ll u = route[i];
        ll v = route[(i+1)%N];
        ans += S[u][v];
        time += G[u][v];
    }
    #ifdef __LOCAL
        debug(N);
        debug(time);
        debug(calc(H, time));
        ofs << ans << endl;
    #else
        print(ans);
    #endif
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
        for (ll t : T) {
            solve(t);
        }
    #else
        solve();
    #endif

    return 0;
}

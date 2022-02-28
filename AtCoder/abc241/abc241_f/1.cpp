/*
・きっちり自力AC！今日はここまで解き切れたからえらい。
・BFS応用
・隣接リストに行と列それぞれ持ってソートしておく。これで現在位置の手前と次の障害物の位置が分かる。
　それが分かれば状態遷移できるので、BFSで最短距離求める。
　状態はせいぜい障害物の数の定数倍くらいしかないはずなので大丈夫。
・訪問済メモも隣接リストも、雑に全部mapで持ったけど
　それでもちゃんと間に合うC++の速度に感謝。(AC0.3秒くらい)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
// #define CAST_MINT_TO_LL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
#include "template.hpp"

void solve() {
    ll H, W, N;
    cin >> H >> W >> N;
    ll sh, sw, gh, gw;
    cin >> sh >> sw >> gh >> gw;

    map<ll, vector<ll>> rows, cols;
    rep(i, N) {
        ll h, w;
        cin >> h >> w;
        rows[h].eb(w);
        cols[w].eb(h);
    }
    for (auto& [k, v] : rows) {
        sort(ALL(v));
    }
    for (auto& [k, v] : cols) {
        sort(ALL(v));
    }

    map<pll, ll> memo;
    queue<array<ll, 3>> que;
    que.push({sh, sw, 0});
    que.push({sh, sw, 1});
    memo[{sh, sw}] = 0;
    while (que.size()) {
        auto [ch, cw, pt] = que.front(); que.pop();
        if (pt == 0) {
            if (rows.count(ch)) {
                ll i = bisect_left(rows[ch], cw);
                if (i < rows[ch].size()) {
                    ll nw1 = rows[ch][i]-1;
                    if (not memo.count({ch, nw1})) {
                        memo[{ch, nw1}] = memo[{ch, cw}]+1;
                        que.push({ch, nw1, 1-pt});
                    }
                }
                if (i) {
                    ll nw2 = rows[ch][i-1]+1;
                    if (not memo.count({ch, nw2})) {
                        memo[{ch, nw2}] = memo[{ch, cw}]+1;
                        que.push({ch, nw2, 1-pt});
                    }
                }
            }
        } else {
            if (cols.count(cw)) {
                ll i = bisect_left(cols[cw], ch);
                if (i < cols[cw].size()) {
                    ll nh1 = cols[cw][i]-1;
                    if (not memo.count({nh1, cw})) {
                        memo[{nh1, cw}] = memo[{ch, cw}]+1;
                        que.push({nh1, cw, 1-pt});
                    }
                }
                if (i) {
                    ll nh2 = cols[cw][i-1]+1;
                    if (not memo.count({nh2, cw})) {
                        memo[{nh2, cw}] = memo[{ch, cw}]+1;
                        que.push({nh2, cw, 1-pt});
                    }
                }
            }
        }
    }
    if (memo.count({gh, gw})) {
        print(memo[{gh, gw}]);
    } else {
        print(-1);
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}

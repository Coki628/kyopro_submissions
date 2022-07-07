/*
・JOI埋め
・自力AC！やったね。
　前にも見て撤退した気がするんだけど、今日は考えたら解けた。
・グリッドダイクストラ応用、多点スタート
・コストの向きが逆だけど、ダイクストラの要領で、
　状態の良い所からの遷移を優先して行うようにすれば、
　マスの更新回数自体は各マス1回で済む。(多分)
　後は全ピラミッドの頂点を初期値に、開始位置としてキューに詰めれば、
　これもやったことのある多点スタートの探索の形になる。
・3000*3000グリッドでTLは心配だったけど、AC1.71秒。(制約5秒)
　普通のダイクストラっぽい速度が出るみたいだ。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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
using mint = ModInt<MOD>;
#include "template.hpp"

#include "grid/constants/dir8.hpp"

void solve() {
    int W, H, N;
    cin >> W >> H >> N;
    auto res = list2d(H, W, 0);
    using P = tuple<int, int, int>;
    priority_queue<P, vector<P>> que;
    rep(i, N) {
        int x, y, h;
        cin >> x >> y >> h;
        if (chmax(res[y][x], h)) {
            que.push({h, y, x});
        }
    }

    while (que.size()) {
        auto [dist, h, w] = que.top(); que.pop();
        if (res[h][w] > dist) continue;
        for (auto [dh, dw] : dir8) {
            int nh = h + dh;
            int nw = w + dw;
            if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
            if (chmax(res[nh][nw], dist-1)) {
                res[nh][nw] = dist - 1;
                que.push({dist-1, nh, nw});
            }
        }
    }

    ll ans = 0;
    rep(i, H) {
        rep(j, W) {
            ans += res[i][j];
        }
    }
    print(ans);
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

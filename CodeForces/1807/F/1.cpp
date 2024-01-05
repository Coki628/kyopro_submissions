/*
・きっちり自力AC！
・グリッド、斜め移動
・ビリヤードみたいな壁反射する移動を考える。
　方針としては、方向を含めた状態の訪問済管理をやっておけば、
　あとは移動を1マスずつ、ほぼシミュるだけ。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll H, W, sh, sw, th, tw;
    cin >> H >> W >> sh >> sw >> th >> tw;
    string S;
    cin >> S;

    ll dh = S[0] == 'U' ? -1 : 1;
    ll dw = S[1] == 'L' ? -1 : 1;
    int visited[H + 1][W + 1][2][2] = {};
    ll ch = sh, cw = sw;
    ll ans = 0;
    while (1) {
        if (ch == th and cw == tw) break;
        if (visited[ch][cw][dh > 0][dw > 0]) {
            print(-1);
            return;
        }
        visited[ch][cw][dh > 0][dw > 0] = true;
        bool bounced = false;
        if (ch + dh > H or ch + dh < 1) {
            dh *= -1;
            bounced = true;
        }
        if (cw + dw > W or cw + dw < 1) {
            dw *= -1;
            bounced = true;
        }
        ch += dh, cw += dw;
        if (bounced) ans++;
    }
    print(ans);
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(15);

    // single test case
    // solve();

    // multi test cases
    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}

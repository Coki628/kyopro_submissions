/*
・きっちり自力AC！
・mapでDP
・dp[i][(h, w)] := i回移動して位置(h, w)にいる通り数 みたいなDPで2次元目はmapで持った。
　遷移が3種類しかないから、なんとなく取りうる場所少ないんじゃないかなー、
　ってお祈りしながら投げて通した。
・もう少し考察すると、遷移A→遷移Bと遷移B→遷移Aっていう動き方が同じ場所に行くことから、
　状態数が少なそうっていう予想をより確信に近くできる。
・通ったけど何か遅くて、2.33秒くらいかかってる。(制約3秒)
　通常mapで試したらむしろ少し速くて2.14秒になったし、何かボトルネックがありそう。
・速度改善。配列節約テク使ったら0.49秒になった。
　同じことを通常mapでやると1.09秒で、この速度差は自然なので、
　HashMapがメモリの枯渇に弱い感じなのかも。
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
// constexpr int MOD = 100000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<pll> A(3);
    rep(i, 3) {
        ll x, y;
        cin >> x >> y;
        A[i] = {x, y};
    }
    HashSet<pll> blocked;
    rep(i, M) {
        ll x, y;
        cin >> x >> y;
        blocked.insert({x, y});
    }

    vector<HashMap<pll, mint>> dp(2);
    dp[0][{0, 0}] = 1;
    rep(i, N) {
        for (auto& [k, v] : dp[i%2]) {
            auto [ch, cw] = k;
            for (auto [dh, dw] : A) {
                ll nh = ch + dh;
                ll nw = cw + dw;
                if (blocked.count({nh, nw})) continue;
                dp[(i+1)%2][{nh, nw}] += v;
            }
        }
        dp[i%2].clear();
    }
    mint ans = 0;
    for (auto& [k, v] : dp[N%2]) {
        ans += v;
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

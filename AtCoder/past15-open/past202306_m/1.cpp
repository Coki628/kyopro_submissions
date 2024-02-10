/*
・自力AC！
・bitset高速化
・題意としては部分和DPなんだけど、制約が絶妙にでかい。
　Nが1000で値の範囲が400万くらいあるので、
　普通の配列に乗せたら40億でこれは無理がある。
　でも持つ値は到達可否のbool2値なので、
　bitsetに乗せて定数倍64で割れると考えると、
　間に合いそうな計算量になる。
　それでも400万のbitset1000回も作ったらきついんじゃないかと思ったけど、
　全然余裕で0.24秒で無事AC。
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
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto D = LIST(N - 1);

    bitset<4000007> bs;
    ll s = 2000003;
    bs.set(s);
    rep(i, N - 1) {
        bitset<4000007> nxt;
        nxt |= bs << D[i];
        nxt |= bs >> D[i];
        bs = move(nxt);
    }
    ll ans = INF;
    rep(i, 4000007) {
        if (bs[i]) {
            chmin(ans, abs(s - i));
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

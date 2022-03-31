/*
・きっちり自力AC！
・ビット全探索、包除原理、LCM
・色々典型要素詰まってる。
・N以下にある数の倍数がいくつあるかはシンプルに割り算で出る。
　で、2要素で考えると、両方の倍数=LCMとなる数は、2回数えてしまうので引きたい。
　同様の理論が3要素以上でも言えて、偶数回なら引いて、奇数回なら足すといった包除をやる。
　これを全ての要素の組み合わせについて、ビット全探索する。
　要素は10しかないので制約的にもぴったりだし、
　最大値50を10乗するとちょうど10^18のちょい手前くらいになって、
　オーバーフローなくこの範囲を正しく計算できることが分かる。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(K);
    cin >> A;

    ll ans = 0;
    rep(bit, 1, 1LL<<K) {
        ll l = 1;
        rep(i, K) {
            if (bit>>i & 1) {
                l = lcm(l, A[i]);
            }
        }
        ans += N / l * -pow(-1, popcount(bit));
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

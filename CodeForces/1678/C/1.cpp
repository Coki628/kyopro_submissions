/*
・きっちり自力AC！
・3点決めは真ん中固定、の4点版みたいなやつ。
・b,cを固定すると、a,dに該当する位置に重複がなくなっていい感じに数えらえれる。
　WMでぶん殴るのを5000^2とTL1.5秒で思い止まってBITにした。
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
using mint = ModInt<MOD>;
#include "template.hpp"

// #include "segment/WaveletMatrix.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST<int>(N);

    // WaveletMatrix<int, 12> wm(A);
    BIT<ll> bit1(N+1);
    ll ans = 0;
    rep(i, N) {
        int b = A[i];
        BIT<ll> bit2(N+1);
        rep(j, i+1, N) {
            bit2.add(A[j], 1);
        }
        rep(j, i+1, N) {
            int c = A[j];
            bit2.add(A[j], -1);
            // ll acnt = wm.range_freq(0, i, 0, c);
            // ll dcnt = wm.range_freq(j+1, N, 0, b);
            ll acnt = bit1.query(0, c);
            ll dcnt = bit2.query(0, b);
            ans += acnt * dcnt;
        }
        bit1.add(A[i], 1);
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

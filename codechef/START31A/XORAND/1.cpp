/*
・きっちり自力AC。
・ビット演算の特性、MSB
・MSBが重なる時はANDのが大きいし、片方だけの時はXORが大きい。
　よってMSBが同じもの同士のペアが該当するので、MSB毎に集計する。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll M = 33;
    vector<ll> C(M);
    rep(i, N) {
        C[bit_length(A[i])]++;
    }
    ll ans = 0;
    rep(i, M) {
        ans += C[i]*(C[i]-1)/2;
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

/*
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

#include "math/FormalPowerSeries.hpp"

template<typename T> void subset_zeta_transform(vector<T> &f) {
    const int n = (int)f.size();
    assert((n & (n - 1)) == 0);
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += i << 1) {
            for (int k = 0; k < i; k++) {
                f[j + k + i] += f[j + k];
            }
        }
    }
}

template<typename T> void subset_mobius_transform(vector<T> &f) {
    const int n = (int)f.size();
    assert((n & (n - 1)) == 0);
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j += i << 1) {
            for (int k = 0; k < i; k++) {
                f[j + k + i] -= f[j + k];
            }
        }
    }
}

template<typename T>
vector<T> bitwise_or_convolution(vector<T> f, vector<T> g) {
    const int n = (int)f.size();
    assert(f.size() == g.size());
    assert((n & (n - 1)) == 0);
    subset_zeta_transform(f);
    subset_zeta_transform(g);
    for (int i = 0; i < n; i++) f[i] *= g[i];
    subset_mobius_transform(f);
    return f;
}

void solve() {
    ll N, Q;
    cin >> N >> Q;
    ll M = pow(2, N);
    vector<ll> A(M), B(M);
    cin >> A >> B;

    vector<FPS<mint>> F(M, FPS<mint>(2 * N + 1)), G(M, FPS<mint>(2 * N + 1));
    rep(i, M) {
        F[i][popcount(i)] = A[i];
        G[i][popcount(i)] = B[i];
    }
    auto FG = bitwise_or_convolution(F, G);

    rep(_, Q) {
        ll x, y;
        cin >> x >> y;
        mint res = FG[x][y];
        print(res);
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

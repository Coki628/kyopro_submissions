/*
・シミュる。盤面とA[i]を両方適切に更新する。
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

void solve() {
    ll N, K, Q;
    cin >> N >> K >> Q;
    auto A = LIST(K);
    rep(i, K) A[i]--;

    vector<ll> cells(N, -1);
    rep(i, K) {
        cells[A[i]] = i;
    }
    rep(_, Q) {
        ll l;
        cin >> l;
        l--;

        if (A[l] == N-1 or cells[A[l]+1] != -1) continue;
        cells[A[l]] = -1;
        A[l]++;
        cells[A[l]] = l;
    }
    rep(i, K) A[i]++;
    print(A);
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

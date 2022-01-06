/*
・きっちり自力AC！
・操作の後半は演算がorなので、そこまでの時点で残っているビットは全て残る。
　前半の全ペアand演算で何が残るかになるが、これはいずれか2つ以上の要素で
　そのビットが立っていればいいので、立っているビット数を集計してチェックすればOK。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    const ll L = 32;
    vector<ll> C(L);
    rep(i, N) {
        rep(j, L) {
            if (A[i]>>j & 1) {
                C[j]++;
            }
        }
    }
    ll ans = 0;
    rep(i, L) {
        if (C[i] >= 2) {
            ans += 1LL<<i;
        }
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

/*
・自力AC！
・切り出したどの位置になるかによって相対的な大小関係が(多分)変わらないことが分かると、
　隣接だけ昇順にできるかチェックして、無理な所を省いた列で達成できる個数を数えるでいい。
　実装としては、無理な所を1とした列で累積和取って、区間和が0ならその区間はOKみたいにした。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    vector<ll> B(N);
    rep(i, 1, N) {
        if (A[i-1] >= A[i]*2) {
            B[i] = 1;
        }
    }
    Accumulate<ll> acc(B);
    ll ans = 0;
    rep(i, N-K) {
        ll j = i + K + 1;
        if (acc.query(i+1, j) == 0) {
            ans++;
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

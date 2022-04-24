/*
・きっちり自力AC！
・元々の差分は必須でかかる。それに加えて、Aの最大最小からはみ出した分を見る。
　最大最小の所に差し込むと両側で*2かかり、端の要素となら*2はない。
　これで小さい方取って必須と合わせる。
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

#include "numbers/arithmetic_sequence_sum.hpp"

void solve() {
    ll N, X;
    cin >> N >> X;
    auto A = LIST(N);

    ll mx = max(A);
    ll mn = min(A);
    ll base = 0;
    rep(i, N-1) {
        base += abs(A[i+1]-A[i]);
    }
    ll lo = min({(mn-1)*2, (A[0]-1), (A[N-1]-1)});
    ll hi = min({max(X-mx, 0LL)*2, max(X-A[0], 0LL), max(X-A[N-1], 0LL)});
    ll ans = base + lo + hi;
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

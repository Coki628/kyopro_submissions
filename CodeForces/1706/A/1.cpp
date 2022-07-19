/*
・きっちり自力AC！
・辞書順最小、貪欲
・前にあるやつから貪欲にAにする。2つの操作のうち前になる方を優先。
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
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);
    rep(i, N) A[i]--;

    string ans(M, 'B');
    rep(i, N) {
        ll a = A[i];
        ll b = M - A[i] - 1;
        if (a > b) swap(a, b);
        if (ans[a] == 'B') ans[a] = 'A';
        else ans[b] = 'A';
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

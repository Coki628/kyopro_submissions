/*
・きっちり自力AC！
・1行置きに斜めに置いていけばいい。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;

    if (ceil(N, 2LL) < K) {
        print(-1);
        return;
    }

    vector<string> grid(N, string(N, '.'));
    rep(i, 0, N, 2) {
        grid[i][i] = 'R';
        K--;
        if (K == 0) break;
    }
    rep(i, N) {
        print(grid[i]);
    }
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

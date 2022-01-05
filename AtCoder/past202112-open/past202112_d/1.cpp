/*
・ソート、比較関数作っちゃったけど、
　解説見たら確かにタプルに正負変えて持てばいいね、となった。
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
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    vector<array<ll, 3>> ABI;
    rep(i, N) {
        ABI.pb({A[i], B[i], i+1});
    }
    sort(ALL(ABI), [](array<ll, 3> a, array<ll, 3> b) {
        if (a[0]+a[1] != b[0]+b[1]) {
            return a[0]+a[1] > b[0]+b[1];
        }
        if (a[0] != b[0]) {
            return a[0] > b[0];
        }
        return a[2] < b[2];
    });
    vector<ll> ans;
    rep(i, N) ans.eb(ABI[i][2]);
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

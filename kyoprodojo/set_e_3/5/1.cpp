/*
・arc055_c
・自力はここまで。部分点解法でO(N^2)
・Bの位置と長さを固定すると、ACも一意になるので合うかどうかチェック。
　後からロリハ組んだけど、普通にsubstrやるやつでもN<=2000は通ってしまった。
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
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

#include "../../../_lib/cpp/_src/string/RollingHash.hpp"

void solve() {
    string S;
    cin >> S;
    ll N = S.size();

    RollingHash rh;
    auto table = rh.build(S);

    ll ans = 0;
    rep(i, 1, N) {
        rep(j, i+1, N) {
            ll m = j-i;
            if ((N-m)%2 != 0) continue;
            ll n = (N-m)/2;
            auto a1 = rh.query(table, 0, i);
            if (n-i <= 0) break;
            auto c1 = rh.query(table, j, j+(n-i));
            auto ac1 = rh.combine(a1, c1, n-i);
            auto ac2 = rh.query(table, j+(n-i), N);
            // string a1 = S.substr(0, i);
            // string c1 = S.substr(j, n-i);
            // if (a1.empty() or c1.empty()) continue;
            // string ac1 = a1+c1;
            // string ac2 = S.substr(j+(n-i));
            if (ac1 == ac2) ans++;
        }
    }
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

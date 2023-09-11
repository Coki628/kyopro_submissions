/*
・きっちり自力AC！
・ソートして累積和取って貪欲
・フリーパスを1セット買ったらなるべくD枚使い切る方が良く、
　それは通常運賃の高い方から優先して充てる方が得。
　この考えに基づいてソートして累積和取って、
　前からD個ずつフリーパスを充てるとすれば貪欲でいける。
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
    ll N, D, P;
    cin >> N >> D >> P;
    vector<ll> F(N);
    cin >> F;

    sort(F.rbegin(), F.rend());
    Accumulate<ll> acc(F);
    ll x = 0, ans = INF;
    while (1) {
        ll i = x * D;
        ll res = x * P + acc.query(min(i, N), N);
        chmin(ans, res);
        if (i >= N) break;
        x++;
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

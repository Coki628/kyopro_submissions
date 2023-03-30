/*
・なんとか自力AC！
・zero sum ranges系
・結構悩んだ。ようは区間内の各数字の出現数の偶奇が全部偶数だといい。
　で、10種の数字をビットに見立ててxorで累積取ると、zero sum ranges的なアレで数えられる。
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
    string S;
    cin >> S;
    ll N = S.size();

    vector<ll> B(N);
    rep(i, N) {
        ll a = toint(S[i]);
        B[i] = 1 << a;
    }
    vector<ll> acc(N + 1);
    rep(i, N) {
        acc[i + 1] = acc[i] ^ B[i];
    }
    auto C = Counter(acc);
    ll ans = 0;
    for (auto [k, v] : C) {
        ans += nC2(v);
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

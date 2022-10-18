/*
・きっちり自力AC。
・Aから脳を使いたくなくて1万回ループ回した。
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
    ll N;
    cin >> N;
    auto A = LIST(N);

    vector<ll> not_used(10);
    rep(i, N) {
        not_used[A[i]] = 1;
    }

    ll ans = 0;
    rep(i, 10000) {
        string s = zfill(tostr(i), 4);
        auto C = Counter(s);
        bool ok = true;
        for (auto [k, v] : C) {
            if (not_used[toint(k)] or v != 2) {
                ok = false;
                break;
            }
        }
        if (ok) ans++;
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

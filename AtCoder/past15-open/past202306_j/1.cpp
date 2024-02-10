/*
・これは自力WA。。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
#include "base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<array<ll, 3>> vec;
    rep(i, N) {
        ll a, b, x;
        cin >> a >> b >> x;
        vec.pb({a, b, x});
    }

    sort(ALL(vec), [](array<ll, 3> a, array<ll, 3> b) {
        ll aval = a[2] == 1 and a[1] >= 2 ? a[0] * 2 : a[0];
        ll bval = b[2] == 1 and b[1] >= 2 ? b[0] * 2 : b[0];
        return aval > bval;
    });
    ll cur = M, ans = 0;
    for (auto &[a, b, x] : vec) {
        if (cur > 0) {
            cur--;
            if (x == 1) {
                x = 0;
            }
            b--;
        }
    }

    sort(ALL(vec), [](array<ll, 3> a, array<ll, 3> b) {
        return a[0] > b[0];
    });
    for (auto [a, b, x] : vec) {
        if (b == 0) continue;
        if (x == 1) {
            assert(cur == 0);
        } else {
            b--;
            ll use = min(b, cur);
            if (use > 0) {
                cur -= use;
                b -= use;
            }
        }
        ans += a * b;
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

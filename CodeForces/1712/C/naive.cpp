/*
・ランダムケース用愚直解
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

    vector<ll> vec = A;
    UNIQUE(vec);
    ll M = vec.size();
    ll ans = INF;
    rep(bit, 1<<M) {
        auto cur = A;
        set<ll> se;
        rep(i, M) {
            if (bit>>i & 1) {
                se.insert(vec[i]);
            }
        }
        rep(i, N) {
            if (se.count(cur[i])) {
                cur[i] = 0;
            }
        }
        bool ok = true;
        rep(i, N-1) {
            if (cur[i] > cur[i+1]) {
                ok = false;
                break;
            }
        }
        if (ok) {
            chmin(ans, (ll)popcount(bit));
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

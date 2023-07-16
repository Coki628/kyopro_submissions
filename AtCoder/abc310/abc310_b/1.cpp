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
    vector<ll> P(N);
    vector<bitset<100>> F(N);
    rep(i, N) {
        cin >> P[i];
        ll sz;
        cin >> sz;
        rep(j, sz) {
            ll f;
            cin >> f;
            f--;
            F[i][f] = 1;
        }
    }

    rep(i, N) {
        rep(j, N) {
            if (P[i] >= P[j]) {
                bool ok = true;
                rep(k, M) {
                    if (F[i][k] and not F[j][k]) {
                        ok = false;
                        break;
                    }
                }
                if (not ok) continue;
                if (P[i] > P[j]) {
                    Yes();
                    return;
                }
                rep(k, M) {
                    if (not F[i][k] and F[j][k]) {
                        Yes();
                        return;
                    }
                }
            }
        }
    }
    No();
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

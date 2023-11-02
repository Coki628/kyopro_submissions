// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
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
    ll N;
    cin >> N;
    ll M = 200000;
    vector<ll> A(N);
    cin >> A;
    int C[N][M] = {};
    rep(i, N) {
        ll sz;
        cin >> sz;
        vector<ll> X(sz);
        cin >> X;
        X--;
        for (auto x : X) {
            C[i][x] = 1;
        }
    }

    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll sz;
        cin >> sz;
        vector<ll> Y(sz);
        cin >> Y;
        Y--;
        ll mx = -INF, res = -1;
        rep(i, N) {
            bool ok = true;
            for (auto y : Y) {
                if (C[i][y]) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                if (chmax(mx, A[i])) {
                    res = i + 1;
                }
            }
        }
        print(res);
    }
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

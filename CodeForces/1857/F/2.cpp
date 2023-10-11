/*
・終了後、やってみた。これは自力TLE。
　さすがに10^18の約数列挙を大量にやっちゃダメだろう。。
・同じyでやる約数列挙をまとめた。がしかし同じケース8でTLE。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

#include "numbers/FastPrimeFactorization.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    auto C = Counter(A);
    ll Q;
    cin >> Q;
    vector<ll> ans(Q);
    set<ll> Y;
    HashMap<pll, vector<ll>> adjx;
    rep(i, Q) {
        ll x, y;
        cin >> x >> y;
        if (y == 0) {
            if (x == 0) {
                // (0, 0)だけ
                ans[i] = nC2(C[0]);
            } else {
                // (0, x)だけ
                ans[i] = C[0] * C[x];
            }
        } else {
            Y.insert(y);
            adjx[{x, y}].eb(i);
        }
    }

    for (auto y : Y) {
        for (auto a : FastPrimeFactorization::divisors(abs(y))) {
            ll b = abs(y) / a;
            if (a != b) {
                // (+, +), (-, -)
                if (y > 0) {
                    if (adjx.count({a + b, y})) {
                        for (auto i : adjx[{a + b, y}]) {
                            ans[i] = C[a] * C[b];
                        }
                    } else if (adjx.count({-a - b, y})) {
                        for (auto i : adjx[{-a - b, y}]) {
                            ans[i] = C[-a] * C[-b];
                        }
                    }
                // (+, -), (-, +)
                } else if (y < 0) {
                    if (adjx.count({a - b, y})) {
                        for (auto i : adjx[{a - b, y}]) {
                            ans[i] = C[a] * C[-b];
                        }
                    } else if (adjx.count({b - a, y})) {
                        for (auto i : adjx[{b - a, y}]) {
                            ans[i] = C[-a] * C[b];
                        }
                    }
                }
            } else {
                // (+, +), (-, -)
                if (y > 0) {
                    if (adjx.count({a + b, y})) {
                        for (auto i : adjx[{a + b, y}]) {
                            ans[i] = nC2(C[a]);
                        }
                    } else if (adjx.count({-a - b, y})) {
                        for (auto i : adjx[{-a - b, y}]) {
                            ans[i] = nC2(C[-a]);
                        }
                    }
                // (+, -), (-, +)
                } else if (y < 0) {
                    if (adjx.count({a - b, y})) {
                        for (auto i : adjx[{a - b, y}]) {
                            ans[i] = C[a] * C[-b];
                        }
                    } else if (adjx.count({b - a, y})) {
                        for (auto i : adjx[{b - a, y}]) {
                            ans[i] = C[-a] * C[b];
                        }
                    }
                }
            }
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

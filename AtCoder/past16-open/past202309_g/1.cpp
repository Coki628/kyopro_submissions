/*
・順列全探索、これはTLE。。
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

#include "combinatorics/factorial.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N * 3);
    cin >> A;

    ll ans = 0;
    vector<ll> P(N * 3);
    iota(ALL(P), 0);
    for (auto perm : permutations(P)) {
        vector<ll> vec;
        bool ok = true;
        rep(i, N * 3) {
            vec.eb(A[perm[i]]);
            if (i % 3 == 2) {
                sort(ALL(vec));
                if (vec[0] + vec[1] <= vec[2]) {
                    ok = false;
                    break;
                }
                vec.clear();
            }
        }
        if (ok) ans++;
    }
    ans /= pow(factorial<ll>(3), 2) * factorial<ll>(N);
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

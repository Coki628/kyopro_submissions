/*
・きっちり自力AC！
・決め打ちにぶたん
・条件としては、ソート済を前後から消していくと良さそう。
　この操作の結果は単調性がありそうなので、にぶたんする。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N), B(N);
    rep(i, 1, N) {
        cin >> A[i];
    }
    A[0] = 1;
    cin >> B;

    sort(ALL(A));
    sort(ALL(B));
    ll res = bisearch_min(-1, N, [&](ll x) {
        auto cura = A;
        auto curb = B;
        reverse(ALL(curb));
        rep(_, x) {
            cura.pop_back();
            curb.pop_back();
        }
        reverse(ALL(curb));
        rep(i, cura.size()) {
            if (cura[i] >= curb[i]) {
                return false;
            }
        }
        return true;
    });
    print(res);
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

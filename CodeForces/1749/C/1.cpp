/*
・自力AC！
・二分探索、シミュレーション
・お気持ち貪欲でにぶたんしたら通った。
　kターンでアリスは勝てるか？の最大値でシミュ。
　multisetからアリスは取れる最大を取って、ボブは最小に加算させた。
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

    ll res = bisearch_max(0, N+1, [&](ll k) {
        multiset<ll> se(ALL(A));
        rep(i, 1, k+1) {
            if (se.empty()) {
                return false;
            }
            auto itr = se.upper_bound(k-i+1);
            if (itr == se.begin()) {
                return false;
            }
            itr--;
            se.erase(itr);

            if (se.empty()) {
                return true;
            }
            ll a = *se.begin(); se.erase(se.begin());
            a += (k-i+1);
            se.insert(a);
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

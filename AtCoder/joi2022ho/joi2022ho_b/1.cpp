/*
・JOI埋め
・きっちり自力AC！
・決め打ち二分探索、最小値の最大化
・目標値を決め打てば、それぞれの科目でそれを達成するための最善を尽くせる。
　授業のが良ければなるべく授業受けて、残った所は自習する。自習時間が足りなくなればNG。
・INFが足りなくて1WA。この前ABCでやったばっかだったからすぐ気づいたけど…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
// #define CAST_MINT_TO_LL
#include "base.hpp"

// constexpr long long INF = 1e18;
constexpr long long INF = LONG_LONG_MAX;
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
    auto A = LIST(N);
    auto B = LIST(N);

    ll res = bisearch_max(0, INF, [&](ll x) {
        ll rest = N * M;
        vector<ll> C(N, x);
        rep(i, N) {
            if (A[i] > B[i]) {
                ll use = min(ceil(x, A[i]), M);
                rest -= use;
                C[i] = max(x - use*A[i], 0LL);
            }
        }
        rep(i, N) {
            if (C[i] > 0) {
                ll use = ceil(C[i], B[i]);
                rest -= use;
                if (rest < 0) {
                    return false;
                }
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
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}

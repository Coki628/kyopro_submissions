/*
・自力AC。まあBよりはこっちのができたけど…。
・基本的に最大値だけが影響を受けるMODで0にしてく方針で、場合分け。
　1なしはOK、0あり1ありは無理、0なし1ありは、ソートして差分1の場所があるかチェック。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    if (find(ALL(A), 1) == A.end()) {
        YES();
        return;
    }
    if (find(ALL(A), 0) != A.end() and find(ALL(A), 1) != A.end()) {
        NO();
        return;
    }

    sort(ALL(A));
    rep(i, N-1) {
        if (abs(A[i]-A[i+1]) == 1) {
            NO();
            return;
        }
    }
    YES();
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

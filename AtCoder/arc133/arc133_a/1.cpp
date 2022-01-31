/*
・きっちり自力AC！
・辞書順最小
・A[i] > A[i+1] となる最初のA[i]でやる。
　辞書順最小なので、ここを消せばこの位置が小さくなる。
　それより手前を小さくするのは無理なのでここが最善。(と信じる)
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

    A.eb(0);
    ll target = -1;
    rep(i, N) {
        if (A[i] > A[i+1]) {
            target = A[i];
            break;
        }
    }
    assert(target != -1);

    vector<ll> ans;
    rep(i, N) {
        if (A[i] != target) {
            ans.eb(A[i]);
        }
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

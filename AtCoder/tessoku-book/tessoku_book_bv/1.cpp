/*
・きっちり自力AC！
・座標平面、隣接スワップ、縦横独立、転倒数
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

ll get_inversion(vector<ll> A) {
    Compress<ll> cp(A);
    A = cp.zip(A);
    ll M = cp.size();
    BIT<ll> bit(M);
    ll res = 0;
    for (auto a : A) {
        res += bit.query(a + 1, M);
        bit.add(a, 1);
    }
    return res;
}

void solve() {
    ll N;
    cin >> N;
    auto mat = listnd(N, N, 0);
    rep(i, N) {
        rep(j, N) {
            cin >> mat[i][j];
        }
    }

    vector<ll> A, B;
    rep(i, N) {
        rep(j, N) {
            if (mat[i][j] > 0) {
                A.eb(mat[i][j]);
            }
        }
    }
    rep(j, N) {
        rep(i, N) {
            if (mat[i][j] > 0) {
                B.eb(mat[i][j]);
            }
        }
    }
    ll ans = get_inversion(A) + get_inversion(B);
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

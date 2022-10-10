/*
・なんとか自力AC！
・二分探索、mex、枝刈り
・にぶたんでA[i]+(i+1)*xが0以上になる最小操作回数xを見つけて、
　そこから先だけやって数字がでかくなったら適当に枝刈り。
　で集めた候補について愚直にmexに使えるかチェック。を祈りながら投げた。
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
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);

    vvl B(M+1);
    rep(i, N) {
        ll x = bisearch_min(0, M, [&](ll x) {
            ll a = A[i]+(i+1)*x;
            return a >= 0;
        });
        rep(j, x, M+1) {
            ll a = A[i]+(i+1)*j;
            if (a > N) break;
            if (a >= 0) {
                B[j].eb(a);
            }
        }
    }
    rep(i, 1, M+1) {
        ll mex = 0;
        sort(ALL(B[i]));
        rep(j, B[i].size()) {
            if (B[i][j] == mex) mex++;
        }
        print(mex);
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

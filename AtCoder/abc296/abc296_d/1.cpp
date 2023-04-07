/*
・自力ならず。これは悔しい。。
・√Mまで全探索、式変形
・約数列挙したり大迷走して何も進まなかった。。
・M <= ab が条件としてあるので、まずこれの式変形を考える。
　b >= M/a としてこれを整数の範囲に限ると、b >= ceil(M, a) とできる。
　これでaを1から√Mくらいまで見ると、その先はa,b逆にしたペア(とbが同値でaが大きいもの)だけになるので、
　見なくてよくなる。これでaの取りうる範囲を1から√Mくらいまでに絞り込める。
　aが決まれば前述の式からbも一意に求まるので、後はNの方の条件チェックしながらaを全探索すればいい。
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

    ll ans = INF;
    rep(a, 1, ceil(sqrt(M)) + 1) {
        ll b = ceil(M, a);
        assert(a * b >= M);
        if (max(a, b) <= N) {
            chmin(ans, a * b);
        }
    }
    if (ans == INF) {
        ans = -1;
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

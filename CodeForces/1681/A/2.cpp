/*
・結局、最大値を初手で使うが最善っていう…。
　言われればそれが自明に思えるけど。。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    ll M;
    cin >> M;
    auto B = LIST(M);

    ll amx = max(A);
    ll bmx = max(B);
    if (amx > bmx) {
        print("Alice");
        print("Alice");
    } elif (amx < bmx) {
        print("Bob");
        print("Bob");
    } else {
        print("Alice");
        print("Bob");
    }
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

/*
・きっちり自力AC！
・約数列挙
・条件を見ると、約数の関係になっている時しかできないのが分かるので、
　A[i]を固定して約数列挙、約数となるA[j]からA[k]を一意にしてペア数を数える。
・全A[i]に対して約数列挙するタイプなので、愚直に√A[i]ではなく
　エラトステネスで前計算してlogにするやつ使ったけど、普通のでも通る。
　前者でAC0.55秒、後者が0.24秒だった。
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

#include "numbers/Eratosthenes.hpp"

const ll M = 200000;
Eratosthenes era(M);

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    auto C = Counter(A, M);
    ll ans = 0;
    rep(i, N) {
        for (auto d : era.divisors(A[i])) {
            ll b = A[i] / d;
            ans += C[d] * C[b];
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

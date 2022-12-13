/*
・すんなり自力AC！まあライブラリで殴っただけなんだけどね。。
・高速素因数分解
・欲しいのは真偽なので、GCDが2以上になるペアが1つでもあるかどうかだけ見たい。
　実際には全部素因数分解して、1つでも被る素因数があればYES。
　max(A[i])=10^9の素因数分解をO(√A[i])で10万回やるのはやばそうな気がしたので、
　高速素因数分解を召喚したら無事AC。
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

#include "numbers/FastPrimeFactorization.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    set<ll> se;
    rep(i, N) {
        for (auto [k, v] : FastPrimeFactorization::factorize(A[i])) {
            if (se.count(k)) {
                YES();
                return;
            }
            se.insert(k);
        }
    }
    NO();
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
    while (T--)
        solve();

    return 0;
}

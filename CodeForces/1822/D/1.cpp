/*
・これは実験のみ。エスパーを試みるも、良い規則性は見つからず。
　終わってみて思うのは、正解になるパターンが多すぎて探せなかった感じ。
　N=8で24個、N=10で288個もあった。
　Nが奇数は常にダメで、先頭が必ずNであることは分かった。
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

void solve() {
    ll N;
    cin >> N;

    debug(N);
    vector<ll> P(N);
    iota(ALL(P), 1);
    for (auto perm : permutations(P)) {
        vector<ll> B(N);
        B[0] = perm[0] % N;
        rep(i, 1, N) {
            B[i] = (B[i - 1] + perm[i]) % N;
        }
        UNIQUE(B);
        if (B.size() == N) {
            print(perm);
        }
    }
    cout << endl;
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

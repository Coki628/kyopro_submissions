/*
・自力AC。
・実験エスパー
・やってみると、N=1は例外。奇数は絶対無理そう。うまくいく時は値が0。
　であればビット反転したやつとペアにする感じが良さそう。
　下からやると、ビット反転で上位ビットをどこまで残すか分からないので、
　上から決めると良さそう。これで通った。
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
    ll N;
    cin >> N;

    vector<ll> A(N);
    iota(ALL(A), 1);
    // for (auto perm : permutations(A)) {
    //     set<ll> se;
    //     rep(i, N) {
    //         se.insert(A[i]&perm[i]);
    //     }
    //     if (se.size() == 1) {
    //         debug(N);
    //         debug(*se.begin());
    //         debug(perm);
    //     }
    // }
    // ・N=1は例外
    // ・奇数は絶対無理そう。
    // ・うまくいく時は全0っぽい。
    // ・ペアでちょうど全ビット埋まるような相方を上から探すと良さそう？

    if (N == 1) {
        print(1);
        print(1);
        return;
    }
    if (N%2 == 1) {
        print(-1);
        return;
    }

    vector<ll> P(N+1, -1);
    vector<ll> B;
    rep(i, N-1, -1, -1) {
        if (P[A[i]] != -1) {
            B.eb(P[A[i]]);
        } else {
            ll msb = bit_length(A[i]);
            ll msk = (1LL<<msb) - 1;
            ll j = msk ^ A[i];
            assert(P[j] == -1);
            B.eb(j);
            P[j] = A[i];
        }
    }
    reverse(ALL(B));
    print(A);
    print(B);
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

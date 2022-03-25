/*
・なんとか自力AC。
・色々考えるも、結局見えなくて、順列全探索書いて実験。
　結果、差分として現れるものしかあり得ないとエスパーできて、ソートしてにぶたん。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    // vector<ll> P(N), V;
    // iota(ALL(P), 0);
    // for (auto perm : permutations(P, N-1)) {
    //     auto cur = A;
    //     vector<bool> used(N);
    //     rep(i, N-1) {
    //         ll a = cur[perm[i]];
    //         rep(j, N) {
    //             if (used[j]) continue;
    //             cur[j] -= a;
    //         }
    //         used[perm[i]] = true;
    //     }
    //     rep(i, N) {
    //         if (not used[i]) {
    //             V.eb(cur[i]);
    //         }
    //     }
    // }
    // UNIQUE(V);
    // print(V);

    sort(ALL(A));
    A.eb(INF);
    rep(i, N) {
        ll x = *lower_bound(ALL(A), A[i]+K);
        if (x-A[i] == K) {
            YES();
            return;
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
    while (T--) solve();

    return 0;
}

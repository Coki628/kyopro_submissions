/*
・きっちり自力AC。
・大きい方から決めてく。最大値が選ばれた回数はN-1回のはずなので、
　ここから選ばれた回数を1回ずつ減らしていけば、
　同値があった場合にも何個あったのかちゃんと分かる。
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
    ll M = N * (N - 1) / 2;
    vector<ll> B(M);
    cin >> B;

    map<ll, ll> C;
    rep(i, M) {
        C[B[i]]++;
    }
    vector<ll> A;
    ll cnt = N - 1;
    for (auto& [k, v] : C) {
        while (v > 0) {
            A.eb(k);
            assert(v - cnt >= 0);
            v -= cnt;
            cnt--;
        }
    }
    A.eb(1e9);
    print(A);
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

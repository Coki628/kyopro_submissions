/*
ライブラリ整備：Wavelet Matrix
・前にK番目までの総和みたいのを取る用に内部累積和は作ってあったので、
　ちょっと追記してrange_freqした時の範囲内の和も取れるようにした。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#define __LOCAL
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

#include "datastructure/WaveletMatrix.hpp"

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    WaveletMatrix<ll> wm(A);
    ll Q;
    cin >> Q;
    ll b = 0;
    rep(i, Q) {
        ll l, r, x;
        cin >> l >> r >> x;
        l ^= b, r ^= b, x ^= b;
        l--;
        ll res = wm.range_freq_sum(l, r, 0, x + 1);
        print(res);
        b = res;
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

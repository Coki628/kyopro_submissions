/*
ライブラリ整備：重み付きWavelet Matrix
・借りてたうしさん版の仕様をNyaanさん版に組み込んだ。
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

#include "datastructure/WeightedWaveletMatrix.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;
    vector<pll> rect;
    Compress<pll> cp;
    rep(i, N) {
        ll h, w;
        cin >> h >> w;
        rect.eb(h, w);
        cp.add({w, i});
    }
    cp.build();
    ll L = cp.size();
    WeightedWaveletMatrix<ll, ll> wwm(L);
    rep(i, N) {
        auto [h, w] = rect[i];
        wwm.set(cp[{w, i}], h, h * w);
    }
    wwm.build();

    rep(i, Q) {
        ll hs, ws, hb, wb;
        cin >> hs >> ws >> hb >> wb;
        ll res = wwm.range_freq_sum(cp[{ws, INF}], cp[{wb, -INF}], hs + 1, hb);
        print(res);
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

/*
・自力AC！
・前後に番兵仕込んでランレングス。前後見て谷っぽくなってる場所が1個だけならYES。
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
    cin >> A;

    A.insert(A.begin(), INF);
    A.eb(INF);
    auto rle = RLE(A);
    ll M = rle.size();
    ll cnt = 0;
    rep(i, 1, M-1) {
        auto [k, v] = rle[i];
        if (rle[i-1].first > k and k < rle[i+1].first) {
            cnt++;
        }
    }
    assert(cnt != 0);
    if (cnt == 1) {
        YES();
    } else {
        NO();
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

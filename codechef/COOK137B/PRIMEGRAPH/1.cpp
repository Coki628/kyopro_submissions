/*
・自力AC！
・グラフ、実験エスパー
・基本方針は、完全グラフから素数の所まで均等に減らす。
　偶数はこれでいいんだけど、Nが奇数だと半端が出るからどうするか。
　自分なりに考えたやつがWAになったので実験。
　すると1つだけ次数2にするのができそうだったので、それで投げてAC。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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

Eratosthenes era(100000);

void solve() {
    ll N;
    cin >> N;

    ll ans = N*(N-1)/2;
    if(N <= 4) {
        print(ans);
        return;
    }

    // ll mx = 0;
    // vector<ll> sz;
    // vector<pii> edges;
    // rep(i, N) {
    //     rep(j, i+1, N) {
    //         edges.eb(i, j);
    //     }
    // }
    // ll M = edges.size();
    // rep(bit, 1LL<<M) {
    //     vvi nodes(N);
    //     rep(i, M) {
    //         if (bit>>i & 1) {
    //             auto [u, v] = edges[i];
    //             nodes[u].eb(v);
    //             nodes[v].eb(u);
    //         }
    //     }
    //     vector<ll> cur(N);
    //     rep(i, N) {
    //         cur[i] = nodes[i].size();
    //     }
    //     bool ok = true;
    //     rep(i, N) {
    //         if (not era.is_prime(cur[i])) {
    //             ok = false;
    //             break;
    //         }
    //     }
    //     if (ok) {
    //         if (chmax(mx, (ll)popcount(bit))) {
    //             sz = cur;
    //         }
    //     }
    // }
    // debug(mx);
    // debug(sz);

    ll cnt = N-1;
    while (not era.is_prime(cnt)) cnt--;
    if (N%2 == 0) {
        ans = N*cnt/2;
    } else {
        ans = ((N-1)*cnt+2)/2;
    }
    print(ans);
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

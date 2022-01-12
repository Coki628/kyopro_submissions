/*
・きっちり自力AC！
・最も近くて同じ値同士を組ませたいので、今出た値のindexを覚えて更新しながら前に進む。
　この2重ループをmapでうまいことするやつは、最近ABCで詰まったばっかりなのですんなり行けた。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    map<ll, ll> mp;
    ll ans = -1;
    rep(i, N) {
        if (mp.count(A[i])) {
            ll j = mp[A[i]];
            chmax(ans, j+(N-i));
        }
        mp[A[i]] = i;
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

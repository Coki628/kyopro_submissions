/*
・きっちり自力AC！
・値→indexの情報を取っておけば、できる。
　でもこれ系、添字バグりがちでいつも冷や冷やしちゃう。
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
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, Q;
    cin >> N >> Q;

    vector<ll> ans(N);
    iota(ALL(ans), 0);
    auto atoi = ans;
    rep(_, Q) {
        ll x;
        cin >> x;
        x--;
        ll xi = atoi[x];
        if (xi == N-1) {
            ll y = ans[xi-1];
            atoi[x] = xi - 1;
            atoi[y] = xi;
            swap(ans[xi], ans[xi-1]);
        } else {
            ll y = ans[xi+1];
            atoi[x] = xi + 1;
            atoi[y] = xi;
            swap(ans[xi], ans[xi+1]);
        }
    }
    rep(i, N) ans[i]++;
    print(ans);
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

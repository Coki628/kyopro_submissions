/*
・きっちり自力AC！
・セグ木、区間AND取得、セグ木にぶたん
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
    vector<ll> A(N);
    cin >> A;
    ll msk = (1LL << 30) - 1;
    auto seg = get_segment_tree(A, [](ll a, ll b) { return a & b; }, msk);

    ll Q;
    cin >> Q;
    vector<ll> ans(Q, -1);
    rep(i, Q) {
        ll l, k;
        cin >> l >> k;
        l--;
        ll r = bisearch_max(l, N + 1, [&](ll r) {
            return seg.query(l, r) >= k;
        });
        if (l < r) {
            ans[i] = r;
        }
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

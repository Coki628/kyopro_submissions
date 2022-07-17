/*
・なんとか自力AC。。
・何回目に追加された位置なのかをkがN未満になるまで遡る。
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
    ll N, C, Q;
    cin >> N >> C >> Q;
    string S;
    cin >> S;

    vector<ll> B = {0};
    vector<array<ll, 2>> P;
    P.pb({0, N});
    ll s = N;
    rep(i, C) {
        ll l, r;
        cin >> l >> r;
        l--;
        P.pb({l, r});
        B.eb(s);
        s += r - l;
    }

    rep(_, Q) {
        ll k;
        cin >> k;
        k--;
        while (k >= N) {
            ll i = bisect_right(B, k) - 1;
            auto [l, r] = P[i];
            ll add = k - B[i];
            k = l + add;
        }
        print(S[k]);
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

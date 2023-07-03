/*
・きっちり自力AC！
・さすがにFでこれは嘘では、って感じのソート貪欲をmultisetでシミュると通る。。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> P(N), L(M), D(M);
    cin >> P >> L >> D;

    multiset<ll> se(ALL(P));
    vector<pll> LD;
    rep(i, M) {
        LD.eb(-D[i], L[i]);
    }
    sort(ALL(LD));
    ll ans = sum(P);
    for (auto [d, l] : LD) {
        auto itr = se.lower_bound(l);
        if (itr != se.end()) {
            se.erase(itr);
            ans += d;
        }
    }
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

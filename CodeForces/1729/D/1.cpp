/*
・自力AC！
・工夫して貪欲
・多分3人以上で組む意味ない。Y-Xが負と正のペア組めるだけ組んで、残りの正のやつ全員で/2する。
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
    auto X = LIST(N);
    auto Y = LIST(N);

    vector<ll> YX(N);
    rep(i, N) {
        YX[i] = Y[i] - X[i];
    }
    vector<ll> V;
    multiset<ll> se;
    rep(i, N) {
        if (YX[i] >= 0) {
            se.insert(YX[i]);
        } else {
            V.eb(-YX[i]);
        }
    }
    sort(ALL(V));

    ll ans = 0;
    for (auto v : V) {
        auto itr = se.lower_bound(v);
        if (itr != se.end()) {
            se.erase(itr);
            ans++;
        }
    }
    ans += se.size() / 2;
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

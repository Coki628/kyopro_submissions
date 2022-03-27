/*
・きっちり自力AC！
・イベントソートっぽく、箱とチョコを両方同じ配列に突っ込んでソート。
　で、箱が来たらmultisetに突っ込んで、チョコが来たら一番スレスレのやつを回収みたいにやる。
　古のARCによく似た問題がある。(ARC046C)
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
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<pll> AB(N), CD(M);
    rep(i, N) cin >> AB[i].first;
    rep(i, N) cin >> AB[i].second;
    rep(i, M) cin >> CD[i].first;
    rep(i, M) cin >> CD[i].second;

    vector<array<ll, 3>> events;
    rep(i, N) {
        events.pb({AB[i].first, 0, AB[i].second});
    }
    rep(i, M) {
        events.pb({CD[i].first, 1, CD[i].second});
    }
    sort(events.rbegin(), events.rend());

    multiset<ll> se;
    for (auto [h, type, w] : events) {
        if (type == 1) {
            se.insert(w);
        } else {
            auto itr = se.lower_bound(w);
            if (itr != se.end()) {
                se.erase(itr);
            } else {
                No();
                return;
            }
        }
    }
    Yes();
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

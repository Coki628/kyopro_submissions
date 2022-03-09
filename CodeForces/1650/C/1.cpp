/*
・きっちり自力AC！
・題意をまとめると、コストが低い方から自由に取っていい。
　それを座標順に並べてペアにする。よってコストと座標で2回ソートする。
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
    vector<array<ll, 3>> P1;
    rep(i, M) {
        ll x, w;
        cin >> x >> w;
        P1.pb({w, x, i});
    }
    sort(ALL(P1));

    vector<array<ll, 2>> P2;
    ll cost = 0;
    rep(i, N*2) {
        auto [w, x, j] = P1[i];
        cost += w;
        P2.pb({x, j});
    }
    sort(ALL(P2));

    print(cost);
    rep(i, N) {
        print(mkp(P2[i][1]+1, P2[N*2-i-1][1]+1));
    }
    print();
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

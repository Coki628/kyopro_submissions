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
    ll N, M;
    cin >> N >> M;

    vector<ll> balls(N);
    iota(ALL(balls), 0);
    vector<set<ll>> boxes(N);
    rep(i, N) {
        boxes[i].insert(i);
    }

    rep(i, M) {
        ll x, y;
        cin >> x >> y;
        x--; y--;

        boxes[balls[x]].erase(x);
        boxes[y].insert(x);
        balls[x] = y;
    }

    rep(i, N) {
        balls[i]++;
    }
    print(balls, '\n');
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

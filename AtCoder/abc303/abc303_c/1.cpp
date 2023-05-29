/*
・自力AC。
・実装。処理順をよく見る(1減ってNo判定してから回復)。取得済消し忘れて1WA。
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
    ll N, M, H, K;
    cin >> N >> M >> H >> K;
    string S;
    cin >> S;
    set<pll> se;
    rep(i, M) {
        ll x, y;
        cin >> x >> y;
        se.insert({x, y});
    }

    string D = "LRDU";
    map<char, ll> mp;
    rep(i, 4) {
        mp[D[i]] = i;
    }
    int cx = 0, cy = 0;
    ll hp = H;
    rep(i, N) {
        auto [dx, dy] = dir4[mp[S[i]]];
        cx += dx, cy += dy;
        hp--;
        if (hp < 0) {
            No();
            return;
        }
        if (se.count({cx, cy}) and hp < K) {
            hp = K;
            se.erase({cx, cy});
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

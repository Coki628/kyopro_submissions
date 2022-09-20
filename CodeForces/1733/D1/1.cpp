/*
・自力AC！
・Dでこんな貪欲さすがに通らんだろ、ってな貪欲が通った…。
　差分が奇数は即アウトとして、操作2回以上あれば1つ離れた所同士でやるとしてy*操作回数、
　操作回数1は離れてれば同上、隣接ならいったん遠くでやって戻す。(しかもこれサンプルにあるので優しい)
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
    ll N, x, y;
    cin >> N >> x >> y;
    string S, T;
    cin >> S >> T;

    vector<ll> V;
    rep(i, N) {
        if (S[i] != T[i]) {
            V.eb(i);
        }
    }
    ll sm = V.size();
    if (sm%2 == 1) {
        print(-1);
        return;
    }

    ll ans = 0;
    if (sm > 2) {
        ans = y * sm / 2;
    } elif (sm == 2) {
        if (V[0]+1 == V[1]) {
            ans = min(y*2, x) * sm / 2;
        } else {
            ans = y;
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

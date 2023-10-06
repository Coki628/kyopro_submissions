/*
・自力AC。
・決め打ちにぶたん
・全体通して算数できそうだけど嫌なのでさっさとにぶたんでシミュる。
　でもこれ、後半の操作までシミュったけど、
　そこはさすがに算数で判定で良かったよね…。
　abs(i-x)*2 < s みたいな感じで多分いいはず。
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
    ll K = 1000;
    map<ll, vector<ll>> adjd;
    rep(i, N) {
        ll d, s;
        cin >> d >> s;
        adjd[d].eb(s);
    }

    ll res = bisearch_max(0, K, [&](ll x) {
        ll t = 0;
        map<ll, vector<ll>> adjt;
        vector<ll> ng(x + 1);
        rep(i, 1, x) {
            if (adjd.count(i)) {
                for (auto s : adjd[i]) {
                    adjt[t + s].eb(i);
                }
            }
            if (adjt.count(t)) {
                for (auto j : adjt[t]) {
                    ng[j] = true;
                }
            }
            t++;
        }
        rep(i, x, 0, -1) {
            if (adjt.count(t)) {
                for (auto j : adjt[t]) {
                    ng[j] = true;
                }
            }
            if (ng[i]) {
                return false;
            }
            t++;
        }
        return true;
    });
    print(res);
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

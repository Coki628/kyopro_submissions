/*
・自力AC！
・決め打ちにぶたん
・シミュは最初A[i]を全部プリキューに詰めておいて、
　使ったらk+1日後に使えるように別のmapに詰めて、
　その日が来たら回収して再度プリキューに詰める、みたいにした。
　最大を雑にINFにしてたら1.7秒で危ない。TL3秒だから多分大丈夫だと思うけど…。
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
    ll N, c, d;
    cin >> N >> c >> d;
    vector<ll> A(N);
    cin >> A;

    ll res = bisearch_max(-1, INF+1, [&](ll x) {
        map<ll, ll> mp;
        priority_queue<ll, vector<ll>> que;
        rep(i, N) {
            que.push(A[i]);
        }
        ll res = 0;
        rep(day, d) {
            if (mp.count(day)) {
                que.push(mp[day]);
            }
            if (que.size()) {
                ll mx = que.top(); que.pop();
                res += mx;
                if (day+x+1 < d) {
                    mp[day+x+1] = mx;
                }
            }
        }
        return res >= c;
    });
    if (res == -1) {
        print("Impossible");
    } elif (res == INF) {
        print("Infinity");
    } else {
        print(res);
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

/*
・自力AC！
・スケジューリング系、座圧してPQで貪欲
・使えるようになったやつからPQに突っ込むやつ。
　取り出しは終わりが早いやつ優先にする。
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
    vector<ll> T(N), D(N);
    Compress<ll> cp;
    rep(i, N) {
        cin >> T[i] >> D[i];
        D[i] += T[i] + 1;
        cp.add(T[i]);
        cp.add(D[i]);
    }
    cp.build();
    ll M = cp.size();
    T = cp.zip(T);
    D = cp.zip(D);

    vvl adj(M);
    rep(i, N) {
        adj[T[i]].eb(i);
    }
    priority_queue<ll, vector<ll>, greater<ll>> que;
    ll ans = 0;
    rep(i, M - 1) {
        ll len = cp.unzip(i + 1) - cp.unzip(i);
        for (auto j : adj[i]) {
            que.push(cp.unzip(D[j]));
        }
        ll add = 0;
        while (que.size() and add < len) {
            if (cp.unzip(i) + add < que.top()) {
                add++;
                ans++;
            }
            que.pop();
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

/*
・終了後10分弱で自力AC…悔しい。
・ビット、BFS
・制約がビットDPを思わせるが、そのくらいのビットの状態数であれば、
　BFSで全探索できるんじゃないかと思う。
・まあその方針でOKだったんだけど、どの頂点にいるかのNを最初状態に持ってなかったり、
　サボってmapで状態持ってたりで、間に合わず。
　終了後、mapをvectorに直して投げたら無事AC。。
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
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    auto dist = list2d(N, 1LL<<N, INF);
    ll s = 0;
    queue<pll> que;
    rep(i, N) {
        s = 1LL<<i;
        dist[i][s] = 1;
        que.push({i, s});
    }
    while (que.size()) {
        auto [u, s] = que.front(); que.pop();
        auto t = s;
        for (auto v : nodes[u]) {
            t ^= 1LL<<v;
            if (dist[v][t] == INF) {
                dist[v][t] = dist[u][s] + 1;
                que.push({v, t});
            }
            t ^= 1LL<<v;
        }
    }

    ll ans = 0;
    rep(bit, 1, 1LL<<N) {
        ll mn = INF;
        rep(i, N) {
            chmin(mn, dist[i][bit]);
        }
        ans += mn;
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

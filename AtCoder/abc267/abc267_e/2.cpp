/*
・なんとか時間内自力AC！
・周囲の頂点から受けるコストみたいのは前計算しておく。
　最大値の最小化でにぶたんする。
　内側のシミュパートは、コストx以下の頂点を選んで消して、
　その影響を隣接する頂点たちに与えて、みたいにする。
　このコストの動的変化をsetでやったらTLEで、終了近くなってセグ木で書き直して無事AC…。
　下界で0取れてなくてWAなの気付くのに結構かかったのも良くなかった。
*/

#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

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
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);
    vvi nodes(N);
    vector<ll> cost(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
        cost[u] += A[v];
        cost[v] += A[u];
    }
    
    ll mx = max(cost);
    ll res = bisearch_min(-1, mx, [&](ll x) {
        auto seg = get_segment_tree(cost, [](ll a, ll b) { return min(a, b); }, INF);
        auto curcost = cost;
        vector<bool> removed(N);
        rep(_, N) {
            ll u = seg.find_first(0, [&](ll a) { return a <= x; });
            // もう取れない
            if (u == -1) {
                return false;
            }
            seg.update(u, INF);
            removed[u] = true;
            for (auto v : nodes[u]) {
                if (removed[v]) continue;
                seg.update(v, seg[v]-A[u]);
            }
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
    solve();

    // multi test cases
    // int T;
    // cin >> T;
    // while (T--) solve();

    return 0;
}

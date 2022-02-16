/*
・dojo set_d_3_2
・自力AC
・でもこれはいまいち。時間かけてしまった。
　平面走査っぽさは感じつつも、どうするか結構悩んだ上で無事AC。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll H, W, M;
    cin >> H >> W >> M;
    vvl adj(H);
    auto seg = get_segment_tree([](ll a, ll b) { return max(a, b); }, -INF);
    seg.build(vector<ll>(W, 0));
    rep(i, M) {
        ll h, w;
        cin >> h >> w;
        h--; w--;
        adj[h].eb(w);
        seg.update(w, seg[w]+1);
    }

    ll ans = 0;
    rep(h, H) {
        for (ll w : adj[h]) {
            seg.update(w, seg[w]-1);
        }
        chmax(ans, seg.all()+(ll)adj[h].size());
        for (ll w : adj[h]) {
            seg.update(w, seg[w]+1);
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

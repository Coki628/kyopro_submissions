/*
・自力AC！これも当時通せなかったようなのでまあ嬉しい。
・ビット全探索、ビットの偶奇で包除、HLD*BIT、辺属性
・1つ以上存在っていう言い回しは何とも包除したくなるやつだけど、
　しばらくうまいのが見えなくて、条件の個数20本をよく検討したら
　ビット全探索でビットの偶奇で包除するやつを思い出せた。
・パスの取得は豪勢にHLD*BITを使ったけど、前計算で49ビットに入れとくの賢いね。
　でもその手のビットの前計算少し前にもやったしまあたまに出てくる印象。
　まあ通らなかったら前計算検討したと思うけど通ったのでヨシ。
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

#include "graph/HeavyLightDecomposition.hpp"
#include "datastructure/BIT2.hpp"

void solve() {
    ll N;
    cin >> N;
    vvi nodes(N);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    ll M;
    cin >> M;
    vector<pii> cond;
    rep(i, M) {
        ll a, b;
        cin >> a >> b;
        a--, b--;
        cond.eb(a, b);
    }

    HeavyLightDecomposition hld(nodes);
    ll ans = 0;
    rep(b, 1 << M) {
        BIT2<ll> bit(N);
        rep(i, M) {
            if (b >> i & 1) {
                auto [a, b] = cond[i];
                hld.update(
                    a, b, [&](ll x, ll y) { bit.add(x, y, 1); }, true
                );
            }
        }
        ll cnt = 1;
        rep(i, 1, N) {
            if (bit[hld.in[i]] == 0) {
                cnt *= 2;
            }
        }
        ans += pow(-1, popcount(b)) * cnt;
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

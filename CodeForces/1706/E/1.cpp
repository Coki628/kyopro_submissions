/*
参考：https://twitter.com/butsurizuki/status/1549072402620899328
・終了10分後くらいで書き上げたけど、システス後投げたらWAで自力ならず。。
・マージテク、部分永続UF、二分探索
・グラフの連結状態と、区間の連結状態を別々に管理する。
　グラフを連結させた時に、関係する頂点について区間が連結したかどうかもチェック。
　この区間管理の方を部分永続UFでやれば、クエリ毎ににぶたんで高速に答えが求まる。
　ここの方針はほぼ良い感じだったんだけど、区間のマージ方法が足りてなかった…。
・グラフのUFをマージさせた後、u,vの隣接だけチェックしていけた気になってたけどこれではダメで、
　集合全体(の隣接)を見る必要がある。当然まともに見るとTLEだと思うけど、
　この時連結になる可能性があるのは(u側の集合の頂点,v側の集合の頂点)だけなので、
　常に小さい方の集合だけチェックすればマージテクになって通る。
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

#include "graph/PartiallyPersistentUnionFind.hpp"

void solve() {
    ll N, M, Q;
    cin >> N >> M >> Q;
    vector<pii> edges;
    UnionFind uf1(N);
    PartiallyPersistentUnionFind uf2(N);
    vvl adj(N);
    rep(i, N) {
        adj[i].eb(i);
    }
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        ll ru = uf1.find(u);
        ll rv = uf1.find(v);
        if (ru != rv) {
            ll r = uf1.merge(u, v);
            if (r == ru) {
                if (adj[r].size() < adj[rv].size()) {
                    swap(adj[r], adj[rv]);
                }
                for (auto w : adj[rv]) {
                    if (w > 0) {
                        if (uf1.same(w, w-1)) {
                            uf2.merge(i+1, w, w-1);
                        }
                    }
                    if (w < N-1) {
                        if (uf1.same(w, w+1)) {
                            uf2.merge(i+1, w, w+1);
                        }
                    }
                    adj[r].eb(w);
                }
            } else {
                if (adj[r].size() < adj[ru].size()) {
                    swap(adj[r], adj[ru]);
                }
                for (auto w : adj[ru]) {
                    if (w > 0) {
                        if (uf1.same(w, w-1)) {
                            uf2.merge(i+1, w, w-1);
                        }
                    }
                    if (w < N-1) {
                        if (uf1.same(w, w+1)) {
                            uf2.merge(i+1, w, w+1);
                        }
                    }
                    adj[r].eb(w);
                }
            }
        }
    }

    vector<ll> ans(Q);
    rep(i, Q) {
        ll a, b;
        cin >> a >> b;
        a--; b--;
        ans[i] = bisearch_min(-1, M, [&](ll m) {
            return uf2.same(m, a, b);
        });
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

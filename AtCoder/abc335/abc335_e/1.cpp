/*
・自力ならず。。これは悔しい。
・最大化でダイクストラ、更新優先度を工夫
・自分で何やってもTLEだった。今回最大化する種類数をキューの優先度にしていた。
　これを数列A[i]の値の最小を優先度としたらAC。。
　確かにA[i]の単調増加で進む訳だから、
　更新順でそれを優先度にするのは理にかなってるよね…。
・でも最長距離はそもそもダイクストラで解くものではないんだから、
　多くの人が解いたようにDAGとしてDPする方針に行くべきだったよねそもそも。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N);
    cin >> A;
    vvpil nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v, A[v]);
        nodes[v].eb(u, A[u]);
    }

    auto dijkstra = [&](const vvpil &nodes, const vector<int> &src, int goal = -1) {
        int N = nodes.size();
        vector<ll> res(N, -INF);
        priority_queue<pli, vector<pli>, greater<pli>> que;
        for (auto s : src) {
            res[s] = 1;
            que.push({A[s], s});
        }
        while (que.size()) {
            auto [_, u] = que.top();
            que.pop();
            if (u == goal) return res;
            for (auto [v, cost] : nodes[u]) {
                if (A[u] > A[v]) continue;
                if (A[u] == A[v]) {
                    if (chmax(res[v], res[u])) {
                        que.push({A[v], v});
                    }
                }
                if (A[u] < A[v]) {
                    if (chmax(res[v], res[u] + 1)) {
                        que.push({A[v], v});
                    }
                }
            }
        }
        return res;
    };
    auto res = dijkstra(nodes, {(int)0});
    ll ans = res[N - 1] > -INF ? res[N - 1] : 0;
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

/*
・きっちり自力AC。でも時間かけたな。。
・祖先側の情報が欲しいので逆辺張ってDFSした。
　2乗が効くので雑に頂点集合を陽に持ってOK。
　マージテクみたいなことしてるけど、多分やらなくて大丈夫。
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

class Solution {
public:
    vector<vector<int>> getAncestors(int N, const vector<vector<int>>& edges) {
        ll M = edges.size();
        vvi nodes(N);
        rep(i, M) {
            ll u = edges[i][0], v = edges[i][1];
            nodes[v].eb(u);
        }

        vector<bool> visited(N);
        vector<set<int>> adj(N);
        auto dfs = [&](auto&& f, int u) -> set<int> {
            if (visited[u]) {
                return adj[u];
            }
            visited[u] = true;
            set<int> cur;
            for (auto v : nodes[u]) {
                auto res = f(f, v);
                if (cur.size() < res.size()) {
                    swap(cur, res);
                }
                for (auto w : res) {
                    cur.insert(w);
                }
            }
            cur.insert(u);
            adj[u] = cur;
            return cur;
        };
        rep(u, N) {
            dfs(dfs, u);
        }
        vvi ans(N);
        rep(u, N) {
            adj[u].erase(u);
            ans[u] = vector<int>{ALL(adj[u])};
        }
        return ans;
    }
};

#ifdef __LOCAL
    int main() {
        Solution sol;
        auto res = sol.getAncestors(
            8,
            {{0,3},{0,4},{1,3},{2,4},{2,7},{3,5},{3,6},{3,7},{4,6}}
        );
        // print(res);
        return 0;
    }
#endif

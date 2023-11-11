/*
・きっちり自力AC！
・グラフに帰着、BFS
・問題をよく読むと、ついこの前鉄則本でやったやつとほぼアイディアは同じ。(tessoku_book_br)
　遷移をいじって、BFSをダイクストラにして、終点の頂点を変えて、とかやるだけ。
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

#include "graph/_dijkstra.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    string S;
    cin >> S;
    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] - '0';
    }
    ll L = 1LL << N;
    vvpil nodes(L);
    rep(i, M) {
        ll c;
        cin >> c;
        string t1, t2;
        cin >> t1 >> t2;
        vector<ll> B1(N), B2(N);
        rep(j, N) {
            B1[j] = t1[j] - '0';
            B2[j] = t2[j] - '0';
        }
        rep(u, L) {
            ll v = u;
            rep(j, N) {
                if (B1[j]) {
                    v &= ~(1LL << j);
                }
                if (B2[j]) {
                    v |= 1LL << j;
                }
            }
            nodes[u].eb(v, c);
        }
    }
    ll s = 0;
    rep(i, N) {
        if (A[i]) {
            s += 1LL << i;
        }
    }
    ll t = 0;
    auto dist = dijkstra(nodes, {(int)s});
    ll ans = dist[t] < INF ? dist[t] : -1;
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

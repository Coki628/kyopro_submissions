/*
・自力ならず。悔しいー。
・両側からBFSで元のコストを取っておいて、
　削除する頂点kの遷移が関係する範囲だけ遷移を取り直す。
　この時、費やす遷移は1回だけとみなしてOK。(お気持ち的には、
　kを跨ぐ瞬間以外の遷移はk削除前と同様にできるため、と思ってる。)
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

#include "graph/bfs.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vvi nodes(N), nodesrev(N);
    vector<string> S(N);
    rep(i, N) {
        cin >> S[i];
        rep(j, M) {
            if (S[i][j] == '1') {
                nodes[i].eb(i + j + 1);
                nodesrev[i + j + 1].eb(i);
            }
        }
    }

    auto res = bfs(nodes, {0});
    auto resrev = bfs(nodesrev, {(int)N - 1});

    vector<ll> ans(N, INF);
    rep(k, 1, N - 1) {
        ll l = max(k - M, 0LL);
        ll r = min(k + M, N - 1);
        rep(from, l, k) {
            for (auto to : nodes[from]) {
                if (k < to) {
                    chmin(ans[k], res[from] + resrev[to] + 1);
                }
            }
        }
    }
    rep(i, N) {
        if (ans[i] >= INF) ans[i] = -1;
    }
    ans.erase(ans.begin());
    ans.pop_back();
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

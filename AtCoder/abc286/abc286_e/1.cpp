/*
・なんとか自力AC！
・BFS
・同値なら2番目の優先事項を更新するやつをやる。DPじゃなくてBFSでも要領は同じ。
　クエリ毎にBFSだと4乗で間に合わないけど、先に全頂点から前計算しておけば3乗なので大丈夫。
・最初ワーシャルフロイドが全然合わなくて、こっちで書き直して通した…。
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

vector<pll> bfs(const vvi &nodes, const vector<int> &src, vector<ll> &A) {

    int N = nodes.size();
    vector<pll> res(N, {INF, 0});
    queue<int> que;
    for (int s : src) {
        res[s] = {0, A[s]};
        que.push(s);
    }

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (auto v : nodes[u]) {
            if (res[v].first > res[u].first + 1) {
                res[v] = {res[u].first + 1, res[u].second + A[v]};
                que.push(v);
            } else if (res[v].first == res[u].first + 1) {
                chmax(res[v].second, res[u].second + A[v]);
            }
        }
    }
    return res;
}

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;
    vvi nodes(N);
    rep(i, N) {
        string S;
        cin >> S;
        rep(j, N) {
            if (S[j] == 'Y') {
                nodes[i].eb(j);
            }
        }
    }

    auto ans = listnd(N, N, pll{INF, 0});
    rep(s, N) {
        auto res = bfs(nodes, {(int)s}, A);
        rep(t, N) {
            if (ans[s][t].first > res[t].first) {
                ans[s][t] = res[t];
            } else if (ans[s][t].first == res[t].first) {
                chmax(ans[s][t].second, res[t].second);
            }
        }
    }

    ll Q;
    cin >> Q;
    rep(i, Q) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        if (ans[u][v].first >= INF) {
            print("Impossible");
        } else {
            print(ans[u][v]);
        }
    }
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

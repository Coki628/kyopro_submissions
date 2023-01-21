/*
参考：https://atcoder.jp/contests/abc286/editorial/5572
・公式解。
・ワーシャルフロイド
・やりたいことはBFSの時と同じで、コストが同値だったら価値の優先する。
　なんだけど自分のやり方だと答え全然合わなくて、
　結局コード見て比べたけど、初期化の時に始点として val[i][i] = A[i]
　みたいにしてたのが良くなくて、辺のある全部のjについて val[i][j] = A[j]
　みたいにするのが正解だった。
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

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;
    auto G = listnd(N, N, INF);
    auto val = listnd(N, N, 0LL);
    rep(i, N) {
        string S;
        cin >> S;
        G[i][i] = 0;
        rep(j, N) {
            if (S[j] == 'Y') {
                G[i][j] = 1;
                // 辺がある所だけ遷移先側のコストで初期化
                val[i][j] = A[j];
            }
        }
    }

    // warshall floyd
    rep(k, N) {
        rep(i, N) {
            rep(j, N) {
                if (G[i][j] > G[i][k] + G[k][j]) {
                    G[i][j] = G[i][k] + G[k][j];
                    val[i][j] = val[i][k] + val[k][j];
                } else if (G[i][j] == G[i][k] + G[k][j]) {
                    chmax(val[i][j], val[i][k] + val[k][j]);
                }
            }
        }
    }

    ll Q;
    cin >> Q;
    rep(i, Q) {
        ll u, v;
        cin >> u >> v;
        u--, v--;

        if (G[u][v] >= INF) {
            print("Impossible");
        } else {
            // 始点の利得はここで追加
            pll res = {G[u][v], A[u] + val[u][v]};
            print(res);
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

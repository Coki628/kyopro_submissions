/*
参考：https://twitter.com/4yAobz/status/1602090092402978817
　　　https://twitter.com/YFuka86/status/1602028817937465344
　　　https://twitter.com/SSRS_cp/status/1601994337952616448
　　　https://codeforces.com/blog/entry/110092
・自力ならず。
・グラフ、回文、部分列、LCSのDP
・ABC197Fと同じ考え方で、グラフ上の2頂点を回文の端点として持ってDPする。
　でも今回は使うのがパス全体じゃなくて部分列だったり、
　任意のパスからの最大値だったりで結構勝手は違う。
・ある1～2頂点から始めて、そこを起点に両側に部分列を伸ばしていくことを考える。
　これができるなら、DP自体はLCSのDPとほぼ同じ要領で3通りの遷移ができる。
　残る問題は、どの方向にパスを伸ばしていけばいいかよく分からない点だ。これは、
　prv[u][v] := 頂点uにいて、頂点vがある方向に向かって1つ移動した頂点
　のようなものを前計算しておくと、貰うDPする時に遷移元がどこか特定できる。
　公式解説はここから更にパス長毎に頂点ペアをまとめておいて、
　パス長の短い方からDPしていく方針を取っていたが、
　4yAobzさんの実装を参考にメモ化再帰でやることにした。
　これなら個々の遷移元さえ特定できていれば、全体としての遷移順は意識しなくてOK。
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
    string S;
    cin >> S;
    vvi nodes(N);
    rep(i, N - 1) {
        ll u, v;
        cin >> u >> v;
        u--, v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }

    // prv[u][v] := 頂点uにいて、頂点vがある方向に向かって1つ移動した頂点
    auto prv = listnd(N, N, -1);
    auto dfs = [&](auto &&f, ll r, ll u, ll par) -> void {
        for (auto v : nodes[u]) {
            if (v == par) continue;
            f(f, r, v, u);
            prv[v][r] = u;
        }
    };
    rep(i, N) {
        dfs(dfs, i, i, -1);
    }

    auto memo = listnd(N, N, -1LL);
    auto rec = [&](auto &&f, ll u, ll v) -> ll {
        if (memo[u][v] != -1) {
            return memo[u][v];
        } else if (u == v) {
            // 最初の1文字
            return memo[u][v] = 1;
        } else if (u == prv[v][u] and v == prv[u][v]) {
            // 隣接頂点で最初の1～2文字
            return memo[u][v] = S[u] == S[v] ? 2 : 1;
        }
        ll res = -INF;
        // v側1つ手前から遷移
        chmax(res, f(f, u, prv[v][u]));
        // u側1つ手前から遷移
        chmax(res, f(f, prv[u][v], v));
        if (S[u] == S[v]) {
            // 同じ文字なら、この2文字を使って両方1つ手前から遷移
            chmax(res, f(f, prv[u][v], prv[v][u]) + 2);
        }
        return memo[u][v] = res;
    };
    ll ans = -INF;
    rep(u, N) {
        rep(v, N) {
            chmax(ans, rec(rec, u, v));
        }
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
    while (T--)
        solve();

    return 0;
}

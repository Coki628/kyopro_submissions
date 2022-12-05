/*
・自力ならず。。これは悔しい。
・重み付きUF
・コスト和が0でないサイクルがあるとその連結成分はいくらでも行ける気がしたけど、
　重み付きグラフでそんなコスト込みのサイクル列挙的なのなんてできなくない？ってのと、
　いずれにしろ他の木でもない一般グラフで高速に任意のコストを答えられる方法もなくない？となり。
　順位表見ると割と同じくらいの人も通してるので、気付くべき何かがある気がしたけど何も見えず。
・重み付きUFちょっと考えたんだけど、矛盾しまくってダメじゃんて思ったけどその時は全部INFでOKかぁ。
　コスト和が0でないサイクルがあるとその連結成分はいくらでも行けるってのは
　別の考察の途中で考えてたのに、なんか紐づけらんなかったなぁ…。言われると確かに。
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

#include "graph/WeightedUnionFind.hpp"

void solve() {
    ll N, M, Q;
    cin >> N >> M >> Q;
    WeightedUnionFind<ll> uf(N);
    vector<ll> is_inf(N);
    rep(i, M) {
        ll u, v, c;
        cin >> u >> v >> c;
        u--; v--;

        if (not uf.same(u, v)) {
            uf.merge(u, v, c);
        } elif (uf.diff(u, v) != c) {
            is_inf[u] = true;
            is_inf[v] = true;
        }
    }
    rep(u, N) {
        if (is_inf[u]) {
            is_inf[uf.find(u)] = true;
        }
    }

    rep(_, Q) {
        ll x, y;
        cin >> x >> y;
        x--; y--;

        if (not uf.same(x, y)) {
            print("nan");
        } elif (is_inf[uf.find(x)]) {
            print("inf");
        } else {
            print(uf.diff(x, y));
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

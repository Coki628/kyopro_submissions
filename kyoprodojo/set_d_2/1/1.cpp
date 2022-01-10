/*
参考：https://img.atcoder.jp/agc014/editorial.pdf
・agc014_b
・自力ならず。。2年前頃の自分が自力ACしててへこむ。
・全然思いつかず。公式解説から考察過程のお気持ちを考えてみる。
　根付き木にするとすると、各クエリはmod 2で見れば、
　LCAから上も使って根からある2頂点に向かう2つのクエリと同一視できる。
　これはLCAから上は2回通るので、mod 2では使ってないのと同じになるため。
　上記より、全てのクエリが根からのものだと思えば、ある頂点に到達する回数が偶数でないと、
　その頂点から親に向かう辺が偶数回にできなそう、と思える。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;

#include "../../../_lib/cpp/_src/base.hpp"

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> C(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        C[u]++;
        C[v]++;
    }

    rep(i, N) {
        if (C[i]%2 == 1) {
            NO();
            return;
        }
    }
    YES();
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

/*
参考：https://fairy-lettuce.hatenadiary.com/entry/2021/05/02/004052
　　　https://atcoder.jp/contests/zone2021/submissions/37628959
・線形独立、XOR基底
・掃き出し法で線形独立がOKならXOR基底求めるやつでもいいんじゃないかと思ったんだけど、
　なんか最初合わなくて、WAが同じ人参考に基底のライブラリちょっといじったら通った。
　そのまま最終的に基底に残ってるやつ使っちゃうとダメで、
　その時の元の値みたいのを取っておくと、それを使えばうまくいく。
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

#include "numbers/XorBasis.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(M);
    cin >> A;

    vector<ll> banned(N);
    rep(i, M) {
        banned[A[i]]++;
    }
    XorBasis<ll, 18> basis;
    rep(i, N) {
        if (not banned[i]) {
            basis.add(i);
        }
    }

    UnionFind uf(N);
    vector<pii> ans;
    rep(u, N) {
        for (auto b : basis.saved) {
            ll v = u ^ b;
            if (not uf.same(u, v)) {
                uf.merge(u, v);
                ans.eb(u, v);
            }
        }
    }
    if (uf.size() == 1) {
        print(ans, '\n');
    } else {
        print(-1);
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

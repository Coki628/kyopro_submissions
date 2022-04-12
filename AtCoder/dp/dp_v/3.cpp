/*
・dojo set_d_6_4
・きっちり自力AC！
・全方位木DP、任意Modint
・その頂点まで見て、その頂点が黒/白の通り数、みたいな木DPで、黒→白だけ遷移させないとする。
　これで根が黒の通り数が求まるので、遷移を全方位に乗せる。
・割とすぐに遷移ちゃんと作れたのは良かったかな。
　昔の見たら、黒い方の状態しか残さないでやってたけど。白の状態いらんのか…。
　まあでも自力じゃなかったみたいだし、これはちゃんと自分でやったからOK。
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

#include "combinatorics/ArbitraryModInt.hpp"
using anymint = ArbitraryModInt;
#include "graph/ReRooting.hpp"

struct Node {
    anymint cnt1, cnt2;
};
auto f1 = [](Node a, Node b) -> Node {
    return { a.cnt1*b.cnt1, a.cnt2*b.cnt2 };
};
auto f2 = [](Node a, int _) -> Node {
    return { a.cnt1+a.cnt2, a.cnt2 };
};

void solve() {
    
    ll N, mod;
    cin >> N >> mod;
    anymint::set_mod(mod);
    auto rr = get_rerooting(N, f1, f2, Node{1, 1}, 0);
    rep(i, N-1) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        rr.add_edge(u, v, 0);
    }
    auto res = rr.build();
    for (auto a : res) print(a.cnt1);
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

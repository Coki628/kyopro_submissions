/*
参考：https://yukicoder.me/problems/no/1097
・これだった。普通に行先と和を持つダブリングでいけたじゃん。。
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

#include "common/Doubling.hpp"

struct Node {
    ll nxt, sm;
    operator ll() const { return nxt; }
};

auto f = [](const Node &prev, const Node &power) {
    Node res;
    res.nxt = power.nxt;
    res.sm = prev.sm + power.sm;
    return res;
};

void solve() {
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    vector<Node> nodes(N);
    rep(i, N) {
        nodes[i] = {(i+A[i])%N, A[i]};
    }
    ll MXLOG = 60;
    auto db = get_doubling(MXLOG, nodes, Node{-1, 0}, f);
    auto res = db.get({0, 0}, K);
    print(res.sm);
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

/*
・なんとか自力AC！
・Bが行けるAに辺張ってマッチングを最大流で、みたいなことして何とか通せた…。
　同値はまとめてあるので、辺の数は爆発しないはずだけど、確固たる自信はない。
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

#include "acl/maxflow.hpp"
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);
    auto B = LIST(N);

    rep(i, N) {
        while (A[i]%2 == 0) {
            A[i] /= 2;
        }
        while (B[i]%2 == 0) {
            B[i] /= 2;
        }
    }
    Compress<ll> cp;
    set<ll> se;
    rep(i, N) {
        cp.add(A[i]);
        cp.add(B[i]);
        se.insert(A[i]);
    }
    cp.build();
    ll M = cp.size();
    auto C1 = Counter(A);
    auto C2 = Counter(B);
    mf_graph<ll> mf(M*2+2);
    ll s = M*2;
    ll t = M*2 + 1;
    for (auto [k, v] : C2) {
        mf.add_edge(s, cp[k], v);
        ll cur = k;
        while (cur) {
            if (se.count(cur)) {
                mf.add_edge(cp[k], M+cp[cur], v);
            }
            cur /= 2;
        }
    }
    for (auto [k, v] : C1) {
        mf.add_edge(M+cp[k], t, v);
    }
    ll res = mf.flow(s, t, N);
    if (res == N) YES();
    else NO();
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

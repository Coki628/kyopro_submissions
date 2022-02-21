/*
・自力AC！
・ギャグ
・平方分割とか真面目に検討して楽しもうとした時間返して欲しい。
・結局、どこに辺付けるかとか何も関係ない。
　頂点数によって初期値みたいのが決まって、そこにsum(A)と辺数*2足して、
　あとはクエリで+2,-2する。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);
    vvi nodes(N);
    rep(i, M) {
        ll u, v;
        cin >> u >> v;
        u--; v--;
        nodes[u].eb(v);
        nodes[v].eb(u);
    }
    bool is_one = false;
    if (N == 1) is_one = true;
    ll base = -N*(N-1)/2;
    ll cur = sum(A)+base+M*2;

    ll Q;
    cin >> Q;
    rep(i, Q) {
        char op;
        ll u = -1, v = -1;
        cin >> op;
        if (op == '?') {
            if (is_one) {
                print(A[0]);
            } else {
                print(cur);
            }
        } else {
            cin >> u >> v;
            u--; v--;
            if (op == '+') {
                cur += 2;
            } else {
                cur -= 2;
            }
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

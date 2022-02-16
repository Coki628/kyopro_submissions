/*
・dojo set_d_3_6
・自力ならず。。
・実験
・実験したけど全く見えず。。
・昔の自分が実験からしっかりエスパーして自力ACしていて涙…。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
#include "../../../_lib/cpp/_src/base.hpp"

constexpr long long INF = 1e18;
// constexpr long long INF = LONG_LONG_MAX;
constexpr int MOD = 1000000007;
// constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "../../../_lib/cpp/_src/macros.hpp"

#include "../../../_lib/cpp/_src/combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;

#include "../../../_lib/cpp/_src/template.hpp"

void solve() {
    ll N, x;
    cin >> N >> x;

    vector<ll> A(N*2-1);
    iota(ALL(A), 1);
    for (auto perm : permutations(A)) {
        auto cur = perm;
        print(perm);
        while (cur.size() > 1) {
            vector<ll> nxt;
            rep(i, 2, cur.size()) {
                vector<ll> tmp = {cur[i-2], cur[i-1], cur[i]};
                sort(ALL(tmp));
                nxt.eb(tmp[1]);
            }
            cur = nxt;
            // print(cur);
        }
    print(cur[0]);
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

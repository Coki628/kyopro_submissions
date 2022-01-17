/*
・きっちり自力AC！
・隣接で桁和して10以上なら後ろ優先、未満なら前優先で使う方がいい。
　N-1箇所全チェックして、10以上の方から優先してやる。
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
    string S;
    cin >> S;
    ll N = S.size();

    vvl adj(2);
    rep(i, N-1) {
        ll a = toint(S[i]);
        ll b = toint(S[i+1]);
        if (a+b >= 10) {
            adj[0].eb(i);
        } else {
            adj[1].eb(i);
        }
    }
    rep(i, 2) {
        if (adj[i].size()) {
            ll j = (i == 0) ? adj[i].back() : adj[i][0];
            auto ans = S.substr(0, j)+tostr(toint(S[j])+toint(S[j+1]))+S.substr(j+2);
            print(ans);
            return;
        }
    }
    assert(0);
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

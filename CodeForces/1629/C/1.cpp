/*
・きっちり自力AC！
・MEX
・値毎にindexをまとめておいて、にぶたんすればそのmexが次にどこで出現するか分かるので、
　あればそこまで進むし、なければ1回そこでmexを答えに追加して状態リセット。
*/

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")

#define CONSTANTS
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
    auto A = LIST(N);

    ll M = max(A);
    vvl adj(M+2);
    rep(i, N) {
        adj[A[i]].eb(i);
    }

    ll mex = 0, nxt = 0;
    set<ll> se;
    vector<ll> ans;
    rep(i, N) {
        se.insert(A[i]);
        while (se.count(mex)) mex++;
        if (i < nxt) continue;
        ll j = bisect_left(adj[mex], i+1);
        if (j < adj[mex].size()) {
            nxt = adj[mex][j];
        } else {
            ans.eb(mex);
            mex = 0;
            se.clear();
            nxt = i+1;
        }
    }
    print(ans.size());
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
    while (T--) solve();

    return 0;
}

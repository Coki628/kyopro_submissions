/*
・古のARC埋め
・結構すんなり自力AC！
・区間GCD取得、セグ木にぶたん
・GCDが同値な区間をまとめることを考える。
　左端を固定して右端を伸ばしていくと、GCDが変化する最初の位置はにぶたんで見つかる。
　後はこれの回数が多くならないかだけど、GCDは変化する時、(多分)値が半分以下くらいにはなるので、
　数列が長くても同じGCDの区間がそう細かく変化することはない。
　区間GCDが高速に取れるようにセグ木を準備して、値はmapとかで集計すればOK。
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

void solve() {
    ll N, M;
    cin >> N >> M;
    auto A = LIST(N);
    auto X = LIST(M);

    auto seg = get_segment_tree(A, [](ll a, ll b) { return gcd(a, b); }, 0LL);
    map<ll, ll> ans;
    rep(i, N) {
        ll l = i;
        while (l < N) {
            ll val = seg.query(i, l+1);
            ll r = seg.find_first(i, [&](ll x) { return x < val; });
            if (r == -1) {
                r = N;
            }
            ans[val] += r - l;
            l = r;
        }
    }
    rep(i, M) {
        print(ans[X[i]]);
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

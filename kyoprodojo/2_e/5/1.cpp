/*
・arc085_c
・自力AC。でもめっちゃ覚えてる割に時間かかり過ぎ。。
・燃やす埋める、最小カット
・燃やす埋めるは何回やっても本質思い出すのに時間かかるなぁ。
　やる度に診断人さんのスライド熟読してる気がする…笑
　最大を求めるのに、失う最小を求める問題になって、
　でも最小の最大みたいな場所が必要だから最大フロー流して、
　みたいに欲しいことの逆の逆みたいなことしないといけないからいつも混乱するんだよね。。
・まあライブラリ改修後初のACL使用だからverifyとしては良かったかな。
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

#include "atcoder/maxflow"
using namespace atcoder;

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll s = N;
    ll t = N+1;
    mf_graph<ll> mf(N+2);
    ll mx = 0;
    rep(i, N) {
        mx += max(A[i], 0LL);
        if (A[i] > 0) {
            mf.add_edge(s, i, 0);
            mf.add_edge(i, t, A[i]);
        } else {
            mf.add_edge(s, i, -A[i]);
            mf.add_edge(i, t, 0);
        }
    }
    rep(i, N) {
        ll d = i+1;
        rep(j, i+d, N, d) {
            mf.add_edge(i, j, MOD);
        }
    }
    ll cut = mf.flow(s, t);
    ll ans = mx-cut;
    print(ans);
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

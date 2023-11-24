/*
・きっちり自力AC！
・セグ木にぶたん
・操作は決まっていて選択の余地はないので、シミュさえできればいい。
　題意の操作はセグ木にぶたんを使えば高速に求まる。
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
// constexpr int MOD = 1000000007;
constexpr int MOD = 998244353;
constexpr long double EPS = 1e-10;
constexpr long double PI = M_PI;

#include "macros.hpp"
#include "combinatorics/ModInt.hpp"
using mint = ModInt<MOD>;
#include "template.hpp"

void solve() {
    ll N, M;
    cin >> N >> M;
    vector<ll> A(N), B(M);
    cin >> A >> B;

    auto seg = get_segment_tree(B, [](ll a, ll b) { return max(a, b); }, -INF);
    rep(i, N) {
        ll j = seg.find_first(0, [&](ll x) { return x >= A[i]; });
        if (j == -1) {
            No();
            print(i + 1);
            return;
        }
        seg.update(j, seg[j] - A[i]);
    }
    vector<ll> ans(M);
    rep(i, M) {
        ans[i] = B[i] - seg[i];
    }
    Yes();
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

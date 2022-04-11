/*
・きっちり自力AC！
・セグ木にぶたん
・最大最小でセグ木2本生やせば、目当ての区間はセグ木にぶたんで取れる。
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
    ll N, MX, MN;
    cin >> N >> MX >> MN;
    auto A = LIST(N);

    auto segmx = get_segment_tree([](ll a, ll b) { return max(a, b); }, -INF);
    auto segmn = get_segment_tree([](ll a, ll b) { return min(a, b); }, INF);
    segmx.build(concat(A, {INF}));
    segmn.build(concat(A, {-INF}));
    ll ans = 0;
    rep(l, N) {
        ll mxl = segmx.find_first(l, [&](ll x) { return x >= MX; });
        ll mxr = segmx.find_first(l, [&](ll x) { return x > MX; });
        ll mnl = segmn.find_first(l, [&](ll x) { return x <= MN; });
        ll mnr = segmn.find_first(l, [&](ll x) { return x < MN; });
        ans += max(min(mxr, mnr) - max(mxl, mnl), 0LL);
    }
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

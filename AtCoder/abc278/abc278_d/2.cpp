/*
・普通の区間更新のみの遅延セグ木でやった版。
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

#include "datastructure/LazySegmentTree.hpp"

// 区間更新・区間最大値取得
auto f = [](ll a, ll b) -> ll { return max(a, b); };
auto g = [](ll a, ll b) -> ll { return b; };
auto h = [](ll a, ll b) -> ll { return b; };
const ll T = 0;
// 要素が取りうる範囲外の値にする
const ll E = INF;

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;

    auto seg = get_lazy_segment_tree(A, f, g, h, T, E);
    ll Q;
    cin >> Q;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll x;
            cin >> x;
            seg.update(0, N, x);
        } elif (op == 2) {
            ll i, x;
            cin >> i >> x;
            i--;
            seg.update(i, seg[i]+x);
        } elif (op == 3) {
            ll i;
            cin >> i;
            i--;
            ll res = seg[i];
            print(res);
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

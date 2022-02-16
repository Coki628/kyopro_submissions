/*
・dojo set_d_3_3
・なんとか自力AC！
・括弧列、遅延セグ木
・これはなんとなく方針思い出したけど、それにしても時間かかった…。
　最初やった時も添字に苦しんだのを覚えてるけど、
　こういうので確実に添字合わせるコツとか何かあるんかな。。
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

#include "../../../_lib/cpp/_src/segment/LazySegmentTree.hpp"

// 区間加算・区間最小値取得
auto f = [](ll a, ll b) -> ll { return min(a, b); };
auto g = [](ll a, ll b) -> ll { return a + b; };
auto h = [](ll a, ll b) -> ll { return a + b; };
const ll T = INF;
const ll E = 0;

void solve() {
    ll N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;

    vector<ll> A(N);
    rep(i, N) {
        A[i] = S[i] == '(' ? 1 : -1;
    }
    auto acc = A;
    rep(i, N-1) {
        acc[i+1] += acc[i];
    }
    acc.insert(acc.begin(), 0);

    auto seg = get_lazy_segment_tree(f, g, h, T, E);
    seg.build(acc);
    rep(_, Q) {
        ll op, l, r;
        cin >> op >> l >> r;
        l--;
        if (op == 1) {
            if (A[l] == A[r-1]) continue;
            seg.update(l+1, r, A[l] == 1 ? -2 : 2);
            swap(A[l], A[r-1]);
        } else {
            if (seg.query(l, r)-seg[l] >= 0 and seg[r]-seg[l] == 0) {
                Yes();
            } else {
                No();
            }
        }
        // seg.print(N+1);
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

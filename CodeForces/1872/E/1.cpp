/*
・きっちり自力AC！
・遅延セグ木、区間XOR取得・区間01反転
・区間01フリップの取得側に01じゃないのを乗せるのは前にやったことがある。(past202107_n)
　これを見ると、取得の要素側に01の代わりに普通の値を乗せればいいのが分かるので、やる。
　演算が今回は和じゃなくてXORだけど、加算とXORは性質もかなり似てるし同様にできると信じる。
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

#include "datastructure/LazySegmentTree.hpp"

// 区間XOR取得・区間01反転
struct Node {
    ll cnt0, cnt1;
    operator ll() const { return cnt1; }
};
auto f = [](Node a, Node b) -> Node {
    a.cnt0 ^= b.cnt0;
    a.cnt1 ^= b.cnt1;
    return a;
};
auto g = [](Node a, bool b) -> Node {
    // 偶数回反転したらそのまま
    if (!b) {
        return a;
    } else {
        // 0と1の数が入れ替わる
        return {a.cnt1, a.cnt0};
    }
};
auto h = [](bool a, bool b) -> bool { return a ^ b; };
// { 区間内の0の個数, 区間内の1の個数 }
const Node T = {0, 0};
const bool E = false;

void solve() {
    ll N;
    cin >> N;
    vector<ll> A(N);
    cin >> A;
    string S;
    cin >> S;

    auto seg = get_lazy_segment_tree(N, f, g, h, T, E);
    rep(i, N) {
        if (S[i] == '0') {
            seg.set(i, {A[i], 0});
        } else {
            seg.set(i, {0, A[i]});
        }
    }
    seg.build();

    ll Q;
    cin >> Q;
    vector<ll> ans;
    rep(_, Q) {
        ll op;
        cin >> op;
        if (op == 1) {
            ll l, r;
            cin >> l >> r;
            l--;
            seg.update(l, r, 1);
        } else {
            ll g;
            cin >> g;
            auto res = seg.query(0, N);
            if (g == 0) {
                ans.eb(res.cnt0);
            } else {
                ans.eb(res.cnt1);
            }
        }
    }
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

/*
・きっちり自力AC！
・1点更新・全体MEX取得、セグ木にぶたん
・mexの高速な取得がセグ木でできるのは前にやったことがあった。(多分ARC038c)
　ので、その雰囲気を思い出しながら書いた。
　結果的にそう詰まらずACはできたけど、
　MEXに大きすぎる値は不要なので、クエリ先読み座圧パートは余計だったな。
　もうちょい手際良くやれても良かった。
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
    ll N, Q;
    cin >> N >> Q;
    vector<ll> A(N);
    cin >> A;
    Compress<ll> cp;
    for (auto a : A) {
        cp.add(a);
    }
    rep(a, 400000) {
        cp.add(a);
    }
    vector<array<ll, 2>> qs;
    rep(_, Q) {
        ll i, x;
        cin >> i >> x;
        i--;
        qs.pb({i, x});
        cp.add(x);
    }
    cp.build();
    ll M = cp.size();

    auto seg = get_segment_tree(vector<ll>(M), [](ll a, ll b) { return min(a, b); }, INF);
    rep(i, N) {
        ll j = cp[A[i]];
        seg.update(j, seg[j] + 1);
    }
    for (auto [i, x] : qs) {
        ll j = cp[A[i]];
        seg.update(cp[j], seg[j] - 1);
        A[i] = x;
        j = cp[A[i]];
        seg.update(cp[j], seg[j] + 1);
        ll res = seg.find_first(0, [](ll x) { return x <= 0; });
        print(cp.unzip(res));
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

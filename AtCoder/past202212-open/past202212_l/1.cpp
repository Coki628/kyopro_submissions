/*
・時間外だけどなんとか自力AC！
・内包する区間
・座圧してソートして平面走査っぽく解く。
　左端で降順ソートしておけば既に終わった要素のLに関する条件は満たされるので、
　Rについてセグ木に、そこまでの最大個数を詰めていく。
　条件を満たすRの範囲[0,r]から今までの最大を取って自分の分+1を追加
　これを最後までやって一番いいのが答え。
・解説見た。LISだって。確かにこれってLISのセグ木で解く方だ。
　Lが降順になっただけだ…。
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
    ll N;
    cin >> N;
    vector<pll> LR;
    Compress<ll> cp;
    rep(i, N) {
        ll l, r;
        cin >> l >> r;
        LR.eb(-l, r);
        cp.add(r);
    }
    cp.build();
    ll M = cp.size();
    auto seg = get_segment_tree(vector<ll>(M), [](ll a, ll b) { return max(a, b); }, -INF);
    sort(ALL(LR));
    rep(i, N) {
        auto [l, r] = LR[i];
        ll cpr = cp[r];
        ll mx = seg.query(0, cpr + 1);
        seg.update(cpr, max(seg[cpr], mx + 1));
    }
    ll ans = seg.all();
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

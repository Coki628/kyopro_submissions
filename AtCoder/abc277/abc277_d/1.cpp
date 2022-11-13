/*
・きっちり自力AC！
・円環、累積和
・ソートするとカードが引ける範囲は区間になるので、
　予め累積和作っておけば区間和で取れる。末尾から先頭は繋がるなら個別にやった。
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
    vector<ll> A(N);
    cin >> A;

    ll total = sum(A);
    auto C = Counter(A);
    UNIQUE(A);
    N = A.size();
    Accumulate<ll> acc(N);
    rep(i, N) {
        acc.add(i, C[A[i]]*A[i]);
    }
    acc.build();
    vector<pll> segs;
    pll cur = {0, -1};
    rep(i, N-1) {
        if (A[i+1] != A[i]+1) {
            cur.second = i + 1;
            segs.eb(cur);
            cur = {i+1, -1};
        }
    }
    cur.second = N;
    segs.eb(cur);

    if (segs.size() == 1) {
        print(0);
        return;
    }

    ll mx = 0;
    for (auto [l, r] : segs) {
        chmax(mx, acc.query(l, r));
    }
    if (A[0] == 0 and A.back() == M-1) {
        auto [l1, r1] = segs[0];
        auto [l2, r2] = segs.back();
        chmax(mx, acc.query(l1, r1) + acc.query(l2, r2));
    }
    ll ans = total - mx;
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

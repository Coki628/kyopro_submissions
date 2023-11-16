/*
・これはWA。色々穴がありそうだが、この時点では分からない。
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
    ll N, L, K;
    cin >> N >> L >> K;
    vector<ll> A(N), C(N);
    rep(i, N) {
        cin >> A[i] >> C[i];
    }
    A.insert(A.begin(), 0);
    C.insert(C.begin(), 0);
    A.eb(L);
    C.eb(0);
    N++;

    auto seg = get_segment_tree(C, [](ll a, ll b) { return min(a, b); }, INF);
    ll i = 0, k = K;
    ll ans = 0;
    while (i < N) {
        ll l = i + 1;
        ll r = bisect_right(A, A[i] + K, l);
        if (r == l) {
            print(-1);
            return;
        }
        ll mn = seg.query(l, r);
        ll mni = seg.find_first(l, [&](ll x) { return x <= mn; });
        assert(mni != -1);
        ll dist = A[mni] - A[i];
        // 今位置がmnより得なら満タン、そうでなければmnまでの最低限
        ll fill = C[i] < mn ? K - k : dist - k;
        assert(fill >= 0);
        assert(fill <= K);
        ll cost = fill * C[i];
        k += fill;
        assert(k <= K);
        k -= dist;
        assert(k >= 0);
        ans += cost;
        i = mni;
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

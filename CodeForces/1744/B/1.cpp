/*
・きっちり自力AC！
・偶奇で総和と個数を覚えておく。足すのが偶数ならそのまま、奇数なら逆側に集める。
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
    ll N, Q;
    cin >> N >> Q;
    auto A = LIST(N);

    vector<ll> sm(2), cnt(2);
    rep(i, N) {
        sm[A[i]%2] += A[i];
        cnt[A[i]%2]++;
    }
    rep(i, Q) {
        ll op, x;
        cin >> op >> x;
        if (op == 0) {
            if (x%2 == 0) {
                sm[0] += cnt[0]*x;
            } else {
                sm[1] += sm[0] + cnt[0]*x;
                cnt[1] += cnt[0];
                sm[0] = 0;
                cnt[0] = 0;
            }
        } else {
            if (x%2 == 0) {
                sm[1] += cnt[1]*x;
            } else {
                sm[0] += sm[1] + cnt[1]*x;
                cnt[0] += cnt[1];
                sm[1] = 0;
                cnt[1] = 0;
            }
        }
        ll ans = sm[0] + sm[1];
        print(ans);
    }
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

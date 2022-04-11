/*
参考：https://codeforces.com/blog/entry/101790
・自力ならず。これは悔しい。
・決め打ち二分探索
・変な貪欲に固執してしまった。A,Bならともかく、Cでそういうことはあんまりないのに…。
　まあでも最適がmax(A)だけでなくmax(A)+1もあるってことに、
　だいぶ終わる頃になって気付いたのが良くなかったな。もっと検討すべきだった。
・決め打ちにぶたんだと思えば、まあ日数によって1と2を使える回数は一意に定まるし、
　使わなくてもいいって問題に書いてあるから、2から貪欲に使ってみて、
　減らし切れればOKだし、無理なら無理。直感的に考えつく条件で通る。
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

ll calc(const vector<ll>& A, ll mx) {
    ll N = A.size();
    ll res = bisearch_min(-1, INF, [&](ll m) {
        vector<ll> need(N);
        rep(i, N) {
            need[i] = mx - A[i];
        }
        ll cnt1 = ceil(m, 2LL);
        ll cnt2 = m / 2;
        rep(i, N) {
            ll use = min(need[i]/2, cnt2);
            need[i] -= use * 2;
            cnt2 -= use;
        }
        rep(i, N) {
            ll use = min(need[i], cnt1);
            need[i] -= use;
            cnt1 -= use;
        }
        return sum(need) == 0;
    });
    return res;
}

void solve() {
    ll N;
    cin >> N;
    auto A = LIST(N);

    ll mx = max(A);
    ll ans = min(calc(A, mx), calc(A, mx+1));
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

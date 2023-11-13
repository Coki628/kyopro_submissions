/*
参考：https://codeforces.com/blog/entry/117468
・自力ならず。悔しいな、これは解けるべきだった。。
・区間、過半数、決め打ちにぶたん
・1回目のクエリで過半数を満たした区間は、
　2回目以降のクエリ時にも明らかに満たしたままなので、
　同様に全部単調性あって、クエリ回数のにぶたんでシミュできる。
　これなんで気付かなかったー。。
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
    ll N, M;
    cin >> N >> M;
    vector<ll> L(M), R(M);
    rep(i, M) {
        cin >> L[i] >> R[i];
        L[i]--;
    }
    ll Q;
    cin >> Q;
    vector<ll> qs(Q);
    cin >> qs;
    qs--;

    ll res = bisearch_min(0, Q + 1, [&](ll x) {
        Accumulate<ll> acc(N);
        rep(i, x) {
            acc.set(qs[i], 1);
        }
        acc.build();
        rep(i, M) {
            ll len = R[i] - L[i];
            ll sm = acc.query(L[i], R[i]);
            if (sm > len / 2) {
                return true;
            }
        }
        return false;
    });
    print(res <= Q ? res : -1);
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

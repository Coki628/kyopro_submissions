/*
参考：https://qiita.com/keroru/items/6e0a22e8c9bf2a24dc68
・尺取りのキュー実装
・これはTLE。セグ木の代わりにビット管理にしたけど、
　60のlog2つはさすがに重かったっぽい。
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
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    ll L = 60;
    ll ans = bisearch_max(0, 1LL << L, [&](ll x) {
        vector<ll> C(L);
        deque<ll> que;
        ll cnt = 0, orsm = 0, i = 0;
        rep(_, N) {
            while (i < N and orsm < x) {
                rep(b, L) {
                    if (A[i] >> b & 1) {
                        C[b]++;
                        if (C[b] == 1) {
                            orsm += 1LL << b;
                        }
                    }
                }
                que.pb(A[i]);
                i++;
            }
            if (orsm >= x) {
                cnt += N - i + 1;
            }
            rep(b, L) {
                if (que.front() >> b & 1) {
                    C[b]--;
                    if (C[b] == 0) {
                        orsm -= 1LL << b;
                    }
                }
            }
            que.pop_front();
        }
        return cnt >= K;
    });
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

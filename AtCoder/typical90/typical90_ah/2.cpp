/*
参考：https://qiita.com/keroru/items/6e0a22e8c9bf2a24dc68
・尺取りのキュー実装
・これも添字なしで楽ちん。
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

    map<ll, ll> C;
    ll ans = 0, cnt = 0;
    deque<ll> que;
    for (auto a : A) {
        if (C[a] == 0) {
            cnt++;
        }
        C[a]++;
        que.eb(a);
        while (que.size() and cnt > K) {
            C[que.front()]--;
            if (C[que.front()] == 0) {
                cnt--;
            }
            que.pop_front();
        }
        chmax(ans, (ll)que.size());
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

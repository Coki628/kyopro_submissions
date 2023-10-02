/*
参考：https://qiita.com/keroru/items/6e0a22e8c9bf2a24dc68
・尺取りのキュー実装
・短く動かすタイプ。これだとちょっとだけ複雑になる。
　とはいえ左端の削除と区間長はdequeに丸投げなので、右端を進めるiだけ気にすればいい。
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
#include "common/input.hpp"
#include "common/print.hpp"
#include "common/chmin.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    deque<ll> que;
    vector<ll> C(K + 1);
    ll ans = INF, cnt = 0, i = 0;
    rep(_, N) {
        while (i < N and cnt < K) {
            que.eb(A[i]);
            if (A[i] <= K) {
                C[A[i]]++;
                if (C[A[i]] == 1) {
                    cnt++;
                }
            }
            i++;
        }
        // 満たしてると限らないので条件チェックする
        if (cnt == K) {
            chmin(ans, (ll)que.size());
        }
        if (que.front() <= K) {
            C[que.front()]--;
            if (C[que.front()] == 0) {
                cnt--;
            }
        }
        que.pop_front();
    }
    if (ans >= INF) {
        ans = 0;
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

/*
参考：https://qiita.com/keroru/items/6e0a22e8c9bf2a24dc68
・尺取りのキュー実装
・久々の尺取りでやはり添字に発狂しかけたので、ずっと気になってたこれやってみた。
　結果すごくいい。これが複雑めな尺取りにも一般に通用するならかなり有用そうなので、
　これから何問か試しに解いてみようと思う。
・実装としては、今まで自分がやってたやつは、
　右端を進めるだけ進める → 左端を1個減らす
　みたいな流れだったけど、これは
　右端を1個足す → 左端を減らせるだけ減らす
　みたいになるので、そこが違うのは意識していこう。
　添字が壊れるのを気にする代わりなのは、キューの空ポップのチェックやるくらいなので、
　添字ゲーよりずっと直感的に対処できると思う。
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

    ll ans = 0, sm = 0;
    deque<ll> que;
    for (auto a : A) {
        // 右端に1つ追加
        que.eb(a);
        sm += a;
        // 条件を満たさない限り、左端を縮める
        while (que.size() and sm > K) {
            sm -= que.front();
            que.pop_front();
        }
        // この右端で条件を満たす区間を答えに計上する
        ans += que.size();
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

/*
参考：https://qiita.com/keroru/items/6e0a22e8c9bf2a24dc68
・尺取りのキュー実装
・短く動かすタイプ。セグ木との連携。でもこれはセグ木を横軸に使ってるとかじゃなくて、
　単に縦軸の演算orが差分で区間和みたいにできないので、代わりにセグ木使ってる感じ。
　(ってことはmaxとかminでも同じ要領で尺取りの縦軸に乗せれるのか)
　一応これもキューに詰めることで左端の添字持たないで済むんだけど、
　まあこれは添字で持ってもいいかなって感じ。キューの中身使ってないし。。
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

#include "datastructure/SparseTable.hpp"

void solve() {
    ll N, K;
    cin >> N >> K;
    vector<ll> A(N);
    cin >> A;

    auto st = get_sparse_table(A, [](ll a, ll b) { return a | b; }, 0LL);
    ll L = 60;
    ll ans = bisearch_max(0, 1LL << L, [&](ll x) {
        deque<ll> que;
        ll cnt = 0, i = 0;
        rep(_, N) {
            while (i < N and st.query(i - que.size(), i) < x) {
                que.pb(A[i]);
                i++;
            }
            if (st.query(i - que.size(), i) >= x) {
                cnt += N - i + 1;
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

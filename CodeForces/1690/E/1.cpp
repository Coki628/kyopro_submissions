/*
・自力ならず。。
・嘘っぽい貪欲でずっと沼ってた…。と思ったら概ね方針は合ってたらしい。
・割られた時切り捨てられるものを最小化したくて、なのでmod Kにして、後は貪欲にマッチング。
　(0以外の)小さい方から、なるべく大きくてK以上になるやつと組ませて、
　K/2までやったら残ったK/2以上のやつはどう組んでも[K,2K)の間のはずなので適当に組む。
　前半で余ったやつは諦める。ってやったんだけどね。
　だいたい合ってるみたいなんだけど、何が間違ってるか分からん。
　頑張れば見つかると思うんだけどモチベが上がらん。。
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
    ll N, K;
    cin >> N >> K;
    auto A = LIST(N);

    ll total = sum(A);
    rep(i, N) {
        A[i] %= K;
    }
    auto C = Counter(A, K);
    ll sub = 0;
    queue<pll> que;
    rep(i, 1, K) {
        ll j = K - i;
        if (j < i) break;
        if (C[j]) {
            que.push({C[j], j});
            C[j] = 0;
        }
        while (C[i] > 0 and que.size()) {
            if (C[i] < que.front().first) {
                que.front().first -= C[i];
                C[i] = 0;
            } else {
                C[i] -= que.front().first;
                que.pop();
            }
        }
        sub += C[i] * i;
    }
    // 残りはK/2以上なので適当に組んでいいはず
    ll tmpsm = 0, tmpcnt = 0;
    while (que.size()) {
        auto [cnt, val] = que.front(); que.pop();
        tmpsm += cnt * val;
        tmpcnt += cnt;
    }
    sub += tmpsm - K*(tmpcnt/2);
    ll ans = (total-sub) / K;
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
